#include "TestBase.hpp"

#include "TempFileHandler.hpp"
#include "ByteSerializers/DeployByteSerializer.h"
#include "Types/ED25519Key.h"
#include "data/TestSourceSecretKey.hpp"
#include "data/TestTargetSecretKey.hpp"

namespace
{
    const std::string pub_key = "02035724e2530c5c8f298ba41fe1cafa28294ab7b04d4f1ade025a4a268138570b3a";
    const std::string pub_key_target = "02032601c0b516c4d7ffa6cd1e657778f330f9f102873bf629d2d5016a48c93e9832";
    const std::string amount_str = "1000000000";

    std::string getTimestampNow() {
        using namespace std::chrono;

        const auto now_ms = time_point_cast<milliseconds>(system_clock::now());
        const auto now_s = time_point_cast<seconds>(now_ms);
        const auto millis = now_ms - now_s;
        const auto c_now = system_clock::to_time_t(now_s);

        std::stringstream ss;
        ss << std::put_time(gmtime(&c_now), "%FT%T") << '.' << std::setfill('0')
           << std::setw(3) << millis.count() << 'Z';

        std::string timestamp_str = ss.str();
        return timestamp_str;
    }

    Casper::DeployHeader getHeader(const std::string& pubKey)
    {
        return {Casper::PublicKey::FromHexString(pubKey),
                getTimestampNow(), "30m", 1, "", {}, "casper-test"};
    }

    Casper::PutDeployResult putDeploy(Casper::Deploy& deploy, Casper::Secp256k1Key& secp256k1Key)
    {
        using namespace Casper;
        Client client(CASPER_TEST_ADDRESS);
        Deploy dp(deploy.header, deploy.payment, deploy.session);
        dp.Sign(secp256k1Key);
        nlohmann::json j;
        to_json(j, dp);
        PutDeployResult res = client.PutDeploy(dp);
        return res;
    }

    void sendCoins(const std::string& sender, const std::string& receiver, const std::string& amountStr,
                   const std::string& privateKeyPem)
    {
        using namespace Casper;

        Casper::PublicKey target_key = Casper::PublicKey::FromHexString(receiver);
        uint512_t amount = u512FromDec(amountStr);

        // create a payment
        ModuleBytes payment(amount);

        // create transfer executable deploy item
        TransferDeployItem session(u512FromDec("2845678925"), AccountHashKey(target_key),
                                   123456789012345u, true);

        // Create deploy object
        Deploy deploy(getHeader(sender), payment, session);
        Casper::Secp256k1Key secp256k1Key(privateKeyPem);
        std::string signature = secp256k1Key.sign(deploy.hash);
        putDeploy(deploy, secp256k1Key);
    }
}

namespace Casper {
using namespace std::literals;
class RpcTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // create a temp file
        // tempFileHandler = std::make_unique<TempFileHandler>();
        // tempFileHandler->createTempFile();
    }

    // void TearDown() override
    // {
    //     // remove the temp file
    //     tempFileHandler->removeTempFile();
    // }

    bool compareString(const std::string& str1, const std::string& str2)
    {
      bool areEqual = StringUtil::toLower(str1) == StringUtil::toLower(str2);
      EXPECT_TRUE(areEqual);
      return areEqual;
    }

    // std::unique_ptr<TempFileHandler> tempFileHandler;
    Client client{"http://138.201.54.44:7777"};

};

/**
 * @brief Check the "info_get_peers" rpc function. The size of the return
 * value should be greater than 0.
 *
 */
TEST_F(RpcTest, infoGetPeers)
{
    auto result = client.GetNodePeers();
    size_t result_size = result.peers.size();

    EXPECT_GT(result_size, 0);
}

/**
 * @brief Check the "get_state_root_hash" rpc function with an example height.
 * Compare the result with the expected hash of the state.
 *
 */
 TEST_F(RpcTest, chainGetStateRootHash_blockHeight)
 {
  uint64_t blockHeight = 10;
  std::string result = client.GetStateRootHash(blockHeight).state_root_hash;
  compareString(result, "4d180287e6eb3dad5173864e30d7653c01fcdef8bc3ee31db4a0707367154ccf");
 }

