#pragma once

#include "Payoff.h"
#include <iostream>

int main() {

  try {

    auto payoff = Payoff("C:/dev/VS/MonteCarloPayoffs/out/build/x64-debug/payoffs/CallPut/CallPut.dll");

    std::cout << "Successfully constructed payoff" << std::endl;

    payoff.test();

    std::cout << "Successfully called test" << std::endl;
  }
  catch (std::exception const& ex) {
    std::cout << "Caught exception: " << ex.what() << std::endl;
  }
  
}
