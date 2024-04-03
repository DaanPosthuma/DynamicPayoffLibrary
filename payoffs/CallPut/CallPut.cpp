#pragma once

#include <iostream>
#include <span>
#include <cassert>

extern "C" {
  
  /*class CallPutPayoff {
  public:
    CallPutPayoff() {}

    void EvaluatePayoff(Market const& market) const {

    }

  private:

    enum class CallPutForward {
      Call, Put, Forward
    };

    double mStrike;
    CallPutForward mType;
  };*/

  enum class TradeFieldType {
    Int, Double, Char256
  };

  struct TradeField {
    TradeFieldType type;
    size_t num;
    void const* data;
  };

  __declspec(dllexport) int Initialize(TradeField(*getTradeField)()) {

    auto getInts = [&]() {
      auto tfs = getTradeField();
      assert(tfs.type == TradeFieldType::Int);
      return std::span<const int>(static_cast<int const*>(tfs.data), tfs.num);

    };

    std::cout << "I'm a vanilla call/put" << std::endl;
    for (int x : getInts()) {
      std::cout << x << std::endl;
    }
    

    //std::cout << "CallPut stack trace: " << std::endl;
    //std::cout << std::stacktrace::current() << std::endl;
    //std::cout << "CallPut stack trace end" << std::endl;

    //auto spot = getSpot();
    //std::cout << "spot is: " << spot << std::endl;
    return 0;
  }

}
