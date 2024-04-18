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
  );

  
  void setDates(std::string const& key, std::vector<int> dates) noexcept;
  void setDoubles(std::string const& key, std::vector<double> doubles) noexcept;
  void setStrings(std::string const& key, std::vector<std::string> strings) noexcept;

  void setDate(std::string const& key, int date) noexcept;
  void setDouble(std::string const& key, double dbl) noexcept;
  void setString(std::string const& key, std::string str) noexcept;

  int getDate(std::string const& key) const;
  double getDouble(std::string const& key) const;
  std::string getString(std::string const& key) const;

  auto getDates(std::string const& key) const;
  auto getDoubles(std::string const& key) const;
  auto getStrings(std::string const& key) const;

private:

  std::vector<int> const& getDatesVec(std::string const& key) const;
  std::vector<double> const& getDoublesVec(std::string const& key) const;
  std::vector<std::string> const& getStringsVec(std::string const& key) const;

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
