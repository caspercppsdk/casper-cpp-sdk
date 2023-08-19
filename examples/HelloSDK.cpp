#include <algorithm>
#include <iostream>

#include "../src/include/CasperClient.h" // To use Casper::Client features
#include "../src/include/Types/GlobalStateKey.h"
#include "../src/include/ByteSerializers/DeployByteSerializer.h"
#include "../src/include/Utils/CryptoUtil.h"

/// Construct a Casper::Client object
Casper::Client casper_client(CASPER_TEST_ADDRESS);

/// Helper function to print a result object
template <typename T>
void printResult(const T& result, const std::string& rpc_call_name, int indent = 2)
{
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << rpc_call_name << std::endl;

    nlohmann::json resultJSON;
    nlohmann::to_json(resultJSON, result);

    std::cout << resultJSON.dump(indent) << std::endl;
}

/// "info_get_peers" RPC function call example
void infoGetPeers()
{
    /// Call GetNodePeers function from the client object.
    Casper::InfoGetPeersResult peers_result = casper_client.GetNodePeers();
    printResult(peers_result, "info_get_peers");
}

/// "chain_get_state_root_hash" RPC function call example
void chainGetStateRootHash()
{
    /// Call the function with a block height.
    const uint64_t block_height = 10;
    Casper::GetStateRootHashResult height_result = casper_client.GetStateRootHash(block_height);
    printResult(height_result, "chain_get_state_root_hash with block height");

    /// Call the function with a block hash.
    const std::string block_hash = "acc4646f35cc1d59b24381547a4d2dc1c992a202b6165f3bf68d3f23c2b93330";
    Casper::GetStateRootHashResult hash_result = casper_client.GetStateRootHash(block_hash);
    printResult(hash_result, "chain_get_state_root_hash with block hash");

    /// Call the function with an empty string.
    Casper::GetStateRootHashResult recent_hash_result = casper_client.GetStateRootHash();
    printResult(recent_hash_result, "chain_get_state_root_hash with empty string");
}

/// "info_get_deploy" RPC function call example
void infoGetDeploy()
{
    std::cout << "-----------------------------------------------";
    std::cout << "\ninfo_get_deploy\n";

    // Option<u64> Testnet Deploy Hash
    // 07d881163cd3cc19b619e461b64d1f674ef74719a18dd5dd41ddb39da1fb1c88

    // List<String> Testnet Deploy Hash
    // da5ddafc219ebe05b087faaee5db6390ce560bda7ab4b6f3cbe9c8d0100bcdd2
    Casper::GetDeployInfoResult deploy_result =
        casper_client.GetDeployInfo("8e535d2baed76141ab47fd93b04dd61f65a07893b7c950022978a2b29628edd7");

    printResult(deploy_result, "info_get_deploy");
}

/// "info_get_status" RPC function call example
void infoGetStatus()
{
    Casper::GetStatusResult status_result = casper_client.GetStatusInfo();
    printResult(status_result, "info_get_status");
}

/// "chain_get_block_transfers" RPC function call example
void chainGetBlockTransfers()
{
    // https://testnet.cspr.live/deploy/8e535d2baed76141ab47fd93b04dd61f65a07893b7c950022978a2b29628edd7
    const std::string block_hash = "35f86b6ab5e13b823daee5d23f3373f6b35048e0b0ea993adfadc5ba8ee7aae5";

    Casper::GetBlockTransfersResult transfersResult = casper_client.GetBlockTransfers(block_hash);

    printResult(transfersResult, "chain_get_block_transfers");
}

/// "chain_get_block" RPC function call example
void chainGetBlock()
{
    const std::string block_hash = "acc4646f35cc1d59b24381547a4d2dc1c992a202b6165f3bf68d3f23c2b93330";

    Casper::GetBlockResult blockResult = casper_client.GetBlock(block_hash);
    // or casper_client.GetBlock(532041);

    printResult(blockResult, "chain_get_block");
}

/// "chain_get_era_info_by_switch_block" RPC function call example
void chainGetEraInfoBySwitchBlock()
{
    const std::string block_hash = "d2077716e5b8796723c5720237239720f54e6ada54e3357f2c4896f2a51a6d8f";

    Casper::GetEraInfoResult eraInfoResult = casper_client.GetEraInfoBySwitchBlock(block_hash);

    printResult(eraInfoResult, "chain_get_era_info_by_switch_block");
}

/// "state_get_item" RPC function call example
void stateGetItem()
{
    const std::string state_root_hash = "39f2800688b94f68ca640b26c7d0f50a90d2ce9af55c9484e66151b544345303";

    const std::string item_key = "transfer-"
                                 "9f5fe878c29fc3bf537c0509ec5abe1781a72bb6a3197a440e3e68247fba5909";

    Casper::GetItemResult itemResult = casper_client.GetItem(state_root_hash, item_key);

    printResult(itemResult, "state_get_item");
}

