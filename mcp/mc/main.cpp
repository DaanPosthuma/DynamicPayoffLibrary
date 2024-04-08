#pragma once

#include "DynamicPayoffManager.h"
#include "TradeData/TradeData.h"
#include <fmt/printf.h>

int main() {

  try {

    TradeData trade;
    trade.setDouble("strike", 1.5);
    trade.setDate("expiry", 500);

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
