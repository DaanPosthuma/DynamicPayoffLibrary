#pragma once

#include "DynamicPayoffManager.h"
#include "TradeData/TradeData.h"
#include <iostream>
#include <functional>
#include <stdexcept>
#include <stacktrace>
#include <unordered_map>
#include <windows.h>


DynamicPayoffManager::DynamicPayoffManager(std::string_view filename) {
  auto const hLibrary = LoadLibrary(filename.data());
  if (!hLibrary) throw std::runtime_error("Could not load the dynamic library");

  mCreatePayoff = reinterpret_cast<CreatePayoffFun*>(GetProcAddress(hLibrary, "CreatePayoff"));
  if (!mCreatePayoff) throw std::runtime_error("Could not find CreatePayoff function");

  mUsePayoff = reinterpret_cast<UsePayoffFun*>(GetProcAddress(hLibrary, "UsePayoff"));
  if (!mUsePayoff) throw std::runtime_error("Could not find UsePayoff function");

  mDeletePayoff = reinterpret_cast<DeletePayoffFun*>(GetProcAddress(hLibrary, "DeletePayoff"));
  if (!mDeletePayoff) throw std::runtime_error("Could not find DeletePayoff function");
}

DynamicPayoff DynamicPayoffManager::createPayoff(TradeData const& tradeData) const {
  std::vector<char> stream;
  serialization::serialize(tradeData, stream);
  return DynamicPayoff(mCreatePayoff(stream.data(), stream.size()));
}

void DynamicPayoffManager::usePayoff(DynamicPayoff const& payoff) const {
  mUsePayoff(payoff.mPtr);
}

void DynamicPayoffManager::deletePayoff(DynamicPayoff const& payoff) const {
  mDeletePayoff(payoff.mPtr);
}