/**
 * @brief Check "get_state_root_hash" rpc function with an
 * invalid height.
 *
 *
 */
TEST_F(RpcTest, chainGetStateRootHash_invalidBlockHeight)
{
  uint64_t blockHeight = 100000000;
  EXPECT_THROW(client.GetStateRootHash(blockHeight), jsonrpccxx::JsonRpcException);
}


/**
 * @brief Check the "get_state_root_hash" rpc function with an example block
 * hash. Compare the result with the expected hash of the state.
 *
 */
TEST_F(RpcTest, chainGetStateRootHash_blockHash)
{
  std::string blockHash =
      "9511adf5ed36ccba48d71840fd558d4397c9eb0470d1e25711b5419632a6f55a";
  std::string result = client.GetStateRootHash(blockHash).state_root_hash;
  compareString(result, "9aa3c10d4db2e02adb464458c7a09d1df2ed551be02d2c7bbdbe847d3731e84f");
}

/**
 * @brief Check the "get_state_root_hash" rpc function without a variable.
 * Compare the result with an empty string.
 *
 */
TEST_F(RpcTest, chainGetStateRootHash_emptyParameter)
{
  std::string result = client.GetStateRootHash().state_root_hash;
  EXPECT_NE(result, "");
}

/**
 * @brief Check the "info_get_deploy" rpc function
 *
 */
TEST_F(RpcTest, infoGetDeploy_DeployHash)
{
  std::string deployHash =
      "8e535d2baed76141ab47fd93b04dd61f65a07893b7c950022978a2b29628edd7";

  nlohmann::json deployResult = client.GetDeployInfo(deployHash);

  EXPECT_NE(deployResult.at("api_version"), "");
  EXPECT_NE(deployResult.count("deploy"), 0);

  nlohmann::json& deployInfo = deployResult.at("deploy");
  compareString(deployInfo.at("hash"), deployHash);

  nlohmann::json& deployHeader = deployInfo.at("header");
  compareString(deployHeader.at("account"), "011fa7f49ed9887f1bd0bceac567dd6a38087e2896411d74d3f8d1c03a3f325828");
  compareString(deployHeader.at("body_hash"), "11f5a10f791fd6ac8b12d52298b7d1db7bd91e8c15b5d1330fd16d792257693c");
  compareString(deployHeader.at("chain_name"), "casper-test");
  EXPECT_EQ(deployHeader.at("gas_price"), 1);
}

/**
 * @brief Check the "info_get_deploy" rpc function with an invalid deploy hash
 * parameter
 *
 */
TEST_F(RpcTest, infoGetDeploy_invalidDeployHash)
{
  std::string deployHash = "ffffffffffffffffffff";
  EXPECT_THROW(client.GetDeployInfo(deployHash), jsonrpccxx::JsonRpcException);
}


// /**
//  * @brief Check the "info_get_status" rpc function. Check the result
//  * variables.
//  *
//  */
TEST_F(RpcTest, infoGetStatus_emptyParameter)
{
  GetStatusResult result = client.GetStatusInfo();

  EXPECT_NE(result.api_version, "");
  EXPECT_NE(result.starting_state_root_hash, "");
  compareString(result.chainspec_name, "casper-test");

  if (result.our_public_signing_key.has_value()) {
    EXPECT_NE(result.our_public_signing_key.value().ToString(), "");
  }

  if (result.last_added_block_info.has_value()) {
    auto& last_block = result.last_added_block_info.value();
    EXPECT_NE(last_block.hash, "");
    EXPECT_GE(last_block.height, 0);
    EXPECT_NE(last_block.timestamp, "");
    EXPECT_NE(last_block.state_root_hash, "");
    EXPECT_NE(last_block.creator.ToString(), "");
  }

  if (result.peers.size() > 0) {
    EXPECT_NE(result.peers[0].address, "");
    EXPECT_NE(result.peers[0].node_id, "");
  }

  EXPECT_NE(result.build_version, "");
  EXPECT_NE(result.uptime, "");
}

