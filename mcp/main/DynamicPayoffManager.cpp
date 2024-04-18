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

  mGetRevision = reinterpret_cast<GetRevisionFun*>(GetProcAddress(hLibrary, "GetRevision"));
  if (!mGetRevision) throw std::runtime_error("Could not find GetRevision function");
}

DynamicPayoffInstance DynamicPayoffManager::createPayoff(TradeData const& tradeData) const {
  ++mNumCreated;
  return mCreatePayoff(tradeData);
}

std::string DynamicPayoffManager::getRevision() const {
  return mGetRevision();
}

int DynamicPayoffManager::numCreated() const {
  return mNumCreated;
}

DynamicPayoffManager::~DynamicPayoffManager() {
  if (mFreeLibrary) mFreeLibrary();
}
