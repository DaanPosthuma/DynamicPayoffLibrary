#pragma once

#include "DynamicPayoffManager.h"
#include "TradeData/TradeData.h"
#include <fmt/printf.h>

using namespace std::string_literals;

class DynmamicPayoffCollection;

class DynmamicPayoffCollection {
public:
  DynmamicPayoffCollection(std::initializer_list<std::pair<std::string, std::string>> idToPath) {
    for (auto const& [id, path] : idToPath) {
      mPayoffManagers.emplace(id, DynamicPayoffManager(path));
    }
  }

  auto create(TradeData const& tradeData) const {

    class PayoffHolder {
    public:

      PayoffHolder(DynamicPayoff&& payoff, DynamicPayoffManager const& manager) : payoff(std::move(payoff)), manager(manager) {}

      void use() const {
        manager.usePayoff(payoff);
      }

      ~PayoffHolder() {
        manager.deletePayoff(payoff);
      }

    private:
      DynamicPayoff payoff;
      DynamicPayoffManager const& manager;
    };

    auto const payoffId = tradeData.getString("PayoffId");
    if (!mPayoffManagers.contains(payoffId)) throw std::logic_error("No manager found for PayoffId '" + payoffId + "'");
    auto const& manager = mPayoffManagers.at(payoffId);
    return PayoffHolder(manager.createPayoff(tradeData), manager);
  }

private:
  std::unordered_map<std::string, DynamicPayoffManager> mPayoffManagers;

};

void EvaluateTrades(std::vector<TradeData> const& trades, DynmamicPayoffCollection const& payoffCollection) {
  
  for (auto const& trade : trades) {
    auto const payoff = payoffCollection.create(trade);
    payoff.use();
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

    auto const payoffs = DynmamicPayoffCollection({{"CallPut"s, "../payoffs/CallPut/CallPut.dll"s}});

    EvaluateTrades({trade0, trade1}, payoffs);

    //auto manager = DynamicPayoffManager("../payoffs/CallPut/CallPut.dll");
    //fmt::println("Successfully constructed payoff");

    //for (auto const& trade : { trade0, trade1 }) {
    //  auto const payoff = manager.createPayoff(trade);
    //  fmt::println("Successfully created payoff");

    //  manager.usePayoff(payoff);
    //  fmt::println("Successfully used payoff");

    //  manager.deletePayoff(payoff);
    //  fmt::println("Successfully deleted payoff");

    //  fmt::println("");
    //}

  }
  catch (std::exception const& ex) {
    fmt::println("Caught exception: {}", ex.what());
  }
  
}