/**
 * @brief Check the "chain_get_block_transfers" rpc function.
 *
 */
TEST_F(RpcTest, chainGetBlockTransfers_blockHash)
{
  // Call the rpc function
  std::string block_hash =
      "35f86b6ab5e13b823daee5d23f3373f6b35048e0b0ea993adfadc5ba8ee7aae5";
  GetBlockTransfersResult result = client.GetBlockTransfers(block_hash);

  // Expected Values
  std::string expected_block_hash = block_hash;
  uint512_t expected_amount = u512FromDec("199000000000");
  std::string expected_deploy_hash =
      "8e535d2baed76141ab47fd93b04dd61f65a07893b7c950022978a2b29628edd7";
  std::string expected_from =
      "account-hash-"
      "308d2a0eCF66bDAcAC5Cf6184C732D83DCeB48A859169e5680FE17cF32Bb974F";
  uint512_t expected_gas = u512FromDec("0");
  std::string expected_source =
      "uref-5ce1d189e8ccafdd5a959088ffd870f54b29bd5afeb05950dddcc12ec7dcbe90-"
      "007";
  std::string expected_target =
      "uref-c9733355d61aa2a36721d9d1081eebcfe5dde94f82386b3d75163fee894d292a-"
      "007";

  EXPECT_NE(result.api_version, "");

  EXPECT_TRUE(result.block_hash.has_value());
  compareString(result.block_hash.value(), expected_block_hash);

  // check transfers
  EXPECT_TRUE(result.transfers.has_value());
  EXPECT_GT(result.transfers.value().size(), 0);

  auto& transfers = result.transfers.value();
  auto test_transfer =
      std::find_if(transfers.begin(), transfers.end(), [&](const Transfer& x) {
        return iequals(x.deploy_hash, expected_deploy_hash);
      });

  // TEST_ASSERT(test_transfer != transfers.end());
  EXPECT_NE(test_transfer, transfers.end());

  // Actual Values
  uint512_t current_amount = test_transfer->amount;
  std::string current_deploy_hash = test_transfer->deploy_hash;
  std::string current_from = test_transfer->from.ToString();
  uint512_t current_gas = test_transfer->gas;
  std::string current_source = test_transfer->source.ToString();
  std::string current_target = test_transfer->target.ToString();

  // tests for the first transfer
  EXPECT_EQ(current_amount, expected_amount);
  compareString(current_deploy_hash, expected_deploy_hash);
  compareString(current_from, expected_from);
  EXPECT_EQ(current_gas, expected_gas);
  compareString(current_source, expected_source);
  compareString(current_target, expected_target);
}


// /**
//  * @brief Check the "chain_get_block" rpc function
//  *
//  */
TEST_F(RpcTest, chainGetBlock_blockHash)
{
  std::string block_hash = "acc4646f35cc1d59b24381547a4d2dc1c992a202b6165f3bf68d3f23c2b93330";
  GetBlockResult blockResult = client.GetBlock(block_hash);

  EXPECT_NE(blockResult.api_version, "");
  EXPECT_TRUE(blockResult.block.has_value());

  auto& current_block = blockResult.block.value();
  compareString(current_block.hash, block_hash);

  // block header
  compareString(current_block.header.parent_hash, "e23b5f98258aff36716a8f60ca8d57c049216eedd88e6c7e14df7a6cfbadca73");
  compareString(current_block.header.state_root_hash, "f5abb3964382e0dde4bc3ec38414f43f325f5dcc6493d5a7c4037972793fb302");
  compareString(current_block.header.body_hash, "e1786ce884cf41abbc758b0795ee3223daec5fb8015791ced0f8ee66deec8ee3");
  compareString(current_block.header.accumulated_seed, "35b5d33db0b43df3971831880f51023b37a468ad54494316ec26af4c61904532");

  EXPECT_NE(current_block.header.timestamp, "");
  EXPECT_NE(current_block.header.era_id, 0);
  EXPECT_EQ(current_block.header.height, 532041);
  EXPECT_NE(current_block.header.protocol_version, "");

  // // block body
  EXPECT_GE(current_block.body.deploy_hashes.size(), 0);
  compareString(current_block.body.proposer.ToString(), "01cd807fb41345d8dD5A61da7991e1468173acbEE53920E4DFe0D28Cb8825AC664");

  EXPECT_GE(current_block.body.transfer_hashes.size(), 0);

  // // block proofs
  EXPECT_GT(current_block.proofs.size(), 0);
  EXPECT_NE(current_block.proofs[0].public_key.ToString(), "");
  EXPECT_NE(current_block.proofs[0].signature.ToString(), "");
}

