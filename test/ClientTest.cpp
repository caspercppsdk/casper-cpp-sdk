#include "CasperClient.h"
#include "Types/GlobalStateKey.cpp"
#include "Types/PublicKey.h"
#include "Utils/CryptoUtil.h"
#include "acutest.h"

// Helper function to compare two strings in a case insensitive way
bool iequals(const std::string& a, const std::string& b) {
  return std::equal(a.begin(), a.end(), b.begin(), b.end(),
                    [](char a, char b) { return tolower(a) == tolower(b); });
}

/// Helper function to print a result object
template <typename T>
void printResult(const T& result, const std::string& rpc_call_name,
                 int indent = 2) {
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << rpc_call_name << std::endl;

  nlohmann::json resultJSON;
  nlohmann::to_json(resultJSON, result);

  std::cout << resultJSON.dump(indent) << std::endl;
}

/**
 * @brief Check the "info_get_peers" rpc function. The size of the return value
 * should be greater than 0.
 *
 */
void infoGetPeersTest() {
  Casper::Client client(CASPER_TEST_ADDRESS);

  auto result = client.GetNodePeers();
  size_t result_size = result.peers.size();

  TEST_ASSERT(result_size > 0);
}

/**
 * @brief Check the "get_state_root_hash" rpc function with an example height.
 * Compare the result with the expected hash of the state.
 *
 */
void getStateRootHashBlockHeightTest() {
  Casper::Client client(CASPER_TEST_ADDRESS);

  uint64_t block_height = 10;
  std::string result = client.GetStateRootHash(block_height).state_root_hash;
  std::string expected_result =
      "4d180287e6eb3dad5173864e30d7653c01fcdef8bc3ee31db4a0707367154ccf";

  TEST_ASSERT(iequals(result, expected_result));
}

/**
 * @brief Check the "get_state_root_hash" rpc function with an example block
 * hash. Compare the result with the expected hash of the state.
 *
 */
void getStateRootHashBlockHashTest() {
  Casper::Client client(CASPER_TEST_ADDRESS);

  std::string block_hash =
      "9511adf5ed36ccba48d71840fd558d4397c9eb0470d1e25711b5419632a6f55a";
  std::string result = client.GetStateRootHash(block_hash).state_root_hash;
  std::string expected_result =
      "9aa3c10d4db2e02adb464458c7a09d1df2ed551be02d2c7bbdbe847d3731e84f";

  TEST_ASSERT(iequals(result, expected_result));
}

/**
 * @brief Check the "get_state_root_hash" rpc function without a variable.
 * Compare the result with an empty string.
 *
 */
void getStateRootHashLastBlockTest() {
  Casper::Client client(CASPER_TEST_ADDRESS);

  std::string result = client.GetStateRootHash().state_root_hash;

  TEST_ASSERT(result != "");
}

/**
 * @brief Check the "info_get_deploy" rpc function
 *
 */
void get_deploy_test() {
  Casper::Client client(CASPER_TEST_ADDRESS);
  // Casper::GetDeployInfoResult result = client.GetDeployInfo();

  // TEST_ASSERT(result.api_version != "");
}

/**
 * @brief Check the "info_get_status" rpc function. Check the result
 * variables.
 *
 */
void getStatusInfoTest() {
  Casper::Client client(CASPER_TEST_ADDRESS);
  Casper::GetStatusResult result = client.GetStatusInfo();

  TEST_ASSERT(result.api_version != "");

  std::string expected_chainspec_name = "casper-test";
  TEST_ASSERT(iequals(result.chainspec_name, expected_chainspec_name));

  TEST_ASSERT(result.starting_state_root_hash != "");

  if (result.our_public_signing_key.has_value()) {
    TEST_ASSERT(result.our_public_signing_key.value().ToString() != "");
  }

  if (result.last_added_block_info.has_value()) {
    auto& last_block = result.last_added_block_info.value();
    TEST_ASSERT(last_block.hash != "");
    TEST_ASSERT(last_block.height >= 0);
    TEST_ASSERT(last_block.timestamp != "");
    TEST_ASSERT(last_block.state_root_hash != "");
    TEST_ASSERT(last_block.creator.ToString() != "");
  }

  if (result.peers.size() > 0) {
    TEST_ASSERT(result.peers[0].address != "");
    TEST_ASSERT(result.peers[0].node_id != "");
  }

  TEST_ASSERT(result.build_version != "");
  TEST_ASSERT(result.uptime != "");
}

