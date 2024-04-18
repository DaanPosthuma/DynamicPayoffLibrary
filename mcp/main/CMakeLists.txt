find_package(fmt CONFIG REQUIRED)

add_executable (MonteCarlo main.cpp DynamicPayoffManager.cpp DynamicPayoffManagerCollection.cpp)

target_link_libraries(MonteCarlo PRIVATE common fmt::fmt TradeData)

