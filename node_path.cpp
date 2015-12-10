#include "output.hpp"
#include "type.hpp"
#include "node.hpp"

namespace libblock {

void NodePath::renderPath(std::ostream &os, size_t level) const {
    for (size_t i = 0; i < level; ++i) {
        os << "->parent";
    }

    if (name != "self") {
        os << "->" << name;
    }
}

Instance &NodePath::getInner(Instance &instance, Output &output) {
    return source.buildOut(
        instance,
        output,
        [](Type &type) -> std::string {
            return type.strReint("tmp");
        }
    ).prepareLookup();
}

NodePath::NodePath(Node &_source, LookupMode _mode, std::string &&_name):
    source {_source},
    mode {_mode},
    name {std::move(_name)} {}

NodePath::NodePath(Node &_source, LookupMode _mode, const std::string &_name):
    source {_source},
    mode {_mode},
    name {_name} {}

void NodePath::buildProc(
    Instance &instance,
    Output &output
) {
    // get inner

    Instance &inner {
        getInner(instance, output)
    };

    // gen type

    size_t level {0};

    if (mode == LookupMode::local) {
        inner.at(name);
    } else {
        inner.lookup(name, level);
    }
}

Type &NodePath::buildOut(
    Instance &instance,
    Output &output,
    std::gc_function<std::string (Type &)> &&target
) {
    // get inner

    Instance &inner {
        getInner(instance, output)
    };

    // get type

    size_t level {0};

    Type &type {
        mode == LookupMode::local ?
        inner.at(name) : inner.lookup(name, level)
    };

    // render

    output.content(
        instance,
        [&, target = std::move(target), level](OutputContext &oc) {
            oc.endl();
            oc.os << target(type) << " = " << inner.strReint("tmp");
            renderPath(oc.os, level);
            oc.os << ";";
        }
    );

    // return

    return type;
}

void NodePath::buildIn(
    Instance &instance, Type &type,
    Output &output,
    std::gc_function<std::string (Type &)> &&target
) {
    // get inner

    Instance &inner {
        getInner(instance, output)
    };

    // set type

    size_t level {0};

    if (mode == LookupMode::global) {
        inner.lookupCheck(name, type, level);
    } else {
        inner.insert(name, type);
    }

    // render

    output.content(
        instance,
        [&, target = std::move(target), level](OutputContext &oc) {
            oc.endl();
            oc.os << inner.strReint("tmp");
            renderPath(oc.os, level);
            oc.os << " = " << target(type) << ";";
        }
    );
}

}
