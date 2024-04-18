#include "DynamicPayoffManagerCollection.h"
#include "payoffs/DynamicPayoffInstance.h"
#include "TradeData/TradeData.h"

DynamicPayoffInstance DynmamicPayoffManagerCollection::createPayoffInstance(TradeData const& tradeData) const {
  auto const payoffId = tradeData.getString("PayoffId");
  if (!mPayoffManagers.contains(payoffId)) throw std::logic_error("No manager found for PayoffId '" + payoffId + "'");
  auto const& manager = mPayoffManagers.at(payoffId);
  return manager.createPayoff(tradeData);
}

std::unordered_map<std::string, std::string> DynmamicPayoffManagerCollection::getRevisions() const {
  auto revisions = std::unordered_map<std::string, std::string>();
  for (auto const& [payoffId, manager] : mPayoffManagers) {
    revisions[payoffId] = manager.getRevision();
  }
  return revisions;
}

std::unordered_map<std::string, int> DynmamicPayoffManagerCollection::getNumCreated() const {
  auto numCreated = std::unordered_map<std::string, int>();
  for (auto const& [payoffId, manager] : mPayoffManagers) {
    numCreated[payoffId] = manager.numCreated();
  }
  return numCreated;
}

DynmamicPayoffManagerCollection::DynmamicPayoffManagerCollection(std::initializer_list<std::pair<std::string, std::string>> idToPath) {
  for (auto const& [id, path] : idToPath) {
    mPayoffManagers.emplace(id, DynamicPayoffManager(path));
  }
}

