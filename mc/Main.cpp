#pragma once

#include "Payoff.h"
#include <iostream>
#include <deque>
#include <array>
#include <fmt/printf.h>
//#include "serialization.h"

class TradeData {
public:

  
  void serialize(std::vector<char>& container) const {

  }

private:
  std::unordered_map<std::string, std::vector<int>> mDatess;
  std::unordered_map<std::string, std::vector<double>> mDoubless;
};




int main() {

  try {

    auto payoff = Payoff("C:/dev/VS/MonteCarloPayoffs/out/build/x64-debug/payoffs/CallPut/CallPut.dll");

    fmt::println("Successfully constructed payoff");

    payoff.test();

    fmt::println("Successfully called test");
  }
  catch (std::exception const& ex) {
    fmt::println("Caught exception: {}", ex.what());
  }
  
}
