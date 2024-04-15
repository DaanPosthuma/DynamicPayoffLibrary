#pragma once

#include "DynamicPayoffManager.h"
#include "TradeData/TradeData.h"
#include <fmt/printf.h>

using namespace std::string_literals;

int main() {

  try {

    TradeData trade;
    trade.setDouble("Strike", 1.5);
    trade.setDate("Expiry", 500);
    trade.setString("DynamicPayoff", "../payoffs/CallPut/CallPut.dll"s);

    auto manager = DynamicPayoffManager("../payoffs/CallPut/CallPut.dll");
    fmt::println("Successfully constructed payoff");

    auto const payoff = manager.createPayoff(trade);
    fmt::println("Successfully created payoff");

    manager.usePayoff(payoff);
    fmt::println("Successfully used payoff");

    manager.deletePayoff(payoff);
    fmt::println("Successfully deleted payoff");
  }
  catch (std::exception const& ex) {
    fmt::println("Caught exception: {}", ex.what());
  }
  
}
