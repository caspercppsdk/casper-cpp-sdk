#include <CasperClient.h>

namespace Casper {

Client::Client(const std::string& address)
    : mAddress{address},
      mHttpConnector{mAddress},
      mRpcClient{mHttpConnector, jsonrpccxx::version::v2} {}

InfoGetPeersResult Client::GetNodePeers() {
  return mRpcClient.CallMethod<InfoGetPeersResult>(1, "info_get_peers", {});
}

GetStateRootHashResult Client::GetStateRootHash(std::string block_hash) {
  nlohmann::json hashJSON{{"Hash", block_hash}};
  nlohmann::json block_identifier{{"block_identifier", hashJSON}};

  return mRpcClient.CallMethodNamed<GetStateRootHashResult>(
      1, "chain_get_state_root_hash", block_identifier);
}

GetStateRootHashResult Client::GetStateRootHash(uint64_t block_height) {
  nlohmann::json heightJSON{{"Height", block_height}};
  nlohmann::json block_identifier{{"block_identifier", heightJSON}};

  return mRpcClient.CallMethodNamed<GetStateRootHashResult>(
      1, "chain_get_state_root_hash", block_identifier);
}

GetDeployInfoResult Client::GetDeployInfo(std::string deploy_hash) {
  nlohmann::json hashJSON{{"deploy_hash", deploy_hash}};

  return mRpcClient.CallMethodNamed<GetDeployInfoResult>(1, "info_get_deploy",
                                                         hashJSON);
}

GetStatusResult Client::GetStatusInfo() {
  return mRpcClient.CallMethodNamed<GetStatusResult>(1, "info_get_status");
}

GetBlockTransfersResult Client::GetBlockTransfers(std::string block_hash) {
  nlohmann::json hashJSON{{"Hash", block_hash}};
  nlohmann::json block_identifier{{"block_identifier", hashJSON}};

  return mRpcClient.CallMethodNamed<GetBlockTransfersResult>(
      1, "chain_get_block_transfers", block_identifier);
}

GetBlockTransfersResult Client::GetBlockTransfers(uint64_t block_height) {
  nlohmann::json heightJSON{{"Height", block_height}};
  nlohmann::json block_identifier{{"block_identifier", heightJSON}};

  return mRpcClient.CallMethodNamed<GetBlockTransfersResult>(
      1, "chain_get_block_transfers", block_identifier);
}

GetBlockResult Client::GetBlock(std::string block_hash) {
  nlohmann::json hashJSON{{"Hash", block_hash}};
  nlohmann::json block_identifier{{"block_identifier", hashJSON}};

  return mRpcClient.CallMethodNamed<GetBlockResult>(1, "chain_get_block",
                                                    block_identifier);
}

GetBlockResult Client::GetBlock(uint64_t block_height) {
  nlohmann::json heightJSON{{"Height", block_height}};
  nlohmann::json block_identifier{{"block_identifier", heightJSON}};

  return mRpcClient.CallMethodNamed<GetBlockResult>(1, "chain_get_block",
                                                    block_identifier);
}

GetEraInfoResult Client::GetEraInfoBySwitchBlock(std::string block_hash) {
  nlohmann::json hashJSON{{"Hash", block_hash}};
  nlohmann::json block_identifier{{"block_identifier", hashJSON}};

  return mRpcClient.CallMethodNamed<GetEraInfoResult>(
      1, "chain_get_era_info_by_switch_block", block_identifier);
}

GetEraInfoResult Client::GetEraInfoBySwitchBlock(uint64_t block_height) {
  nlohmann::json heightJSON{{"Height", block_height}};
  nlohmann::json block_identifier{{"block_identifier", heightJSON}};

  return mRpcClient.CallMethodNamed<GetEraInfoResult>(
      1, "chain_get_era_info_by_switch_block", block_identifier);
}

GetItemResult Client::GetItem(std::string state_root_hash, std::string key,
                              std::vector<std::string> path) {
  nlohmann::json paramsJSON{
      {"state_root_hash", state_root_hash}, {"key", key}, {"path", path}};

  return mRpcClient.CallMethodNamed<GetItemResult>(1, "state_get_item",
                                                   paramsJSON);
}

GetDictionaryItemResult Client::GetDictionaryItem(std::string stateRootHash,
                                                  std::string dictionaryItem) {
  nlohmann::json dictionaryJSON{{"Dictionary", dictionaryItem}};

  nlohmann::json paramsJSON{{"state_root_hash", stateRootHash},
                            {"dictionary_identifier", dictionaryJSON}};

  return mRpcClient.CallMethodNamed<GetDictionaryItemResult>(
      1, "state_get_dictionary_item", paramsJSON);
}

GetDictionaryItemResult Client::GetDictionaryItemByAccount(
    std::string stateRootHash, std::string accountKey,
    std::string dictionaryName, std::string dictionaryItemKey) {
  nlohmann::json accountNamedKey{{"key", accountKey},
                                 {"dictionary_name", dictionaryName},
                                 {"dictionary_item_key", dictionaryItemKey}};
  nlohmann::json accountNamedKeyJSON{{"AccountNamedKey", accountNamedKey}};
  nlohmann::json paramsJSON{{"state_root_hash", stateRootHash},
                            {"dictionary_identifier", accountNamedKeyJSON}};

  return mRpcClient.CallMethodNamed<GetDictionaryItemResult>(
      1, "state_get_dictionary_item", paramsJSON);
}

GetDictionaryItemResult Client::GetDictionaryItemByContract(
    std::string stateRootHash, std::string contractKey,
    std::string dictionaryName, std::string dictionaryItemKey) {
  nlohmann::json contractNamedKey{{"key", contractKey},
                                  {"dictionary_name", dictionaryName},
                                  {"dictionary_item_key", dictionaryItemKey}};
  nlohmann::json contractNamedKeyJSON{{"ContractNamedKey", contractNamedKey}};
  nlohmann::json paramsJSON{{"state_root_hash", stateRootHash},
                            {"dictionary_identifier", contractNamedKeyJSON}};

  return mRpcClient.CallMethodNamed<GetDictionaryItemResult>(
      1, "state_get_dictionary_item", paramsJSON);
}

GetDictionaryItemResult Client::GetDictionaryItemByURef(
    std::string stateRootHash, std::string seedURef,
    std::string dictionaryItemKey) {
  nlohmann::json urefIdentifier{{"seed_uref", seedURef},
                                {"dictionary_item_key", dictionaryItemKey}};
  nlohmann::json urefIdentifierJSON{{"URef", urefIdentifier}};
  nlohmann::json paramsJSON{{"state_root_hash", stateRootHash},
                            {"dictionary_identifier", urefIdentifierJSON}};

  return mRpcClient.CallMethodNamed<GetDictionaryItemResult>(
      1, "state_get_dictionary_item", paramsJSON);
}

GetBalanceResult Client::GetAccountBalance(std::string purseURef,
                                           std::string stateRootHash) {
  /*
// TODO:
if (!purseURef.StartsWith("uref-"))
            {
                var response = await GetAccountInfo(purseURef);
                purseURef = response.Result.GetProperty("account")
                    .GetProperty("main_purse").GetString();
            }


  if (stateRootHash.empty()) {
    stateRootHash = GetStateRootHash().state_root_hash;
  }
*/
  nlohmann::json paramsJSON{{"state_root_hash", stateRootHash},
                            {"purse_uref", purseURef}};

  return mRpcClient.CallMethodNamed<GetBalanceResult>(1, "state_get_balance",
                                                      paramsJSON);
}

GetAuctionInfoResult Client::GetAuctionInfo(std::string block_hash) {
  nlohmann::json hashJSON{{"Hash", block_hash}};
  nlohmann::json block_identifier{{"block_identifier", hashJSON}};

  return mRpcClient.CallMethodNamed<GetAuctionInfoResult>(
      1, "state_get_auction_info", block_identifier);
}

GetAuctionInfoResult Client::GetAuctionInfo(uint64_t block_height) {
  nlohmann::json heightJSON{{"Height", block_height}};
  nlohmann::json block_identifier{{"block_identifier", heightJSON}};

  return mRpcClient.CallMethodNamed<GetAuctionInfoResult>(
      1, "state_get_auction_info", block_identifier);
}

PutDeployResult Client::PutDeploy(Deploy deploy) {
  nlohmann::json deploy_json;
  to_json(deploy_json, deploy);
  nlohmann::json paramsJSON{"deploy", deploy_json};

  return mRpcClient.CallMethodNamed<PutDeployResult>(1, "account_put_deploy",
                                                     paramsJSON);
}

}  // namespace Casper