/// "state_get_dictionary_item" RPC function call example
void stateGetDictionaryItem()
{
    std::string state_root_hash = "322b8d17faea2ee780b9b952a25a86520d36a78e20113f0658ae0b29a68a7384";

    std::string item_key = "dictionary-"
                           "5d3e90f064798d54e5e53643c4fce0cbb1024aadcad1586cc4b7c1358a530373";

    Casper::GetDictionaryItemResult dictionaryItemResult = casper_client.GetDictionaryItem(state_root_hash, item_key);

    printResult(dictionaryItemResult, "state_get_dictionary_item");
}

/// "state_get_balance" RPC function call example
void stateGetBalance()
{
    const std::string purse_uref = "uref-54fd72455872082a254b0160e94a86245acd0c441f526688bda1261d0969057a-"
                                   "007";

    const std::string state_root_hash = "66eb7e43886c908aae8246ba2d22aa30d21e1c187a38fa3093f14e4a4219dd6c";

    Casper::GetBalanceResult balanceResult = casper_client.GetAccountBalance(purse_uref, state_root_hash);

    printResult(balanceResult, "state_get_balance");
}

/// "state_get_auction_info" RPC function call example
void stateGetAuctionInfo()
{
    const std::string block_hash = "a5ce9e1ea4ff786cf1eb9dfbe3a79f70ae33d723134a060910a2db80daf85bab";

    Casper::GetAuctionInfoResult auction_result = casper_client.GetAuctionInfo(block_hash);

    printResult(auction_result, "state_get_auction_info");
}

/// "account_put_deploy" RPC function call example
void accountPutDeploy()
{
    // TODO: fix error: Invalid Deploy, data: "deploy received by the node expired at
    std::string file_path = __FILE__;
    std::string dir_path = file_path.substr(0, file_path.rfind('/'));
    std::cout << dir_path << std::endl;
    std::string file_path_name = dir_path + "/example_put_deploy1.json";

    std::ifstream ifs(file_path_name);
    nlohmann::json deploy_params_json = nlohmann::json::parse(ifs);

    // std::cout << deploy_params_json.dump(2) << std::endl;

    Casper::Deploy deploy_params;
    Casper::from_json(deploy_params_json, deploy_params);

    Casper::Deploy dp(deploy_params.header, deploy_params.payment, deploy_params.session);

    Casper::DeployApproval approval(
        Casper::PublicKey::FromHexString(deploy_params.approvals[0].signer.ToString()),
        Casper::Signature::FromHexString(deploy_params.approvals[0].signature.ToHexString()));
    dp.AddApproval(approval);

    using namespace std::chrono;

    const auto now_ms = time_point_cast<milliseconds>(system_clock::now());
    const auto now_s = time_point_cast<seconds>(now_ms);
    const auto millis = now_ms - now_s;
    const auto c_now = system_clock::to_time_t(now_s);
    /*
       std::stringstream ss;
       ss << std::put_time(gmtime(&c_now), "%FT%T") << '.' << std::setfill('0')
          << std::setw(3) << millis.count() << 'Z';

     */

    // dp.header.timestamp = Casper::CryptoUtil::timeToRFC3339(c_now);
    dp.header.timestamp = "2022-04-23T09:38:21.700Z";
    Casper::Deploy t2(dp.header, dp.payment, dp.session);
    t2.AddApproval(approval);

    t2.header.body_hash = Casper::CEP57Checksum::Encode(t2.ComputeBodyHash(t2.payment, t2.session));
    t2.hash = Casper::CEP57Checksum::Encode(t2.ComputeHeaderHash(t2.header));
    Casper::DeployByteSerializer sery;
    std::string deploy_bytes = Casper::hexEncode(sery.ToBytes(t2));
    std::reverse(deploy_bytes.begin(), deploy_bytes.end());

    Casper::PutDeployResult put_deploy_result = casper_client.PutDeploy(t2);
    printResult(put_deploy_result, "account_put_deploy");
}

int main()
{
    // Milestone 1
    infoGetPeers();

    chainGetStateRootHash();
    // ---------------------------------------------------------------------------

    // Milestone 2
    infoGetDeploy();

    infoGetStatus();

    chainGetBlockTransfers();

    chainGetBlock();

    chainGetEraInfoBySwitchBlock();

    stateGetItem();

    stateGetDictionaryItem();

    stateGetBalance();

    stateGetAuctionInfo();

    // Milestone 3

    accountPutDeploy();
}
