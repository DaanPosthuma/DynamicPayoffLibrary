#pragma once

#include "Payoff.h"
#include <iostream>
#include <functional>
#include <stdexcept>
#include <stacktrace>
#include <unordered_map>
#include <windows.h>

namespace {
  TradeField getTradeField() {
    static const auto nums = std::vector<int>{ 1,2,3,4,5 };
    return {TradeFieldType::Int, nums.size(), nums.data()};
  }
}

Payoff::Payoff(std::string_view filename) {
  auto const hLibrary = LoadLibrary(filename.data());
  if (!hLibrary) throw std::runtime_error("Could not load the dynamic library");

  using TestFun = void(*)(TradeField(*)());
  mTestFun = (TestFun)GetProcAddress(hLibrary, "Initialize");
  if (!mTestFun) throw std::runtime_error("Could not find Initialize function");
  
}

void Payoff::test() const {
  mTestFun(getTradeField);
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
