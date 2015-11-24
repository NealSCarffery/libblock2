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

inline bool operator<(const Type &a, const Type &b) {
    return a.tuid() < b.tuid();
}

template <class T>
class TypeNative: public Type {
private:
    TypeNative() = default;

public:
    static TypeNative<T> &get();

    virtual std::string strDecl(const std::string &name) const;
};
using TypeNativeBool = TypeNative<bool>;
using TypeNativeInt = TypeNative<int64_t>;
using TypeNativeReal = TypeNative<double>;
using TypeNativeStr = TypeNative<std::string>;

class TypeClosure: public Type {
private:
    Instance &parent;
    NodeBlock &blocks;

    friend class NodeCall;

public:
    TypeClosure(Instance &_parent, NodeBlock &_blocks);

    virtual std::string strDecl(const std::string &name) const;
};

class Instance: public Type {
private:
    static void typeCheck(Type &type1, Type &type2);

    size_t last_position {0}; // TODO

    std::map<std::string, Type &> symbol_types;
    std::map<
        std::reference_wrapper<NodeBlock>,
        std::shared_ptr<TypeClosure>
    > closure_types;
    std::map<size_t, Instance &> callee_types;

    void renderStruct(OutputContext &oc) const;
    void renderFuncHead(OutputContext &oc) const;
    void renderFuncTail(OutputContext &oc) const;

    friend class Block;

public:
    Instance();

    std::string strFunc() const;
    std::string strStruct() const;
    std::string strCast(const std::string &name) const;

    std::string strLabel(size_t position) const;
    std::string strCalleeType(size_t position) const;
    std::string strCalleeName(size_t position) const;
    std::string strInner(size_t position) const;
    std::string strCallee(size_t position) const;

    bool in(Instance &instance) const;

    size_t addPosition();

    Type &at(const std::string &name);
    void insert(const std::string &name, Type &type);
    Type &lookup(const std::string &name, size_t &level);

    Type &addClosure(NodeBlock &blocks);
    void addCallee(size_t position, Instance &callee);

    virtual std::string strDecl(const std::string &name) const;
};
