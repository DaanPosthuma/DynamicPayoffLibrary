#pragma once

#include "Payoff.h"
#include <functional>
#include <string_view>
#include <memory>

class Payoff {
public:
    Payoff(std::string_view filename);
    int test() const;
    
private:
    std::function<int(void(*)())> mTestFun;
};
