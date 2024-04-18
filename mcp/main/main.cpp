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
    trade0.setString("PayoffId", "CallPutA");

    TradeData trade1;
    trade1.setDouble("Strike", 1.5);
    trade1.setDate("Expiry", 500);
    trade1.setString("PayoffId", "CallPutA");

    TradeData trade2;
    trade2.setDouble("Strike", 1.5);
    trade2.setDate("Expiry", 500);
    trade2.setString("PayoffId", "CallPutB");

    auto const payoffManagers = DynmamicPayoffManagerCollection({ {"CallPutA", "../payoffs/CallPut/CallPut.dll"} ,
                                                                  {"CallPutB", "../payoffs/CallPut/CallPut.dll"} });

    fmt::println("");
    fmt::println("Application revision: {}", GIT_COMMIT_HASH);
    fmt::println("Dynamic payoff revisions: ");
    for (auto const& [payoffId, revision] : payoffManagers.getRevisions()) {
      fmt::println("{}: {}", payoffId, revision);
    }
    fmt::println("");

    EvaluateTrades({trade0, trade1, trade2}, payoffManagers);

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
