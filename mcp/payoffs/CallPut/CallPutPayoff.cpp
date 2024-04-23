#include "CallPutPayoff.h"
#include "TradeData/TradeData.h"
#include <iostream>

CallPutPayoff::CallPutPayoff(TradeData const& trade) : mStrike(trade.getDouble("Strike")), mExpiryDate(trade.getDate("ExpiryDate")), mCurrencyPair(trade.getString("CurrencyPair")) {}

void CallPutPayoff::test() const {
  std::cout << "I'm a Call Put payoff" << std::endl;
  std::cout << "Strike: " << mStrike << std::endl;
  std::cout << "Expiry date: " << mExpiryDate << std::endl;
  std::cout << "Currency pair: " << mCurrencyPair << std::endl;
}

double CallPutPayoff::evaluateSimpleEuropeanPayoff(double spot) const {
  return spot > mStrike ? spot - mStrike : 0.0;
}
