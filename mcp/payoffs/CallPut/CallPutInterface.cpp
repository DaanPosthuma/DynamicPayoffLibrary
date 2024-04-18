#pragma once

#include "TradeData/TradeData.h"
#include "payoffs/DynamicPayoffInstance.h"
#include "CallPutPayoff.h"
  
__declspec(dllexport) DynamicPayoffInstance CreatePayoff(TradeData const& trade) {
  return DynamicPayoffInstance(CallPutPayoff(trade));
}
