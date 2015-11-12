#pragma once

#include "include.hpp"

class Output;
class OutputContext;
class Instance;
class NodeBlock;
class NodeCall;
class Block;

class Type {
public:
    uintptr_t tuid() const;

    Instance &prepareLookup();

    virtual std::string strDecl(const std::string &name) const = 0;
};

inline bool operator==(const Type &a, const Type &b) {
    return a.tuid() == b.tuid();
}

inline bool operator!=(const Type &a, const Type &b) {
    return !(a == b);
}

template <class T>
class TypeNative: public Type {
public:
    virtual std::string strDecl(const std::string &name) const;
};

class TypeClosure: public Type {
private:
    Instance &parent;
    NodeBlock &blocks;

public:
    TypeClosure(Instance &_parent, NodeBlock &_blocks);

    void call(
        Output &output,
        std::function<void (Instance &, Block &, Instance &)> &&before,
        std::function<void (Instance &, Block &)> &&after
    );

    virtual std::string strDecl(const std::string &name) const;
};

class Instance: public Type {
private:
    std::map<std::string, Type &> symbol_types;
    std::map<uintptr_t, std::shared_ptr<TypeClosure>> closure_types;
    std::map<uintptr_t, Instance &> callee_types;

    void renderStruct(OutputContext &oc) const;
    void renderFuncHead(OutputContext &oc) const;
    void renderFuncTail(OutputContext &oc) const;

    friend class Block;

public:
    std::string strFunc() const;
    std::string strStruct() const;
    std::string strCast(const std::string &name) const;

    std::string strLabel(NodeCall &call) const;
    std::string strCalleeType(NodeCall &call) const;
    std::string strCalleeName(NodeCall &call) const;
    std::string strInner(NodeCall &call) const;
    std::string strCallee(NodeCall &call) const;

    void check(Type &type1, Type &type2);
    Type &at(const std::string &name);
    void insert(const std::string &name, Type &type);
    Type &lookup(const std::string &name, size_t &level);

    Type &addClosure(NodeBlock &blocks);
    void addCallee(NodeCall &call, Instance &callee);

    virtual std::string strDecl(const std::string &name) const;
};
