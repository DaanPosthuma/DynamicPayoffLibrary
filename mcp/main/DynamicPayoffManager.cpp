#pragma once

#include "DynamicPayoffManager.h"
#include "TradeData/TradeData.h"
#include <stdexcept>
#include <unordered_map>
#include <fmt/printf.h>
#include <windows.h>

DynamicPayoffManager::DynamicPayoffManager(std::string_view filename) {
  auto const hLibrary = LoadLibrary(filename.data());
  if (!hLibrary) throw std::runtime_error("Could not load the dynamic library");

  mFreeLibrary = [hLibrary]() { 
    if (!FreeLibrary(hLibrary)) fmt::println("Warning! Could not unload payoff library");
  };

  mCreatePayoff = reinterpret_cast<CreatePayoffFun*>(GetProcAddress(hLibrary, "CreatePayoff"));
  if (!mCreatePayoff) throw std::runtime_error("Could not find CreatePayoff function");
}

DynamicPayoffInstance DynamicPayoffManager::createPayoff(TradeData const& tradeData) const {
  return mCreatePayoff(tradeData);
}

DynamicPayoffDiagnostics DynamicPayoffManager::getDiagnostics() const {
  return {};
}

DynamicPayoffManager::~DynamicPayoffManager() {
  if (mFreeLibrary) mFreeLibrary();
}
