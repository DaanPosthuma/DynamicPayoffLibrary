#pragma once

#include <string>
class TradeData;

class CallPutPayoff {
public:
  explicit CallPutPayoff(TradeData const& trade);
  void test() const;
  double evaluateSimpleEuropeanPayoff(double spot) const;
  std::string const& getCurrencyPair() const { return mCurrencyPair; }
  int getExpiryDate() const { return mExpiryDate;  }

private:
  double mStrike;
  int mExpiryDate;
  std::string mCurrencyPair;

};
