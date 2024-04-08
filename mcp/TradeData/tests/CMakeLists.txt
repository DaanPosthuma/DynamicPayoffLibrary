include(CTest)
include(Catch)

add_executable(TradeDataTests TradeDataTests.cpp)
target_link_libraries(TradeDataTests  PRIVATE Catch2::Catch2WithMain)

catch_discover_tests(TradeDataTests)