// /**
//  * @brief Check the "chain_get_era_info_by_switch_block" rpc function
//  *
//  */
TEST_F(RpcTest, chainGetEraInfoBySwitchBlock_blockHash)
{
  GetEraInfoResult result = client.GetEraInfoBySwitchBlock(
      "d2077716e5b8796723c5720237239720f54e6ada54e3357f2c4896f2a51a6d8f");

  EXPECT_NE(result.api_version, "");
  EXPECT_TRUE(result.era_summary.has_value());
  EXPECT_NE(result.era_summary.value().era_id, 0);
  EXPECT_NE(result.era_summary.value().block_hash, "");
  EXPECT_NE(result.era_summary.value().merkle_proof, "");
  EXPECT_NE(result.era_summary.value().state_root_hash, "");
  EXPECT_TRUE(result.era_summary.value().stored_value.era_info.has_value());
  EXPECT_GT(result.era_summary.value().stored_value.era_info.value().seigniorage_allocations.size(), 0);

  int validator_cnt = 0;
  int delegator_cnt = 0;

  for (int i = 0; i < result.era_summary.value().stored_value.era_info.value().seigniorage_allocations.size(); i++) 
  {
    if (delegator_cnt == 1 && validator_cnt == 1) 
    {
      break;
    }

    bool is_delegator = result.era_summary.value().stored_value.era_info.value().seigniorage_allocations[i].is_delegator;

    if (is_delegator == true && delegator_cnt == 0) 
    {
      delegator_cnt++;
      EXPECT_NE(result.era_summary.value().stored_value.era_info.value().seigniorage_allocations[i].delegator_public_key.ToString(), "");
      EXPECT_GE(result.era_summary.value().stored_value.era_info.value().seigniorage_allocations[i].amount, 0);
    }
    else if (is_delegator == false && validator_cnt == 0) 
    {
      validator_cnt++;
      EXPECT_NE(result.era_summary.value().stored_value.era_info.value().seigniorage_allocations[i].validator_public_key.ToString(), "");
      EXPECT_GE(result.era_summary.value().stored_value.era_info.value().seigniorage_allocations[i].amount, 0);
    }
  }
}

// /**
//  * @brief Check the "state_get_item" rpc function
//  *
//  */
TEST_F(RpcTest, stateGetItem_key)
{
  std::string state_root_hash = "39f2800688b94f68ca640b26c7d0f50a90d2ce9af55c9484e66151b544345303";
  std::string key = "transfer-9f5fe878c29fc3bf537c0509ec5abe1781a72bb6a3197a440e3e68247fba5909";

  GetItemResult result = client.GetItem(state_root_hash, key);

  EXPECT_NE(result.api_version, "");
  EXPECT_NE(result.merkle_proof, "");
  EXPECT_TRUE(result.stored_value.transfer.has_value());

  auto& current_transfer = result.stored_value.transfer.value();

  compareString(current_transfer.deploy_hash, "8e535d2baed76141ab47fd93b04dd61f65a07893b7c950022978a2b29628edd7");
  compareString(current_transfer.from.ToString(), "account-hash-308d2a0eCF66bDAcAC5Cf6184C732D83DCeB48A859169e5680FE17cF32Bb974F");
  compareString(current_transfer.source.ToString(), "uref-5ce1d189e8ccafdd5a959088ffd870f54b29bd5afeb05950dddcc12ec7dcbe90-007");
  compareString(current_transfer.target.ToString(), "uref-c9733355d61aa2a36721d9d1081eebcfe5dde94f82386b3d75163fee894d292a-007");

  EXPECT_EQ(current_transfer.amount, 199000000000);
  EXPECT_EQ(current_transfer.gas, 0);
}

