#pragma once

#include "DynamicPayoffManagerCollection.h"
#include "TradeData/TradeData.h"
#include <fmt/printf.h>


void EvaluateTrades(std::vector<TradeData> const& trades, DynmamicPayoffManagerCollection const& payoffManagers) {
  
  for (auto const& trade : trades) {
    auto const payoff = payoffManagers.createPayoffInstance(trade);
    payoff.test();
  }
}

int main() {

  try {

    TradeData trade0;
    trade0.setDouble("Strike", 1.3);
    trade0.setDate("Expiry", 400);
    trade0.setString("PayoffId", "CallPut");

    TradeData trade1;
    trade1.setDouble("Strike", 1.5);
    trade1.setDate("Expiry", 500);
    trade1.setString("PayoffId", "CallPut");

    auto const payoffManagers = DynmamicPayoffManagerCollection({{"CallPut", "../payoffs/CallPut/CallPut.dll"}});

    fmt::println("");
    fmt::println("Dynamic Payoff Revisions: ");
    for (auto const& [payoffId, revision] : payoffManagers.getRevisions()) {

      fmt::println("{}: {}", payoffId, revision);
    }
    fmt::println("");

    EvaluateTrades({trade0, trade1}, payoffManagers);

    fmt::println("");
    fmt::println("Num created: ");
    for (auto const& [payoffId, numCreated] : payoffManagers.getNumCreated()) {

      fmt::println("{}: {}", payoffId, numCreated);
    }

  }
  catch (std::exception const& ex) {
    fmt::println("Caught exception: {}", ex.what());
  }
  
}
