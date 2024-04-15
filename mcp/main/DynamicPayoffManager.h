#pragma once

#include <functional>
#include <string_view>
#include <memory>

class TradeData;
class DynamicPayoffManager;

class DynamicPayoff {
public:
private:
  DynamicPayoff(void const* ptr) : mPtr(ptr) {}
  friend class DynamicPayoffManager;

  void const* mPtr;
};

class DynamicPayoffManager {
public:
  DynamicPayoffManager(std::string_view filename);
  DynamicPayoffManager(DynamicPayoffManager const&) = delete;
  DynamicPayoffManager(DynamicPayoffManager&&) = default;

  DynamicPayoff createPayoff(TradeData const& tradeData) const;
  void usePayoff(DynamicPayoff const& payoff) const;
  void deletePayoff(DynamicPayoff const& payoff) const;

  ~DynamicPayoffManager();

private:
  using CreatePayoffFun = void const* (char const*, size_t);
  using UsePayoffFun = void(void const*);
  using DeletePayoffFun = void(void const*);

  std::function<CreatePayoffFun> mCreatePayoff;
  std::function<UsePayoffFun> mUsePayoff;
  std::function<DeletePayoffFun> mDeletePayoff;
  std::function<void()> mFreeLibrary;
};