/**
 * @brief Check the "chain_get_block_transfers" rpc function.
 *
 */
void getBlockTransfersTest() {
  Casper::Client client(CASPER_TEST_ADDRESS);

  // Call the rpc function
  std::string block_hash =
      "35f86b6ab5e13b823daee5d23f3373f6b35048e0b0ea993adfadc5ba8ee7aae5";
  Casper::StringUtil::toLower(block_hash);
  Casper::GetBlockTransfersResult result = client.GetBlockTransfers(block_hash);

  // Expected Values
  std::string expected_block_hash = block_hash;
  big_int expected_amount = 199000000000;
  std::string expected_deploy_hash =
      "8e535d2baed76141ab47fd93b04dd61f65a07893b7c950022978a2b29628edd7";
  std::string expected_from =
      "account-hash-"
      "308d2a0eCF66bDAcAC5Cf6184C732D83DCeB48A859169e5680FE17cF32Bb974F";
  big_int expected_gas = 0;
  std::string expected_source =
      "uref-5ce1d189e8ccafdd5a959088ffd870f54b29bd5afeb05950dddcc12ec7dcbe90-"
      "007";
  std::string expected_target =
      "uref-c9733355d61aa2a36721d9d1081eebcfe5dde94f82386b3d75163fee894d292a-"
      "007";

  TEST_ASSERT(result.api_version != "");

  TEST_ASSERT(result.block_hash.has_value());
  TEST_ASSERT(iequals(result.block_hash.value(), expected_block_hash));

  // check transfers
  TEST_ASSERT(result.transfers.has_value());
  TEST_ASSERT(result.transfers.value().size() > 0);

  auto& transfers = result.transfers.value();
  auto test_transfer = std::find_if(
      transfers.begin(), transfers.end(), [&](const Casper::Transfer& x) {
        return iequals(x.deploy_hash, expected_deploy_hash);
      });
  TEST_ASSERT(test_transfer != transfers.end());

  // Actual Values
  big_int current_amount = test_transfer->amount;
  std::string current_deploy_hash = test_transfer->deploy_hash;
  std::string current_from = test_transfer->from.ToString();
  big_int current_gas = test_transfer->gas;
  std::string current_source = test_transfer->source.ToString();
  std::string current_target = test_transfer->target.ToString();

  // tests for the first transfer
  TEST_ASSERT(current_amount == expected_amount);
  TEST_ASSERT(iequals(current_deploy_hash, expected_deploy_hash));
  TEST_ASSERT(iequals(current_from, expected_from));
  TEST_ASSERT(current_gas == expected_gas);
  TEST_ASSERT(iequals(current_source, expected_source));
  TEST_ASSERT(iequals(current_target, expected_target));
}

/**
 * @brief Check the "chain_get_block" rpc function
 *
 */
