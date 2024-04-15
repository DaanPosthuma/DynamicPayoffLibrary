#include "CallPutPayoff.h"
#include "TradeData/TradeData.h"
#include <iostream>

CallPutPayoff::CallPutPayoff(TradeData const& trade) : mStrike(trade.getDouble("Strike")), mExpiry(trade.getDate("Expiry")) {}

void CallPutPayoff::test() const {
  std::cout << "I'm a Call Put payoff" << std::endl;
  std::cout << "Trade strike: " << mStrike << std::endl;
  std::cout << "Trade expiry: " << mExpiry << std::endl;
}
