#include "TradeData.h"

TradeData::TradeData(
  std::unordered_map<std::string, std::vector<int>> dates,
  std::unordered_map<std::string, std::vector<double>> doubles,
  std::unordered_map<std::string, std::vector<std::string>> strings
) : mDates(std::move(dates)), mDoubles(std::move(doubles)), mStrings(std::move(strings)) {}

void TradeData::setDates(std::string const& key, std::vector<int> dates) noexcept {
  mDates[key] = std::move(dates);
}
void TradeData::setDoubles(std::string const& key, std::vector<double> doubles) noexcept {
  mDoubles[key] = std::move(doubles);
}
void TradeData::setStrings(std::string const& key, std::vector<std::string> strings) noexcept {
  mStrings[key] = std::move(strings);
}

void TradeData::setDate(std::string const& key, int date) noexcept {
  mDates[key] = { date };
}
void TradeData::setDouble(std::string const& key, double dbl) noexcept {
  mDoubles[key] = { dbl };
}
void TradeData::setString(std::string const& key, std::string str) noexcept {
  mStrings[key].clear();
  mStrings[key].emplace_back(std::move(str));
}

int TradeData::getDate(std::string const& key) const {
  return getDatesVec(key)[0];
}
double TradeData::getDouble(std::string const& key) const {
  return getDoublesVec(key)[0];
}
std::string TradeData::getString(std::string const& key) const {
  return getStringsVec(key)[0];
}

auto TradeData::getDates(std::string const& key) const {
  return getDatesVec(key);
}
auto TradeData::getDoubles(std::string const& key) const {
  return getDoublesVec(key);
}
auto TradeData::getStrings(std::string const& key) const {
  return getStringsVec(key);
}

std::vector<int> const& TradeData::getDatesVec(std::string const& key) const {
  if (!mDates.contains(key)) throw std::logic_error("Key '" + key + "' not found in dates");
  return mDates.at(key);
}

std::vector<double> const& TradeData::getDoublesVec(std::string const& key) const {
  if (!mDoubles.contains(key)) throw std::logic_error("Key '" + key + "' not found in doubles");
  return mDoubles.at(key);
}

std::vector<std::string> const& TradeData::getStringsVec(std::string const& key) const {
  if (!mStrings.contains(key)) throw std::logic_error("Key '" + key + "' not found in strings");
  return mStrings.at(key);
}
