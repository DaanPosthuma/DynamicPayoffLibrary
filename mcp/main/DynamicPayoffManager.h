#pragma once

#include <functional>
#include <string_view>
#include <memory>
#include "payoffs/DynamicPayoffInstance.h"

class TradeData;

class DynamicPayoffDiagnostics {
public:
private:

};

class DynamicPayoffManager {
public:
  DynamicPayoffManager(std::string_view filename);
  DynamicPayoffManager(DynamicPayoffManager const&) = delete;
  DynamicPayoffManager(DynamicPayoffManager&&) = default;

  DynamicPayoffInstance createPayoff(TradeData const& tradeData) const;
  
  DynamicPayoffDiagnostics getDiagnostics() const;

  ~DynamicPayoffManager();

private:
  using CreatePayoffFun = DynamicPayoffInstance(TradeData const&);
  
  std::function<CreatePayoffFun> mCreatePayoff;
  std::function<void()> mFreeLibrary;
};
