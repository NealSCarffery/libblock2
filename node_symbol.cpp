#include "output.hpp"
#include "type.hpp"
#include "node.hpp"

void NodeSymbol::renderPath(std::ostream &os, size_t level) const {
    for (size_t i = 0; i < level; ++i) {
        os << "->parent";
    }

    if (name != "self") {
        os << "->" << name;
    }
}

NodeSymbol::NodeSymbol(std::string &&_name):
    name {std::move(_name)} {}

void NodeSymbol::buildProc(
    Instance &instance,
    Output &output
) {
    // gen type

    size_t level {0};

    instance.lookup(name, level);

    // render

    output.content(
        instance,
        [&, level](OutputContext &oc) {
            oc.endl();
            oc.os << instance.strCast("self");
            renderPath(oc.os, level);
            oc.os << ";";
        }
    );
}

Type &NodeSymbol::buildOut(
    Instance &instance,
    Output &output,
    std::function<std::string ()> &&target
) {
    // get type

    size_t level {0};

    Type &type {
        instance.lookup(name, level)
    };

    // render

    output.content(
        instance,
        [&, target = std::move(target), level](OutputContext &oc) {
            oc.endl();
            oc.os << target() << " = " << instance.strCast("self");
            renderPath(oc.os, level);
            oc.os << ";";
        }
    );

    // return

    return type;
}

void NodeSymbol::buildIn(
    Instance &instance, Type &type,
    Output &output,
    std::function<std::string ()> &&target
) {
    // set type

    instance.insert(name, type);

    // render

    output.content(
        instance,
        [&, target = std::move(target)](OutputContext &oc) {
            oc.endl();
            oc.os << instance.strCast("self");
            renderPath(oc.os, 0);
            oc.os << " = " << target() << ";";
        }
    );
}
