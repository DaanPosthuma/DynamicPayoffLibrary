#pragma once

#include <unordered_map>
#include <string>
#include "DynamicPayoffManager.h"

class DynmamicPayoffManagerCollection {
public:
  DynmamicPayoffManagerCollection(std::initializer_list<std::pair<std::string, std::string>> idToPath);
  DynamicPayoffInstance createPayoffInstance(TradeData const& tradeData) const;
  std::unordered_map<std::string, std::string> getRevisions() const;
  std::unordered_map<std::string, int> getNumCreated() const;

private:
  std::unordered_map<std::string, DynamicPayoffManager> mPayoffManagers;

};