// /**
//  * @brief Check the "state_get_item" rpc function with an invalid key and a
//  * state root hash
//  *
//  */
TEST_F(RpcTest, stateGetItem_invalidKey)
{
  EXPECT_THROW(client.GetItem("NOT_EXIST_STATE_ROOT_HASH", "NOT_EXIST_KEY"), jsonrpccxx::JsonRpcException);
}

// /**
//  * @brief Check the "state_get_dictionary_item" rpc function by URef
//  *
//  */
TEST_F(RpcTest, stateGetDictionaryItem_key)
{
  std::string state_root_hash = "322b8d17faea2ee780b9b952a25a86520d36a78e20113f0658ae0b29a68a7384";
  std::string item_key = "dictionary-5d3e90f064798d54e5e53643c4fce0cbb1024aadcad1586cc4b7c1358a530373";
  nlohmann::json dictionaryItemResult = client.GetDictionaryItem(state_root_hash, item_key);

  EXPECT_NE(dictionaryItemResult.at("api_version"), "");
  EXPECT_NE(dictionaryItemResult.at("dictionary_key"), "");
  EXPECT_NE(dictionaryItemResult.at("merkle_proof"), "");

  EXPECT_FALSE(dictionaryItemResult.at("stored_value").at("CLValue").is_null());
  compareString(dictionaryItemResult.at("stored_value").at("CLValue").at("bytes"), "090000006162635F76616C7565");
  compareString(dictionaryItemResult.at("stored_value").at("CLValue").at("cl_type"), "String");
}

// /**
//  * @brief Check the "state_get_balance" rpc function
//  *
//  */
TEST_F(RpcTest, stateGetBalance_uref)
{
  std::string purse_uref = "uref-54fd72455872082a254b0160e94a86245acd0c441f526688bda1261d0969057a-007";
  std::string state_root_hash = "66eb7e43886c908aae8246ba2d22aa30d21e1c187a38fa3093f14e4a4219dd6c";
  GetBalanceResult result = client.GetAccountBalance(purse_uref, state_root_hash);

  EXPECT_NE(result.api_version, "");
  EXPECT_GE(result.balance_value, 0);
  EXPECT_NE(result.merkle_proof, "");
}

// /**
//  * @brief Check the "state_get_balance" rpc function with an invalid uref and
//  * a state root hash
//  *
//  */
TEST_F(RpcTest, stateGetBalance_invalidUref)
{
  EXPECT_THROW(client.GetAccountBalance("NOT_EXIST_UREF", "NOT_EXIST_STATE_ROOT_HASH"), jsonrpccxx::JsonRpcException);
}


// /**
//  * @brief Check the "state_get_auction_info" rpc function
//  *
//  */
TEST_F(RpcTest, stateGetAuctionInfo_blockHash)
{
  std::string block_hash = "a5ce9e1ea4ff786cf1eb9dfbe3a79f70ae33d723134a060910a2db80daf85bab";
  GetAuctionInfoResult auction_result = client.GetAuctionInfo(block_hash);

  EXPECT_NE(auction_result.api_version, "");
  EXPECT_EQ(auction_result.auction_state.state_root_hash, "fb9847a919b0745e3bea1cc25f3ad4ad5fee0e18fe4bebd303a9e7a93508ddb8");
  EXPECT_EQ(auction_result.auction_state.block_height, 569706);

  EXPECT_GT(auction_result.auction_state.era_validators.size(), 0);
  EXPECT_GT(auction_result.auction_state.era_validators[0].era_id, 0);
  EXPECT_GT(auction_result.auction_state.era_validators[0].validator_weights.size(), 0);
  EXPECT_NE(auction_result.auction_state.era_validators[0].validator_weights[0].public_key.ToString(), "");
  EXPECT_GT(auction_result.auction_state.era_validators[0].validator_weights[0].weight, 0);

  EXPECT_GT(auction_result.auction_state.bids.size(), 0);
  EXPECT_NE(auction_result.auction_state.bids[0].public_key.ToString(), "");
  EXPECT_NE(auction_result.auction_state.bids[0].bid.validator_public_key.ToString(), "");
  EXPECT_NE(auction_result.auction_state.bids[0].bid.bonding_purse.ToString(), "");
  EXPECT_GT(auction_result.auction_state.bids[0].bid.staked_amount, 0);
  EXPECT_GT(auction_result.auction_state.bids[0].bid.delegation_rate, 0);
}

