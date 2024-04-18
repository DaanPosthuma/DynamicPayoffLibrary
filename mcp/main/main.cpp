#pragma once

#include "DynamicPayoffManagerCollection.h"
#include "TradeData/TradeData.h"
#include <fmt/printf.h>


void EvaluateTrades(std::vector<TradeData> const& trades, DynmamicPayoffManagerCollection const& payoffCollection) {
  
  for (auto const& trade : trades) {
    auto const payoff = payoffCollection.create(trade);
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

    auto const payoffs = DynmamicPayoffManagerCollection({{"CallPut", "../payoffs/CallPut/CallPut.dll"}});

    EvaluateTrades({trade0, trade1}, payoffs);

    auto diagnostics = payoffs.getDiagnostics();
    
    fmt::println("");
    fmt::println("Diagnostics: ");
    for (auto const& [payoffId, diagnostics] : diagnostics) {
      
      fmt::println("PayoffId: {}", payoffId);
    }

  }
  catch (std::exception const& ex) {
    fmt::println("Caught exception: {}", ex.what());
  }
  
}