void getBlockTest() {
  Casper::Client client(CASPER_TEST_ADDRESS);

  std::string block_hash =
      "acc4646f35cc1d59b24381547a4d2dc1c992a202b6165f3bf68d3f23c2b93330";
  Casper::GetBlockResult blockResult = client.GetBlock(block_hash);

  TEST_ASSERT(blockResult.api_version != "");

  TEST_ASSERT(blockResult.block.has_value());
  auto& current_block = blockResult.block.value();

  TEST_ASSERT(iequals(
      current_block.hash,
      "acc4646f35cc1d59b24381547a4d2dc1c992a202b6165f3bf68d3f23c2b93330"));

  // block header
  TEST_ASSERT(iequals(
      current_block.header.parent_hash,
      "e23b5f98258aff36716a8f60ca8d57c049216eedd88e6c7e14df7a6cfbadca73"));

  TEST_ASSERT(iequals(
      current_block.header.state_root_hash,
      "f5abb3964382e0dde4bc3ec38414f43f325f5dcc6493d5a7c4037972793fb302"));

  TEST_ASSERT(iequals(
      current_block.header.body_hash,
      "e1786ce884cf41abbc758b0795ee3223daec5fb8015791ced0f8ee66deec8ee3"));

  TEST_ASSERT(iequals(
      current_block.header.accumulated_seed,
      "35b5d33db0b43df3971831880f51023b37a468ad54494316ec26af4c61904532"));

  TEST_ASSERT(current_block.header.timestamp != "");
  TEST_ASSERT(current_block.header.era_id != 0);
  TEST_ASSERT(current_block.header.height == 532041);
  TEST_ASSERT(current_block.header.protocol_version != "");

  // block body
  TEST_ASSERT(current_block.body.deploy_hashes.size() >= 0);

  TEST_ASSERT(iequals(
      current_block.body.proposer.ToString(),
      "01cd807fb41345d8dD5A61da7991e1468173acbEE53920E4DFe0D28Cb8825AC664"));

  TEST_ASSERT(current_block.body.transfer_hashes.size() >= 0);

  // block proofs
  TEST_ASSERT(current_block.proofs.size() > 0);
  TEST_ASSERT(current_block.proofs[0].public_key.ToString() != "");
  TEST_ASSERT(current_block.proofs[0].signature.ToString() != "");
}

/**
 * @brief Check the "chain_get_era_info_by_switch_block" rpc function
 *
 */
void getEraInfoBySwitchBlockTest() {
  Casper::Client client(CASPER_TEST_ADDRESS);
  Casper::GetEraInfoResult result = client.GetEraInfoBySwitchBlock(
      "d2077716e5b8796723c5720237239720f54e6ada54e3357f2c4896f2a51a6d8f");

  TEST_ASSERT(result.api_version != "");
  TEST_ASSERT(result.era_summary.has_value());
  TEST_ASSERT(result.era_summary.value().era_id != 0);
  TEST_ASSERT(result.era_summary.value().block_hash != "");
  TEST_ASSERT(result.era_summary.value().merkle_proof != "");
  TEST_ASSERT(result.era_summary.value().state_root_hash != "");
  TEST_ASSERT(result.era_summary.value().stored_value.era_info.has_value());
  TEST_ASSERT(result.era_summary.value()
                  .stored_value.era_info.value()
                  .seigniorage_allocations.size() > 0);

  int validator_cnt = 0;
  int delegator_cnt = 0;

  for (int i = 0; i < result.era_summary.value()
                          .stored_value.era_info.value()
                          .seigniorage_allocations.size();
       i++) {
    if (delegator_cnt == 1 && validator_cnt == 1) {
      break;
    }

    bool is_delegator = result.era_summary.value()
                            .stored_value.era_info.value()
                            .seigniorage_allocations[i]
                            .is_delegator;

    if (is_delegator == true && delegator_cnt == 0) {
      delegator_cnt++;
      TEST_ASSERT(result.era_summary.value()
                      .stored_value.era_info.value()
                      .seigniorage_allocations[i]
                      .delegator_public_key.ToString() != "");
      TEST_ASSERT(result.era_summary.value()
                      .stored_value.era_info.value()
                      .seigniorage_allocations[i]
                      .amount >= 0);
    } else if (is_delegator == false && validator_cnt == 0) {
      validator_cnt++;
      TEST_ASSERT(result.era_summary.value()
                      .stored_value.era_info.value()
                      .seigniorage_allocations[i]
                      .validator_public_key.ToString() != "");
      TEST_ASSERT(result.era_summary.value()
                      .stored_value.era_info.value()
                      .seigniorage_allocations[i]
                      .amount >= 0);
    }
  }
}

/**
 * @brief Check the "state_get_item" rpc function
 *
 */
