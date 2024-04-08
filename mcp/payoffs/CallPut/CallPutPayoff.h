#pragma once

class TradeData;

class CallPutPayoff {
public:
  explicit CallPutPayoff(TradeData const& trade);

  void test() const;

private:
  double mStrike;
  int mExpiry;
};
