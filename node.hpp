#pragma once

#include "type.hpp"

class Output;

class Node {
protected:
    uintptr_t nuid() const;
    std::string nuidOut() const;
    std::string nuidIn() const;

public:
    virtual void buildProc(Instance &instance, Output &output) = 0;
    virtual Type &buildOut(Instance &instance, Output &output) = 0;
    virtual void buildIn(Instance &instance, Type &type, Output &output) = 0;
};

template <class T>
class NodeLiteral: public Node {
private:
    T value;

    void renderValue(std::ostream &os) const;

public:
    inline NodeLiteral(T &&_value):
        value {std::move(_value)} {}

    virtual void buildProc(Instance &instance, Output &output);
    virtual Type &buildOut(Instance &instance, Output &output);
    virtual void buildIn(Instance &instance, Type &type, Output &output);
};
using NodeLiteralBool = NodeLiteral<bool>;
using NodeLiteralInt = NodeLiteral<int64_t>;
using NodeLiteralReal = NodeLiteral<double>;
using NodeLiteralStr = NodeLiteral<std::string>;

class NodeSymbol: public Node {
private:
    std::vector<std::string> path;
    std::string name;

    size_t level {0};

    void renderPath(std::ostream &os) const;

public:
    inline NodeSymbol(std::vector<std::string> &&_path):
        path {std::move(_path)},
        name {path.back()} {
            path.pop_back();
        }

    virtual void buildProc(Instance &instance, Output &output);
    virtual Type &buildOut(Instance &instance, Output &output);
    virtual void buildIn(Instance &instance, Type &type, Output &output);
};

class NodeCall: public Node {
private:
    std::unique_ptr<Node> callee;
    std::vector<std::unique_ptr<Node>> args;

    void build(
        Instance &instance, Output &output,
        std::function<void (Instance &)> &&before,
        std::function<void (Instance &)> &&after
    );

public:
    template <class... Args>
    inline NodeCall(Node *_callee, Args... _args):
        callee {_callee} {
            Node *init[] {_args...};

            args.reserve(sizeof...(_args));
            for (Node *i: init) {
                args.push_back(std::unique_ptr<Node> {i});
            }
        }

    virtual void buildProc(Instance &instance, Output &output);
    virtual Type &buildOut(Instance &instance, Output &output);
    virtual void buildIn(Instance &instance, Type &type, Output &output);
};

enum class SymbolMode {
    in, out, var, special
};

class Block: public Node {
private:
    // TODO: multiple signature (overloading and SFINAE)
    std::vector<std::pair<std::string, SymbolMode>> params;

    std::vector<std::unique_ptr<Instance>> instances;

protected:
    void inArg(
        Instance &caller, Instance &instance,
        size_t index, std::unique_ptr<Node> &arg,
        Output &output
    );
    Instance &matchInstance(
        std::unique_ptr<Instance> &&instance,
        Output &output
    );
    void outArg(
        Instance &caller, Instance &instance,
        size_t index, std::unique_ptr<Node> &arg,
        Output &output
    );

    virtual void inSpecialArg(
        Instance &caller, Instance &instance,
        size_t index, std::unique_ptr<Node> &arg,
        Output &output
    );
    virtual void buildContent(Instance &instance, Output &output) = 0;
    virtual void outSpecialArg(
        Instance &caller, Instance &instance,
        size_t index, std::unique_ptr<Node> &arg,
        Output &output
    );

public:
    inline Block(std::vector<std::pair<std::string, SymbolMode>> &&_params):
        params {std::move(_params)} {}

    void makeBoot(
        Output &output,
        std::function<void (Instance &)> &&before,
        std::function<void (Instance &)> &&after
    );
    void makeCall(
        Instance &parent, Instance &caller,
        std::vector<std::unique_ptr<Node>> &args,
        Output &output,
        std::function<void (Instance &)> &&before,
        std::function<void (Instance &)> &&after
    );

    // as node
    virtual void buildProc(Instance &instance, Output &output);
    virtual Type &buildOut(Instance &instance, Output &output);
    virtual void buildIn(Instance &instance, Type &type, Output &output);
};

class BlockBuiltin: public Block {
private:
    std::string name;

protected:
    // as block
    virtual void buildContent(Instance &instance, Output &output);

public:
    inline BlockBuiltin(
        std::vector<std::pair<std::string, SymbolMode>> &&_params,
        std::string &&_name
    ):
        Block {std::move(_params)},
        name {std::move(_name)} {
            builtins().insert({name, *this});
        }

    static std::map<std::string, BlockBuiltin &> &builtins();
    static void applyBuiltin(Instance &instance);
};

class BlockUser: public Block {
private:
    std::unique_ptr<Node> ast;

protected:
    // as block
    virtual void buildContent(Instance &instance, Output &output);

public:
    inline BlockUser(
        std::vector<std::pair<std::string, SymbolMode>> &&_params,
        Node *_ast
    ):
        Block {std::move(_params)},
        ast {_ast} {}
};