void getItemTest() {
  Casper::Client client(CASPER_TEST_ADDRESS);
  std::string state_root_hash =
      "39f2800688b94f68ca640b26c7d0f50a90d2ce9af55c9484e66151b544345303";
  std::string key =
      "transfer-"
      "9f5fe878c29fc3bf537c0509ec5abe1781a72bb6a3197a440e3e68247fba5909";

  Casper::GetItemResult result = client.GetItem(state_root_hash, key);

  // tests
  TEST_ASSERT(result.api_version != "");
  TEST_ASSERT(result.merkle_proof != "");

  TEST_ASSERT(result.stored_value.transfer.has_value());

  auto& current_transfer = result.stored_value.transfer.value();

  TEST_ASSERT(iequals(
      current_transfer.deploy_hash,
      "8e535d2baed76141ab47fd93b04dd61f65a07893b7c950022978a2b29628edd7"));

  TEST_ASSERT(iequals(
      current_transfer.from.ToString(),
      "account-hash-"
      "308d2a0eCF66bDAcAC5Cf6184C732D83DCeB48A859169e5680FE17cF32Bb974F"));

  TEST_ASSERT(iequals(
      current_transfer.source.ToString(),
      "uref-5ce1d189e8ccafdd5a959088ffd870f54b29bd5afeb05950dddcc12ec7dcbe90-"
      "007"));

  TEST_ASSERT(iequals(
      current_transfer.target.ToString(),
      "uref-c9733355d61aa2a36721d9d1081eebcfe5dde94f82386b3d75163fee894d292a-"
      "007"));

  TEST_ASSERT(current_transfer.amount == 199000000000);
  TEST_ASSERT(current_transfer.gas == 0);
}

// TODO: Check this when the CLValue is implemented
// TODO: Write the other tests such as by NamedKey, Dictionary, etc.
/**
 * @brief Check the "state_get_dictionary_item" rpc function by URef
 *
 */
void getDictionaryItemTest() {
  Casper::Client client(CASPER_TEST_ADDRESS);
  std::string state_root_hash =
      "322b8d17faea2ee780b9b952a25a86520d36a78e20113f0658ae0b29a68a7384";

  std::string item_key =
      "dictionary-"
      "5d3e90f064798d54e5e53643c4fce0cbb1024aadcad1586cc4b7c1358a530373";

  Casper::GetDictionaryItemResult dictionaryItemResult =
      client.GetDictionaryItem(state_root_hash, item_key);

  TEST_ASSERT(dictionaryItemResult.api_version != "");

  TEST_ASSERT(dictionaryItemResult.dictionary_key != "");
  TEST_ASSERT(dictionaryItemResult.merkle_proof != "");
  TEST_ASSERT(dictionaryItemResult.stored_value.cl_value.has_value());
  TEST_ASSERT(dictionaryItemResult.stored_value.cl_value.value().bytes.size() >
              0);
  TEST_ASSERT(dictionaryItemResult.stored_value.cl_value.value()
                  .cl_type.type_info.has_value());
  uint8_t cl_type_val =
      static_cast<uint8_t>(dictionaryItemResult.stored_value.cl_value.value()
                               .cl_type.type_info.value()
                               .type);
  TEST_ASSERT(cl_type_val == 10);
}

/**
 * @brief Check the "state_get_balance" rpc function
 *
 */
void getBalanceTest() {
  Casper::Client client(CASPER_TEST_ADDRESS);

  std::string purse_uref =
      "uref-54fd72455872082a254b0160e94a86245acd0c441f526688bda1261d0969057a-"
      "007";
  std::string state_root_hash =
      "66eb7e43886c908aae8246ba2d22aa30d21e1c187a38fa3093f14e4a4219dd6c";

  Casper::GetBalanceResult result =
      client.GetAccountBalance(purse_uref, state_root_hash);

  TEST_ASSERT(result.api_version != "");
  TEST_ASSERT(result.balance_value >= 0);
  TEST_ASSERT(result.merkle_proof != "");
}

/**
 * @brief Check the "state_get_auction_info" rpc function
 *
 */
