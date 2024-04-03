#include "serialization.h"
#include <catch2/catch_test_macros.hpp>

namespace {
  struct X {
    explicit X(int x) : x(x) {}
    int x;
  };

  inline bool operator==(X const& lhs, X const& rhs) noexcept {
    return lhs.x == rhs.x;
  }

  inline std::ostream& operator<<(std::ostream& ostr, X const& x) noexcept {
    ostr << "X(" << x.x << ")";
    return ostr;
  }
}

namespace detail {
  template <>
  struct serializer<X> {
    static void serialize(X const& x, std::deque<char>& stream) {
      ::serialize(x.x, stream);
    }

    static X deserialize(std::deque<char>& stream) {
      return X(::deserialize<int>(stream));
    }
  };
}

namespace {

  using namespace std::string_literals;

  void round_trip(auto obj) {
    std::deque<char> stream;
    serialize(obj, stream);
    REQUIRE(deserialize<decltype(obj)>(stream) == obj);
  }

  TEST_CASE("int round trip") {
    round_trip(3);
  }

  TEST_CASE("double round trip") {
    round_trip(3.0);
  }

  TEST_CASE("string round trip") {
    round_trip("test"s);
  }

  TEST_CASE("non-trivial type round trip") {
    round_trip("test"s);
  }

  TEST_CASE("Custom object round trip") {
    round_trip(X(3));
  }

  TEST_CASE("empty vector round trip") {
    round_trip(std::vector<char>());
  }

  TEST_CASE("vector of trivial types round trip") {
    round_trip(std::vector{ 1,2,3 });
  }

  TEST_CASE("vector of strings round trip") {
    round_trip(std::vector{ "one"s, "two"s, "three"s });
  }

  TEST_CASE("vector of booleans round trip") {
    round_trip(std::vector{ true, false, true, true, false, false });
  }

  TEST_CASE("vector of vectors round trip") {
    round_trip(std::vector{ std::vector{ 1,2,3 }, std::vector{ 4,5 } });
  }

  TEST_CASE("unordered_map round trip") {
    round_trip(std::unordered_map<std::string, int>{ {"one"s, 1}, { "two"s, 2 }, { "three"s, 3 } });
  }

  TEST_CASE("map string to vector round trip") {
    round_trip(std::map<std::string, std::vector<int>>{{"one"s, std::vector{ 1,2,3 }}, { "two"s, std::vector{4,5} }, { "three"s, std::vector{6,7,8} } });
  }

  TEST_CASE("multiple objects") {
    std::deque<char> stream;

    for (int i = 0; i != 10; ++i) {
      serialize(1, stream);
      serialize(5.0, stream);
      serialize(std::vector{ 1,2,3 }, stream);
      serialize("test"s, stream);
    }
    
    for (int i = 0; i != 10; ++i) {
      REQUIRE(deserialize<int>(stream) == 1);
      REQUIRE(deserialize<double>(stream) == 5.0);
      REQUIRE(deserialize<std::vector<int>>(stream) == std::vector{ 1,2,3 });
      REQUIRE(deserialize<std::string>(stream) == "test"s);
    }

  }

  template <class T>
  auto f() {
    return "default"s;
  }

  template<typename T>
  concept map_type =
    std::same_as<T, std::map<typename T::key_type, typename T::mapped_type, typename T::key_compare, typename T::allocator_type>> ||
    std::same_as<T, std::unordered_map<typename T::key_type, typename T::mapped_type, typename T::hasher, typename T::key_equal, typename T::allocator_type>>;

  template <map_type T>
  auto f() {
    return "map"s;
  }

  TEST_CASE("test test") {
    REQUIRE(f<int>() == "default");
    REQUIRE(f<std::map<int, std::string>>() == "map");
  }

}
