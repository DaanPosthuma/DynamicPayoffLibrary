#pragma once

class Observables {
public:
  virtual double getSpot(std::string const& currencyPair, int date) const = 0;
  virtual ~Observables() = default;
};

template <class T>
concept SimpleEuropeanPayoff = requires(T a, double spot)
{
  { a.test() };
  { a.evaluateSimpleEuropeanPayoff(spot) } -> std::same_as<double>;
  { a.getCurrencyPair() } -> std::same_as<std::string const&>;
  { a.getExpiryDate() } -> std::same_as<int>;
};

template <SimpleEuropeanPayoff Payoff>
class SimpleEuropeanPayoffAdapter : private Payoff {
public:
  explicit SimpleEuropeanPayoffAdapter(TradeData const& trade) : Payoff(trade) {}

  using Payoff::test;

  void evaluate(Observables const& observables) const {
    auto spot = observables.getSpot(Payoff::getCurrencyPair(), Payoff::getExpiryDate());
    auto payoffAtExpiry = Payoff::evaluateSimpleEuropeanPayoff(spot);
  }

};
