#include "exception.hpp"
#include "output.hpp"
#include "type.hpp"
#include "node.hpp"
#include "block.hpp"

void NodeBlock::buildProc(
    Instance &,
    Output &
) {
    // nothing
}

Type &NodeBlock::buildOut(
    Instance &instance,
    Output &output,
    std::function<std::string ()> &&target
) {
    // get type

    Type &type {instance.addClosure(*this)};

    // render

    output.content(
        instance,
        [&, target = std::move(target)](OutputContext &oc) {
            oc.endl();
            oc.os << target() << " = " << instance.strCast("self") << ";";
        }
    );

    // return

    return type;
}

void NodeBlock::buildIn(
    Instance &, Type &,
    Output &,
    std::function<std::string ()> &&
) {
    throw ErrorWriteNotAllowed {};
}
