#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>


class TradeData {
public:
  TradeData() = default;
  TradeData(
    std::unordered_map<std::string, std::vector<int>> dates, 
    std::unordered_map<std::string, std::vector<double>> doubles,
    std::unordered_map<std::string, std::vector<std::string>> strings
    ) : mDates(std::move(dates)), mDoubles(std::move(doubles)), mStrings(std::move(strings)) {}

  
  void setDates(std::string const& key, std::vector<int> dates) noexcept {
    mDates[key] = std::move(dates);
  }
  void setDoubles(std::string const& key, std::vector<double> doubles) noexcept {
    mDoubles[key] = std::move(doubles);
  }
  void setStrings(std::string const& key, std::vector<std::string> strings) noexcept {
    mStrings[key] = std::move(strings);
  }

  void setDate(std::string const& key, int date) noexcept {
    mDates[key] = { date };
  }
  void setDouble(std::string const& key, double dbl) noexcept {
    mDoubles[key] = { dbl };
  }
  void setString(std::string const& key, std::string str) noexcept {
    mStrings[key].clear();
    mStrings[key].emplace_back(std::move(str));
  }

  auto getDate(std::string const& key) const {
    return getDatesVec(key)[0];
  }
  auto getDouble(std::string const& key) const {
    return getDoublesVec(key)[0];
  }
  auto getString(std::string const& key) const {
    return getStringsVec(key)[0];
  }

  auto getDates(std::string const& key) const {
    return getDatesVec(key);
  }
  auto getDoubles(std::string const& key) const {
    return getDoublesVec(key);
  }
  auto getStrings(std::string const& key) const {
    return getStringsVec(key);
  }

private:

  std::vector<int> const& getDatesVec(std::string const& key) const {
    if (!mDates.contains(key)) throw std::logic_error("Key '" + key + "' not found in dates");
    return mDates.at(key);
  }

  std::vector<double> const& getDoublesVec(std::string const& key) const {
    if (!mDoubles.contains(key)) throw std::logic_error("Key '" + key + "' not found in doubles");
    return mDoubles.at(key);
  }

  std::vector<std::string> const& getStringsVec(std::string const& key) const {
    if (!mStrings.contains(key)) throw std::logic_error("Key '" + key + "' not found in strings");
    return mStrings.at(key);
  }

  auto tie() const noexcept {
    return std::tie(mDates, mDoubles);
  }

  friend bool operator==(TradeData const& lhs, TradeData const& rhs) noexcept;

  std::unordered_map<std::string, std::vector<int>> mDates;
  std::unordered_map<std::string, std::vector<double>> mDoubles;
  std::unordered_map<std::string, std::vector<std::string>> mStrings;

};

inline bool operator==(TradeData const& lhs, TradeData const& rhs) noexcept {
  return lhs.tie() == rhs.tie();
}
