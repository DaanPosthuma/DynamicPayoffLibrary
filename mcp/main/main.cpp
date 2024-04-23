#pragma once

#include "DynamicPayoffManagerCollection.h"
#include "TradeData/TradeData.h"
#include <fmt/printf.h>

class Observables {
public:
  virtual double getSpot(std::string const& currencyPair, int date) const = 0;
  virtual ~Observables() = default;

};

class TestObservables : public Observables {
public:
  double getSpot(std::string const& currencyPair, int date) const override {
    fmt::println("Getting spot for ccy pair {} and date {}", currencyPair, date);
    return 0.0;
  }
};

void EvaluateTrades(std::vector<TradeData> const& trades, DynmamicPayoffManagerCollection const& payoffManagers) {

  auto const observables = TestObservables();

  for (auto const& trade : trades) {
    auto const payoff = payoffManagers.createPayoffInstance(trade);
    payoff.test();
    payoff.evaluate(observables);
  }

}

int main() {

  try {

    TradeData trade0;
    trade0.setDouble("Strike", 1.3);
    trade0.setDate("ExpiryDate", 400);
    trade0.setString("CurrencyPair", "EURUSD");
    trade0.setString("PayoffId", "CallPutA");

    TradeData trade1;
    trade1.setDouble("Strike", 1.5);
    trade1.setDate("ExpiryDate", 500);
    trade1.setString("CurrencyPair", "EURUSD");
    trade1.setString("PayoffId", "CallPutA");

    TradeData trade2;
    trade2.setDouble("Strike", 1.5);
    trade2.setDate("ExpiryDate", 500);
    trade2.setString("CurrencyPair", "GBPUSD");
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
