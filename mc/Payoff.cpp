#pragma once

#include "Payoff.h"
#include <iostream>
#include <functional>
#include <stdexcept>
#include <windows.h>

namespace {

  void callback() {
    std::cout << "Successfully called callback" << std::endl;
  }

}

Payoff::Payoff(std::string_view filename) {
  auto const hLibrary = LoadLibrary(filename.data());
  if (!hLibrary) throw std::runtime_error("Could not load the dynamic library");

  using TestFun = int(*)(void(*callback)());
  mTestFun = (TestFun)GetProcAddress(hLibrary, "test");
  if (!mTestFun) throw std::runtime_error("Could not find test function");
  
}

int Payoff::test() const {
  return mTestFun(callback);
}

//
//Payoff LoadPayoff(std::string_view filename) {
//
//  return Payoff(new Payoff::Impl(filename));
//
//  //auto payoff = Payoff(new Payoff::Impl(filename));
//  //
//  //return std::expected<Payoff, std::string>(std::move(payoff));
//  
//  //if (!hGetProcIDDLL) {
//  //  std::cout << "could not load the dynamic library" << std::endl;
//  //  return EXIT_FAILURE;
//  //}
//
//  //using TestFun = int(*)();
//
//  //// resolve function address here
//  //auto funci = (TestFun)GetProcAddress(hGetProcIDDLL, "test");
//  //if (!funci) {
//  //  std::cout << "could not locate the function" << std::endl;
//  //  return EXIT_FAILURE;
//  //}
//
//  //std::cout << "funci() returned " << funci() << std::endl;
//
//  //return EXIT_SUCCESS;
//
//  //return std::unexpected("test");
//}
