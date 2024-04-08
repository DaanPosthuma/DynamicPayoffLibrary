#pragma once

#include "serialization/serialization.h"
#include <unordered_map>
#include <vector>
#include <string>


class TradeData {
public:
  TradeData() = default;
  TradeData(std::unordered_map<std::string, std::vector<int>> datess, std::unordered_map<std::string, std::vector<double>> doubless) : mDatess(datess), mDoubless(doubless) {}

  void setDate(std::string const& key, int date) noexcept {
    mDatess[key] = { date };
  }

  void setDates(std::string const& key, std::vector<int> dates) noexcept {
    mDatess[key] = std::move(dates);
  }

  void setDouble(std::string const& key, double dbl) noexcept {
    mDoubless[key] = { dbl };
  }

  void setDoubles(std::string const& key, std::vector<double> doubles) noexcept {
    mDoubless[key] = std::move(doubles);
  }

  auto getDate(std::string const& key) const {
    return mDatess.at(key)[0];
  }

  auto getDates(std::string const& key) const {
    return mDatess.at(key);
  }

  auto getDouble(std::string const& key) const {
    return mDoubless.at(key)[0];
  }

  auto getDoubles(std::string const& key) const {
    return mDoubless.at(key);
  }



private:

  auto tie() const noexcept {
    return std::tie(mDatess, mDoubless);
  }

  friend struct serialization::detail::serializer<TradeData>;
  friend bool operator==(TradeData const& lhs, TradeData const& rhs) noexcept;

  std::unordered_map<std::string, std::vector<int>> mDatess;
  std::unordered_map<std::string, std::vector<double>> mDoubless;
};

inline bool operator==(TradeData const& lhs, TradeData const& rhs) noexcept {
  return lhs.tie() == rhs.tie();
}


namespace serialization::detail {
  template <>
  struct serializer<TradeData> {
    static void serialize(TradeData const& td, std::vector<char>& stream) {
      serialization::serialize(td.mDatess, stream);
      serialization::serialize(td.mDoubless, stream);
    }

    static TradeData deserialize(std::vector<char>& stream) {
      auto datess = serialization::deserialize<decltype(TradeData::mDatess)>(stream);
      auto doubless = serialization::deserialize<decltype(TradeData::mDoubless)>(stream);
      return TradeData{ datess, doubless };
    }
  };
}

