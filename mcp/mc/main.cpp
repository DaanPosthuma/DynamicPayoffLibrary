#pragma once

#include "Payoff.h"
#include <iostream>
#include <deque>
#include <array>
#include <fmt/printf.h>
#include "serialization/serialization.h"

class TradeData {
public:
  TradeData() = default;
  TradeData(std::unordered_map<std::string, std::vector<int>> datess, std::unordered_map<std::string, std::vector<double>> doubless) : mDatess(datess), mDoubless(doubless) {}

  void setDate(std::string const& key, int date) noexcept {
    mDatess[key] = {date};
  }

  void setDates(std::string const& key, std::vector<int> dates) noexcept {
    mDatess[key] = std::move(dates);
  }

  void setDouble(std::string const& key, double dbl) noexcept {
    mDoubless[key] = {dbl};
  }

  void setDoubles(std::string const& key, std::vector<double> doubles) noexcept {
    mDoubless[key] = std::move(doubles);
  }

private:

  friend struct detail::serializer<TradeData>;

  std::unordered_map<std::string, std::vector<int>> mDatess;
  std::unordered_map<std::string, std::vector<double>> mDoubless;
};

namespace detail {
  template <>
  struct serializer<TradeData> {
    static void serialize(TradeData const& td, std::deque<char>& stream) {
      ::serialize(td.mDatess, stream);
      ::serialize(td.mDoubless, stream);
    }

    static TradeData deserialize(std::deque<char>& stream) {
      auto datess = ::deserialize<decltype(TradeData::mDatess)>(stream);
      auto doubless = ::deserialize<decltype(TradeData::mDoubless)>(stream);
      return TradeData{datess, doubless};
    }
  };
}




int main() {

  try {

    TradeData trade;
    trade.setDouble("strike", 1.5);
    trade.setDate("expiry", 500);

    std::deque<char> stream;
    serialize(trade, stream);

    auto tradeCopy = deserialize<TradeData>(stream);



    auto payoff = Payoff("C:/dev/VS/MonteCarloPayoffs/out/build/x64-debug/payoffs/CallPut/CallPut.dll");

    fmt::println("Successfully constructed payoff");

    payoff.test();

    fmt::println("Successfully called test");
  }
  catch (std::exception const& ex) {
    fmt::println("Caught exception: {}", ex.what());
  }
  
}
