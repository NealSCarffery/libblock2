#pragma once

#ifndef NO_STD_LIB
#include <memory>
#include <vector>
#include <map>
#include <sstream>
#endif

class Instance;

class OutputContext {
private:
    std::ostringstream header;
    std::ostringstream content;

    friend class Output;
};

class Output {
private:
    std::vector<std::unique_ptr<OutputContext>> members;
    std::map<uintptr_t, OutputContext &> map;

public:
    std::ostream &osHeader(Instance &instance);
    std::ostream &osContent(Instance &instance);
    void insert(Instance &instance);

    void getHeader(std::ostream &os) const;
    void getContent(std::ostream &os) const;
};
