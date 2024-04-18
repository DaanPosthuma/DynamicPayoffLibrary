#pragma once

#include <unordered_map>
#include <string>
#include "DynamicPayoffManager.h"

class DynmamicPayoffManagerCollection {
public:
  DynmamicPayoffManagerCollection(std::initializer_list<std::pair<std::string, std::string>> idToPath);
  DynamicPayoffInstance create(TradeData const& tradeData) const;
  std::unordered_map<std::string, DynamicPayoffDiagnostics> getDiagnostics() const;

private:
  std::unordered_map<std::string, DynamicPayoffManager> mPayoffManagers;

};