TEST_F(RpcTest, putDeploy_transfer)
{
  TempFileHandler sourceKeyFile{sourceSecretKey, "sourceSecretKey"};
  TempFileHandler targetKeyFile{targetSecretKey, "targetSecretKey"};
  sendCoins(pub_key, pub_key_target, amount_str, sourceKeyFile.getPath());
  sendCoins(pub_key_target, pub_key, amount_str, targetKeyFile.getPath());
}

TEST_F(RpcTest, putDeploy_storedContractByName)
{
  uint512_t amount = u512FromDec("15000000000");
  ModuleBytes payment(amount);

  NamedArg arg1("target", CLValue::ByteArray("0203297ebdcc8cb840e6e5ffb427420ec754ac35364c502f4ac58b0ffea799e57f11"));
  uint512_t amount2 = u512FromDec("100000000000");
  NamedArg arg2("amount", CLValue::U512(amount2));
  std::vector<NamedArg> y_args = {arg1, arg2};
  StoredContractByName scbn("faucet", "call_faucet", y_args);

  Deploy deploy(getHeader(pub_key), payment, scbn);

  TempFileHandler sourceKeyFile{sourceSecretKey, "sourceSecretKey"};
  Casper::Secp256k1Key secp256k1Key(sourceKeyFile.getPath());

  putDeploy(deploy, secp256k1Key);
}

TEST_F(RpcTest, putDeploy_storedContractByHash)
{
  uint512_t amount = u512FromDec("5000000000");
  ModuleBytes payment(amount);
  StoredContractByHash scbh("e3523602448b6085b861890b1c214181e2c1a7bdd2b23424b1941d1301256517", "unlock_cspr", {NamedArg("receipient_publickey", CLValue::String("01f28f169dad17315a03d15e16aa93d5342303ae11f15c68aadfdab3df31b0fcbf")), NamedArg("bsc_transaction_hash", CLValue::String("0xd6e7f5aa561e069c385d0f63a3c8dc5501f63d3616c361749e5efab9776fa33e")), NamedArg("amount", CLValue::U512("33780000000"))});
  Deploy deploy(getHeader(pub_key), payment, scbh);
  TempFileHandler sourceKeyFile{sourceSecretKey, "sourceSecretKey"};
  Casper::Secp256k1Key secp256k1Key(sourceKeyFile.getPath());
  putDeploy(deploy, secp256k1Key);
}

// /**
//  * @brief Check the "query_global_state" rpc function
//  *
//  */
TEST_F(RpcTest, queryGlobalState_key)
{
  std::string blockHash = "a55471527f5b3aa75f8e9c26b781369623d24ada613e09ed341bb56968b7ede1";
  std::string key = "transfer-b243c65eb43d304c74282c33a835eef25da2760f978f451e49d344cd47fcc466";

  QueryGlobalStateResult result = client.QueryGlobalStateWithBlockHash(key, blockHash);

  EXPECT_NE(result.api_version, "");
  EXPECT_NE(result.merkle_proof, "");

  nlohmann::json res;
  nlohmann::to_json(res, result);

  // TODO: Add more checks
}

TEST_F(RpcTest, globalStateKey_simple)
{
  GlobalStateKey key, key2;
  key.key = "uref-2f9ac53033ea0b3bae7df8047be450478b69b48d91db7243791b26598af9fcf0-007";
  nlohmann::json j;
  to_json(j, key);
  from_json(j, key2);
  compareString(key.ToString(), key2.ToString());
}

}  // namespace Casper
