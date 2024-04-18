#pragma once

#include <functional>
#include <string_view>
#include <memory>
#include "payoffs/DynamicPayoffInstance.h"

class TradeData;

class DynamicPayoffManager {
public:
  DynamicPayoffManager(std::string_view filename);
  DynamicPayoffManager(DynamicPayoffManager const&) = delete;
  DynamicPayoffManager(DynamicPayoffManager&&) = default;

  DynamicPayoffInstance createPayoff(TradeData const& tradeData) const;
  std::string getRevision() const;
  
  int numCreated() const;

  ~DynamicPayoffManager();

private:
  using CreatePayoffFun = DynamicPayoffInstance(TradeData const&);
  using GetRevisionFun = std::string();
  
  std::function<CreatePayoffFun> mCreatePayoff;
  std::function<GetRevisionFun> mGetRevision;
  std::function<void()> mFreeLibrary;

  mutable int mNumCreated = 0;
};
