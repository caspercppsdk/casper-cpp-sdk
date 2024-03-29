#include <spdlog/spdlog.h>

#include <utility>
#include "CasperClient.h"
namespace Casper
{

/// Construct a new Casper Client object
Client::Client(std::string address, const LogConfig* const log_config)
    : mAddress{std::move(address)}
    , mHttpConnector{mAddress}
    , mRpcClient{mHttpConnector, jsonrpccxx::version::v2}
{
    if (log_config)
    {
        LogConfig config{.log_name = "Casper-SDK", .severity = log_config->severity, .sink = log_config->sink};

        LogConfigurator::initDefault(config);
    }
}

/// Get a list of the nodes.
InfoGetPeersResult Client::GetNodePeers()
{
    return mRpcClient.CallMethod<InfoGetPeersResult>(1, "info_get_peers", {});
}

/// Returns the state root hash at a given block
GetStateRootHashResult Client::GetStateRootHash(const std::string& block_hash)
{
    nlohmann::json hashJSON{{"Hash", block_hash}};
    nlohmann::json block_identifier{{"block_identifier", hashJSON}};

    if (block_hash.empty())
        block_identifier = nlohmann::json({});

    return mRpcClient.CallMethodNamed<GetStateRootHashResult>(1, "chain_get_state_root_hash", block_identifier);
}

/// Returns the state root hash at a given height
GetStateRootHashResult Client::GetStateRootHash(uint64_t block_height)
{
    nlohmann::json heightJSON{{"Height", block_height}};
    nlohmann::json block_identifier{{"block_identifier", heightJSON}};

    return mRpcClient.CallMethodNamed<GetStateRootHashResult>(1, "chain_get_state_root_hash", block_identifier);
}

/// Returns the deploy info.
GetDeployInfoResult Client::GetDeployInfo(const std::string& deploy_hash, int counter)
{
    nlohmann::json hashJSON{{"deploy_hash", deploy_hash}};
    return mRpcClient.CallMethodNamed<GetDeployInfoResult>(1, "info_get_deploy", hashJSON);
    // try
    //     {
    //         return mRpcClient.CallMethodNamed<GetDeployInfoResult>(1, "info_get_deploy", hashJSON);

    // } catch (const jsonrpccxx::JsonRpcException& e)
    //     {
    //         if (counter++ < 3)
    //             {
    //                 spdlog::error("JsonRpcException: {}", e.what());
    //                 spdlog::error("Retrying...");
    //                 std::this_thread::sleep_for(std::chrono::seconds(5));
    //                 return GetDeployInfo(deploy_hash, counter);
    //             }
    //         else
    //             {
    //                 spdlog::error("JsonRpcException: {}", e.what());
    //                 spdlog::error("Retrying...");
    //                 throw;
    //             }
    // }
}

/// Returns the status info.
GetStatusResult Client::GetStatusInfo()
{
    return mRpcClient.CallMethodNamed<GetStatusResult>(1, "info_get_status");
}

/// Returns the transfers at the block given by the block hash.
GetBlockTransfersResult Client::GetBlockTransfers(const std::string& block_hash)
{
    nlohmann::json hashJSON{{"Hash", block_hash}};
    nlohmann::json block_identifier{{"block_identifier", hashJSON}};

    return mRpcClient.CallMethodNamed<GetBlockTransfersResult>(1, "chain_get_block_transfers", block_identifier);
}

/// Returns the transfers at the block given by the block height.
GetBlockTransfersResult Client::GetBlockTransfers(uint64_t block_height)
{
    nlohmann::json heightJSON{{"Height", block_height}};
    nlohmann::json block_identifier{{"block_identifier", heightJSON}};

    return mRpcClient.CallMethodNamed<GetBlockTransfersResult>(1, "chain_get_block_transfers", block_identifier);
}

/// Returns the block at the block given by the block hash.
GetBlockResult Client::GetBlock(const std::string& block_hash)
{
    nlohmann::json hashJSON{{"Hash", block_hash}};
    nlohmann::json block_identifier{{"block_identifier", hashJSON}};

    return mRpcClient.CallMethodNamed<GetBlockResult>(1, "chain_get_block", block_identifier);
}

/// Returns the block at the block given by the block height.
GetBlockResult Client::GetBlock(uint64_t block_height)
{
    nlohmann::json heightJSON{{"Height", block_height}};
    nlohmann::json block_identifier{{"block_identifier", heightJSON}};

    return mRpcClient.CallMethodNamed<GetBlockResult>(1, "chain_get_block", block_identifier);
}

/// Returns the era information at the block given by the block hash.
GetEraInfoResult Client::GetEraInfoBySwitchBlock(const std::string& block_hash)
{
    nlohmann::json hashJSON{{"Hash", block_hash}};
    nlohmann::json block_identifier{{"block_identifier", hashJSON}};

    return mRpcClient.CallMethodNamed<GetEraInfoResult>(1, "chain_get_era_info_by_switch_block", block_identifier);
}

/// Returns the era information at the block given by the block height.
GetEraInfoResult Client::GetEraInfoBySwitchBlock(uint64_t block_height)
{
    nlohmann::json heightJSON{{"Height", block_height}};
    nlohmann::json block_identifier{{"block_identifier", heightJSON}};

    return mRpcClient.CallMethodNamed<GetEraInfoResult>(1, "chain_get_era_info_by_switch_block", block_identifier);
}

/// Returns the item at the given address with the given key.
GetItemResult Client::GetItem(const std::string& state_root_hash, const std::string& key,
                              const std::vector<std::string>& path)
{
    nlohmann::json paramsJSON{{"state_root_hash", state_root_hash}, {"key", key}, {"path", path}};

    return mRpcClient.CallMethodNamed<GetItemResult>(1, "state_get_item", paramsJSON);
}

/// Returns the item in json at the given address with the given key.
/// FIXME: It is only a workaround, as GetItem function does not parse
/// correctly result from json:
/// https://matterfi.atlassian.net/browse/CD-216
nlohmann::json Client::GetItem_WA(const std::string& state_root_hash, const std::string& key,
                                  const std::vector<std::string>& path)
{
    nlohmann::json paramsJSON{{"state_root_hash", state_root_hash}, {"key", key}, {"path", path}};

    return mRpcClient.CallMethodNamed_JsonRepr(1, "state_get_item", paramsJSON);
}

/// Returns the dictionary item with the given key and state root hash.
nlohmann::json Client::GetDictionaryItem(const std::string& stateRootHash, const std::string& dictionaryItem)
{
    nlohmann::json dictionaryJSON{{"Dictionary", dictionaryItem}};

    nlohmann::json paramsJSON{{"state_root_hash", stateRootHash}, {"dictionary_identifier", dictionaryJSON}};

    return mRpcClient.CallMethodNamed<nlohmann::json>(1, "state_get_dictionary_item", paramsJSON);
}

/// Returns the dictionary item with the given account key and item key.
GetDictionaryItemResult Client::GetDictionaryItemByAccount(const std::string& stateRootHash,
                                                           const std::string& accountKey,
                                                           const std::string& dictionaryName,
                                                           const std::string& dictionaryItemKey)
{
    nlohmann::json accountNamedKey{
        {"key", accountKey}, {"dictionary_name", dictionaryName}, {"dictionary_item_key", dictionaryItemKey}};
    nlohmann::json accountNamedKeyJSON{{"AccountNamedKey", accountNamedKey}};
    nlohmann::json paramsJSON{{"state_root_hash", stateRootHash}, {"dictionary_identifier", accountNamedKeyJSON}};

    return mRpcClient.CallMethodNamed<GetDictionaryItemResult>(1, "state_get_dictionary_item", paramsJSON);
}

/// Returns the dictionary item with the given contract.
GetDictionaryItemResult Client::GetDictionaryItemByContract(const std::string& stateRootHash,
                                                            const std::string& contractKey,
                                                            const std::string& dictionaryName,
                                                            const std::string& dictionaryItemKey)
{
    nlohmann::json contractNamedKey{
        {"key", contractKey}, {"dictionary_name", dictionaryName}, {"dictionary_item_key", dictionaryItemKey}};
    nlohmann::json contractNamedKeyJSON{{"ContractNamedKey", contractNamedKey}};
    nlohmann::json paramsJSON{{"state_root_hash", stateRootHash}, {"dictionary_identifier", contractNamedKeyJSON}};

    return mRpcClient.CallMethodNamed<GetDictionaryItemResult>(1, "state_get_dictionary_item", paramsJSON);
}

/// Returns the dictionary item with the given URef.
GetDictionaryItemResult Client::GetDictionaryItemByURef(const std::string& stateRootHash, const std::string& seedURef,
                                                        const std::string& dictionaryItemKey)
{
    nlohmann::json urefIdentifier{{"seed_uref", seedURef}, {"dictionary_item_key", dictionaryItemKey}};
    nlohmann::json urefIdentifierJSON{{"URef", urefIdentifier}};
    nlohmann::json paramsJSON{{"state_root_hash", stateRootHash}, {"dictionary_identifier", urefIdentifierJSON}};

    return mRpcClient.CallMethodNamed<GetDictionaryItemResult>(1, "state_get_dictionary_item", paramsJSON);
}

/// Returns the balance of the given account.
GetBalanceResult Client::GetAccountBalance(const std::string& purseURef, const std::string& stateRootHash)
{
    nlohmann::json paramsJSON{{"state_root_hash", stateRootHash}, {"purse_uref", purseURef}};

    return mRpcClient.CallMethodNamed<GetBalanceResult>(1, "state_get_balance", paramsJSON);
}

/// Returns the auction information for the given block hash.
GetAuctionInfoResult Client::GetAuctionInfo(const std::string& block_hash)
{
    nlohmann::json hashJSON{{"Hash", block_hash}};
    nlohmann::json block_identifier{{"block_identifier", hashJSON}};

    return mRpcClient.CallMethodNamed<GetAuctionInfoResult>(1, "state_get_auction_info", block_identifier);
}

/// Returns the auction information for the given block height.
GetAuctionInfoResult Client::GetAuctionInfo(uint64_t block_height)
{
    nlohmann::json heightJSON{{"Height", block_height}};
    nlohmann::json block_identifier{{"block_identifier", heightJSON}};

    return mRpcClient.CallMethodNamed<GetAuctionInfoResult>(1, "state_get_auction_info", block_identifier);
}

/// Returns the deploy hash of the given deploy.
PutDeployResult Client::PutDeploy(const Deploy& deploy)
{
    nlohmann::json deploy_json;
    to_json(deploy_json, deploy);
    nlohmann::json paramsJSON{{"deploy", deploy_json}};
    return mRpcClient.CallMethodNamed<PutDeployResult>(1, "account_put_deploy", paramsJSON);
}

std::vector<std::string> Client::splitPath(const std::string& path)
{
    std::stringstream ss(path);
    std::string curr_path;
    std::vector<std::string> paths;
    while (std::getline(ss, curr_path, '/'))
    {
        paths.push_back(curr_path);
    }
    return paths;
}

QueryGlobalStateResult Client::QueryGlobalState(const std::string& key, const std::string& state_root_hash,
                                                const std::string& path)
{
    std::vector<std::string> path_vec = splitPath(path);
    nlohmann::json hashJSON{{"StateRootHash", state_root_hash}};

    nlohmann::json paramsJSON{{"state_identifier", hashJSON}, {"key", key}, {"path", path_vec}};

    return mRpcClient.CallMethodNamed<QueryGlobalStateResult>(1, "query_global_state", paramsJSON);
}

QueryGlobalStateResult Client::QueryGlobalState(GlobalStateKey key, const std::string& state_root_hash,
                                                const std::string& path)
{
    return QueryGlobalState(key.ToString(), state_root_hash, path);
}

QueryGlobalStateResult Client::QueryGlobalStateWithBlockHash(const std::string& key, const std::string& block_hash,
                                                             const std::string& path)
{
    std::vector<std::string> path_vec = splitPath(path);
    nlohmann::json hashJSON{{"BlockHash", block_hash}};

    nlohmann::json paramsJSON{{"state_identifier", hashJSON}, {"key", key}, {"path", path_vec}};

    return mRpcClient.CallMethodNamed<QueryGlobalStateResult>(1, "query_global_state", paramsJSON);
}

QueryGlobalStateResult Client::QueryGlobalStateWithBlockHash(GlobalStateKey key, const std::string& block_hash,
                                                             const std::string& path)
{
    return QueryGlobalState(key.ToString(), block_hash, path);
}

/// Returns the state root hash at a given block
SpeculativeExecResult Client::SpeculativeExec(const Deploy& deploy, const std::string& block_hash)
{
    nlohmann::json blockHashJson{{"Hash", block_hash}};

    nlohmann::json deploy_json;
    to_json(deploy_json, deploy);

    nlohmann::json paramsJSON{{"block_identifier", nullptr}, {"deploy", deploy_json}};

    return mRpcClient.CallMethodNamed<SpeculativeExecResult>(1, "speculative_exec", paramsJSON);
}

/// Returns the state root hash at a given height
SpeculativeExecResult Client::SpeculativeExec(const Deploy& deploy, uint64_t block_height)
{
    nlohmann::json blockHeightJSON{{"Height", block_height}};

    nlohmann::json deploy_json;
    to_json(deploy_json, deploy);

    nlohmann::json paramsJSON{{"block_identifier", blockHeightJSON}, {"deploy", deploy_json}};

    return mRpcClient.CallMethodNamed<SpeculativeExecResult>(1, "speculative_exec", paramsJSON);
}

/// Returns the chainspec.toml file of the node.
GetChainspecResult Client::GetChainspec()
{
    return mRpcClient.CallMethodNamed<GetChainspecResult>(1, "info_get_chainspec");
}

} // namespace Casper
