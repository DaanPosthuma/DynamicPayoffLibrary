#pragma once

#include "TradeData/TradeData.h"
#include "payoffs/DynamicPayoffInstance.h"
#include "payoffs/SimpleEuropeanPayoffAdapter.h"
#include "CallPutPayoff.h"
  
__declspec(dllexport) DynamicPayoffInstance CreatePayoff(TradeData const& trade) {
  return DynamicPayoffInstance(SimpleEuropeanPayoffAdapter<CallPutPayoff>(trade));
}

__declspec(dllexport) std::string GetRevision() {
  return GIT_COMMIT_HASH;
}
