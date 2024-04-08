#pragma once

#include "Payoff.h"
#include <functional>
#include <string_view>
#include <memory>

enum class TradeFieldType {
  Int, Double, Char256
};

struct TradeField {
  TradeFieldType type;
  size_t num;
  void const* data;
};

class Payoff {
public:
    Payoff(std::string_view filename);
    void test() const;
    
private:
    std::function<void(TradeField(*)())> mTestFun;
};
