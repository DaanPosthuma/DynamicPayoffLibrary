#pragma once

#include "TradeData/TradeData.h"
#include "serialization/serialization.h"
#include "CallPutPayoff.h"

extern "C" {
  
  __declspec(dllexport) void const* CreatePayoff(char const* data, size_t size) {

    std::vector<char> stream(data, data + size);
    auto const trade = serialization::deserialize<TradeData>(stream);
    auto payoff = new CallPutPayoff(trade);
    return payoff;
  }

  __declspec(dllexport) void UsePayoff(CallPutPayoff const* payoff) {
    payoff->test();
  }

  __declspec(dllexport) void DeletePayoff(CallPutPayoff const* payoff) {
    delete payoff;
  }

}
