#include "TradeData/TradeData.h"
#include <catch2/catch_test_macros.hpp>

namespace {

  using namespace std::string_literals;

  namespace {

    void round_trip(auto obj) {
      std::vector<char> stream;
      serialization::serialize(obj, stream);
      REQUIRE(serialization::deserialize<decltype(obj)>(stream) == obj);
    }

    TEST_CASE("Trade round trip") {

      TradeData trade;
      trade.setDouble("strike", 1.5);
      trade.setDate("expiry", 500);

      round_trip(trade);

    }

  }
}
