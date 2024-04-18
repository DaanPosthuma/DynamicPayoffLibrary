#include "DynamicPayoffManagerCollection.h"
#include "payoffs/DynamicPayoffInstance.h"
#include "TradeData/TradeData.h"

DynamicPayoffInstance DynmamicPayoffManagerCollection::create(TradeData const& tradeData) const {
  auto const payoffId = tradeData.getString("PayoffId");
  if (!mPayoffManagers.contains(payoffId)) throw std::logic_error("No manager found for PayoffId '" + payoffId + "'");
  auto const& manager = mPayoffManagers.at(payoffId);
  return manager.createPayoff(tradeData);
}

std::unordered_map<std::string, DynamicPayoffDiagnostics> DynmamicPayoffManagerCollection::getDiagnostics() const {
  auto diagnostics = std::unordered_map<std::string, DynamicPayoffDiagnostics>();
  for (auto const& [payoffId, manager] : mPayoffManagers) {
    diagnostics[payoffId] = manager.getDiagnostics();
  }
  return diagnostics;
}

DynmamicPayoffManagerCollection::DynmamicPayoffManagerCollection(std::initializer_list<std::pair<std::string, std::string>> idToPath) {
  for (auto const& [id, path] : idToPath) {
    mPayoffManagers.emplace(id, DynamicPayoffManager(path));
  }
}