void getAuctionInfoTest() {
  Casper::Client client(CASPER_TEST_ADDRESS);

  std::string block_hash =
      "a5ce9e1ea4ff786cf1eb9dfbe3a79f70ae33d723134a060910a2db80daf85bab";

  Casper::GetAuctionInfoResult auction_result =
      client.GetAuctionInfo(block_hash);

  // tests
  TEST_ASSERT(auction_result.api_version != "");

  TEST_ASSERT(iequals(
      auction_result.auction_state.state_root_hash,
      "fb9847a919b0745e3bea1cc25f3ad4ad5fee0e18fe4bebd303a9e7a93508ddb8"));

  TEST_ASSERT(auction_result.auction_state.block_height == 569706);

  TEST_ASSERT(auction_result.auction_state.era_validators.size() > 0);
  TEST_ASSERT(auction_result.auction_state.era_validators[0].era_id > 0);
  TEST_ASSERT(
      auction_result.auction_state.era_validators[0].validator_weights.size() >
      0);
  TEST_ASSERT(auction_result.auction_state.era_validators[0]
                  .validator_weights[0]
                  .public_key.ToString() != "");
  TEST_ASSERT(auction_result.auction_state.era_validators[0]
                  .validator_weights[0]
                  .weight > 0);

  TEST_ASSERT(auction_result.auction_state.bids.size() > 0);
  TEST_ASSERT(auction_result.auction_state.bids[0].public_key.ToString() != "");

  TEST_ASSERT(auction_result.auction_state.bids[0]
                  .bid.validator_public_key.ToString() != "");
  TEST_ASSERT(
      auction_result.auction_state.bids[0].bid.bonding_purse.ToString() != "");
  TEST_ASSERT(auction_result.auction_state.bids[0].bid.staked_amount > 0);
  TEST_ASSERT(auction_result.auction_state.bids[0].bid.delegation_rate > 0);
}

/// <summary>
/// Check the Casper lower-case convert function
/// </summary>
void stringUtilToLowerTest() {
  std::string str = "Hello World";
  std::string str_lower = "hello world";
  TEST_ASSERT(str_lower == Casper::StringUtil::toLower(str));
}

/// <summary>
/// Check the public key to account hash convert function
/// </summary>
void publicKeyGetAccountHashTest() {
  Casper::PublicKey publicKey = Casper::PublicKey::FromHexString(
      "01cd807fb41345d8dd5a61da7991e1468173acbee53920e4dfe0d28cb8825ac664");

  std::string lower_case_account_hash = publicKey.GetAccountHash();
  Casper::StringUtil::toLower(lower_case_account_hash);

  std::string expected_account_hash =
      "account-hash-"
      "998c5fd4e7b568bedd78e05555c83c61893dc5d8546ce0bec8b30e1c570f21aa";

  TEST_ASSERT(lower_case_account_hash == expected_account_hash);
}

// Optional TODO:
// 1. CryptoUtil functions tests
// 2. Other StringUtil functions tests
// 3. CEP57 Checksum tests

TEST_LIST = {
    {"infoGetPeers", infoGetPeersTest},
    {"chainGetStateRootHash - Height", getStateRootHashBlockHeightTest},
    {"chainGetStateRootHash - Hash", getStateRootHashBlockHashTest},
    {"chainGetStateRootHash - Last Block", getStateRootHashLastBlockTest},
    {"infoGetDeploy", get_deploy_test},
    {"infoGetStatus", getStatusInfoTest},
    {"infoGetBlockTransfers", getBlockTransfersTest},
    {"chainGetBlock", getBlockTest},
    {"chainGetEraInfoBySwitchBlock", getEraInfoBySwitchBlockTest},
    {"stateGetItem", getItemTest},
    {"stateGetDictionaryItem", getDictionaryItemTest},
    {"stateGetBalance", getBalanceTest},
    {"stateGetAuctionInfo(may take a while)", getAuctionInfoTest},
    {"StringUtil - ToLower", stringUtilToLowerTest},
    {"PublicKey - GetAccountHash", publicKeyGetAccountHashTest},
    {NULL, NULL}};
