find_package(fmt CONFIG REQUIRED)

add_executable (MonteCarlo Main.cpp Payoff.cpp)

target_link_libraries(MonteCarlo PRIVATE fmt::fmt)

