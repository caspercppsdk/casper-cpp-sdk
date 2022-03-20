#include <algorithm>
#include <iostream>

#include "../src/include/CasperClient.h"  // To use Casper::Client features
#include "../src/include/Types/GlobalStateKey.h"
/// Construct a Casper::Client object
Casper::Client casper_client(CASPER_TEST_ADDRESS);

template <typename T>
void printResult(const T& result, int indent = 2) {
  nlohmann::json resultJSON;
  nlohmann::to_json(resultJSON, result);

  std::cout << resultJSON.dump(indent);
  std::cout << std::endl;
}

/// “info_get_peers” RPC.
void infoGetPeers() {
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "info_get_peers\n";
  /// Call GetNodePeers function from the client object.
  Casper::InfoGetPeersResult peers_result = casper_client.GetNodePeers();

  /// Print the nodes in the network.
  std::cout << "\npeers.size = " << peers_result.peers.size() << "\n";
  // limited by 2 to improve readability
  for (int i = 0; i < std::min(2, static_cast<int>(peers_result.peers.size()));
       i++) {
    /// Print the node ID.
    std::cout << "Peer " << i + 1
              << "\n\tnode_id: " << peers_result.peers[i].node_id;

    /// Print the node IP address.
    std::cout << "\n\taddress: " << peers_result.peers[i].address << "\n";
  }

  std::cout << std::endl;
}

/// “chain_get_state_root_hash” RPC.
void chainGetStateRootHash() {
  std::cout << "-----------------------------------------------";
  std::cout << "\nchain_get_state_root_hash\n";

  /// Call GetStateRootHash function with the height of the block.
  Casper::GetStateRootHashResult height_result =
      casper_client.GetStateRootHash(10);
  std::cout << "\nBlock Height: " << height_result.state_root_hash;

  /// Call GetStateRootHash function with the block hash of the block.
  Casper::GetStateRootHashResult hash_result = casper_client.GetStateRootHash(
      "acc4646f35cc1d59b24381547a4d2dc1c992a202b6165f3bf68d3f23c2b93330");
  std::cout << "\nBlock Hash: " << hash_result.state_root_hash;

  /// Call GetStateRootHash function with empty string.
  Casper::GetStateRootHashResult recent_hash_result =
      casper_client.GetStateRootHash();
  std::cout << "\nMost Recent: " << recent_hash_result.state_root_hash;

  std::cout << std::endl;
}

void infoGetDeploy() {
  // TODO: fill in this function
  std::cout << "-----------------------------------------------";
  std::cout << "\ninfo_get_deploy\n";

  Casper::GetDeployInfoResult deploy_result = casper_client.GetDeployInfo(
      "8e535d2baed76141ab47fd93b04dd61f65a07893b7c950022978a2b29628edd7");
  std::cout << "\napi_version: " << deploy_result.api_version;

  nlohmann::json deployJSON;
  nlohmann::to_json(deployJSON, deploy_result.deploy);
  std::cout << "\ndeploy: " << deployJSON.dump(2);
  std::vector<Casper::ExecutionResult> execution_results =
      deploy_result.execution_results;
  // TODO: uncomment below

  std::cout << "\nexecution_results.size: " << execution_results.size() << "\n";
  for (size_t i = 0;
       i < std::min(2, static_cast<int>(execution_results.size())); i++) {
    std::cout << "ExecutionResult " << i + 1 << "\n";
    nlohmann::json execution_results_json;
    to_json(execution_results_json, execution_results[i]);
    std::cout << execution_results_json.dump(2) << "\n";
  }

  std::cout << std::endl;
}

void infoGetStatus() {
  std::cout << "-----------------------------------------------";
  std::cout << "\ninfo_get_status\n";

  /// Call GetStatusInfo function.
  Casper::GetStatusResult status_result = casper_client.GetStatusInfo();
  nlohmann::json j;
  to_json(j, status_result);
  std::cout << "\n" << j.dump() << "\n";
}

void chainGetBlockTransfers() {
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "chain_get_block_transfers" << std::endl;

  /// Call GetBlockTransfers function.
  // https://testnet.cspr.live/deploy/8e535d2baed76141ab47fd93b04dd61f65a07893b7c950022978a2b29628edd7
  Casper::GetBlockTransfersResult transfersResult =
      casper_client.GetBlockTransfers(
          "35f86b6ab5e13b823daee5d23f3373f6b35048e0b0ea993adfadc5ba8ee7aae5");
  std::cout << "\napi_version: " << transfersResult.api_version;

  if (transfersResult.block_hash.has_value()) {
    std::cout << "\nblock_hash: " << transfersResult.block_hash.value() << "\n";
  }

  if (transfersResult.transfers.has_value()) {
    std::vector<Casper::Transfer> transfers = transfersResult.transfers.value();
    std::cout << "\ntransfers.size = " << transfers.size();
    // limited by 2 to improve readability
    for (std::size_t i = 0; i < std::min(2, static_cast<int>(transfers.size()));
         i++) {
      std::cout << "\nTransfer " << i + 1
                << "\n\tdeploy_hash: " << transfers[i].deploy_hash
                << "\n\tfrom: " << transfers[i].from;

      if (transfers[i].to.has_value()) {
        std::cout << "\n\tto: " << transfers[i].to.value() << "\n";
      }

      std::cout << "\n\tsource: " << transfers[i].source.ToString()
                << "\n\ttarget: " << transfers[i].target.ToString()
                << "\n\tamount: " << transfers[i].amount
                << "\n\tgas: " << transfers[i].gas;

      if (transfers[i].id.has_value()) {
        std::cout << "\n\tid: " << transfers[i].id.value() << "\n";
      }
    }
  }

  std::cout << std::endl;
}

void chainGetBlock() {
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "chain_get_block" << std::endl;

  /// Call GetBlockResult rpc function.
  Casper::GetBlockResult blockResult = casper_client.GetBlock(
      "acc4646f35cc1d59b24381547a4d2dc1c992a202b6165f3bf68d3f23c2b93330");
  // or casper_client.GetBlock(532041);

  std::cout << "\napi_version: " << blockResult.api_version;

  if (!blockResult.block.body.proposer.empty()) {
    std::cout << "\nproposer: " << blockResult.block.body.proposer
              << "\nhash: " << blockResult.block.hash << "\naccumulated_seed: "
              << blockResult.block.header.accumulated_seed
              << "\nbody_hash: " << blockResult.block.header.body_hash
              << "\nera_end: " << blockResult.block.header.era_end
              << "\nera_id: " << blockResult.block.header.era_id
              << "\nheight: " << blockResult.block.header.height
              << "\nparent_hash: " << blockResult.block.header.parent_hash
              << "\nprotocol_version: "
              << blockResult.block.header.protocol_version
              << "\nrandom_bit: " << blockResult.block.header.random_bit
              << "\nstate_root_hash: "
              << blockResult.block.header.state_root_hash
              << "\ntimestamp: " << blockResult.block.header.timestamp;

    std::cout << "\n";

    std::cout << "\nblock.body.deploy_hashes.size = "
              << blockResult.block.body.deploy_hashes.size();
    // limited by 2 to improve readability
    for (std::size_t i = 0;
         i < std::min(2, static_cast<int>(
                             blockResult.block.body.deploy_hashes.size()));
         i++) {
      std::cout << "\nDeploy hash: " << blockResult.block.body.deploy_hashes[i];
    }

    std::cout << "\n";

    std::cout << "\nblock.body.transfer_hashes.size = "
              << blockResult.block.body.transfer_hashes.size();
    // limited by 2 to improve readability
    for (std::size_t i = 0;
         i < std::min(2, static_cast<int>(
                             blockResult.block.body.transfer_hashes.size()));
         i++) {
      std::cout << "\nTransfer Hash: "
                << blockResult.block.body.transfer_hashes[i];
    }

    std::cout << "\n";

    std::cout << "\nblock.proofs.size = " << blockResult.block.proofs.size();
    // limited by 2 to improve readability
    for (std::size_t i = 0;
         i < std::min(2, static_cast<int>(blockResult.block.proofs.size()));
         i++) {
      std::cout << "\n"
                << i + 1
                << ".Proof\n\tPK: " << blockResult.block.proofs[i].public_key
                << "\n\tSignature: " << blockResult.block.proofs[i].signature;
      std::cout << std::endl;
    }
  }

  std::cout << std::endl;
}

void chainGetEraInfoBySwitchBlock() {
  std::cout << "-----------------------------------------------\n";
  std::cout << "chain_get_era_info_by_switch_block" << std::endl;

  /// Call chain_get_era_info_by_switch_block rpc function.
  Casper::GetEraInfoResult eraInfoResult =
      casper_client.GetEraInfoBySwitchBlock(
          "d2077716e5b8796723c5720237239720f54e6ada54e3357f2c4896f2a51a6d8f");

  printResult(eraInfoResult);
}

void stateGetItem() {
  std::cout << "-----------------------------------------------\n";
  std::cout << "state_get_item" << std::endl;
  Casper::GetItemResult itemResult = casper_client.GetItem(
      "39f2800688b94f68ca640b26c7d0f50a90d2ce9af55c9484e66151b544345303",
      "transfer-"
      "9f5fe878c29fc3bf537c0509ec5abe1781a72bb6a3197a440e3e68247fba5909");
  nlohmann::json itemJSON;
  to_json(itemJSON, itemResult.stored_value);
  std::cout << itemJSON.dump(2) << std::endl;
}

void stateGetDictionaryItem() {
  std::cout << "-----------------------------------------------\n";
  std::cout << "state_get_dictionary_item" << std::endl;

  std::string state_root_hash =
      "322b8d17faea2ee780b9b952a25a86520d36a78e20113f0658ae0b29a68a7384";

  std::string item_key =
      "dictionary-"
      "5d3e90f064798d54e5e53643c4fce0cbb1024aadcad1586cc4b7c1358a530373";

  Casper::GetDictionaryItemResult dictionaryItemResult =
      casper_client.GetDictionaryItem(state_root_hash, item_key);

  nlohmann::json itemJSON;
  to_json(itemJSON, dictionaryItemResult.stored_value);
  std::cout << itemJSON.dump(2) << std::endl;
}

void stateGetBalance() {
  std::cout << "-----------------------------------------------\n";
  std::cout << "state_get_balance" << std::endl;

  /// Call state_get_balance rpc function.
  Casper::GetBalanceResult balanceResult = casper_client.GetAccountBalance(
      "uref-54fd72455872082a254b0160e94a86245acd0c441f526688bda1261d0969057a-"
      "007",
      "66eb7e43886c908aae8246ba2d22aa30d21e1c187a38fa3093f14e4a4219dd6c");
  std::cout << "\nbalanceResult: " << balanceResult.balance_value;
  std::cout << std::endl;
}

void stateGetAuctionInfo() {
  // TODO: implement
  std::cout << "-----------------------------------------------\n";
  std::cout << "state_get_auction_info" << std::endl;

  /// Call GetStateRootHash function with the height of the block.
  Casper::GetAuctionInfoResult auction_result = casper_client.GetAuctionInfo(
      "a5ce9e1ea4ff786cf1eb9dfbe3a79f70ae33d723134a060910a2db80daf85bab");

  std::cout << "\napi_version: " << auction_result.api_version;

  std::cout << "\nauction_state"
            << "\nstate_root_hash: "
            << auction_result.auction_state.state_root_hash
            << "\nblock_height: " << auction_result.auction_state.block_height;

  std::cout << "\n";

  std::cout << "\nera_validators.size = "
            << auction_result.auction_state.era_validators.size() << "\n";
  // limited by 2 to improve readability
  for (size_t i = 0;
       i < std::min(2, static_cast<int>(
                           auction_result.auction_state.era_validators.size()));
       i++) {
    std::cout << "Era ID: "
              << auction_result.auction_state.era_validators[i].era_id;

    std::cout << "\n\tera_validators.validator_weights.size =  "
              << auction_result.auction_state.era_validators[i]
                     .validator_weights.size();
    // limited by 2 to improve readability
    for (size_t j = 0;
         j < std::min(2, static_cast<int>(
                             auction_result.auction_state.era_validators[i]
                                 .validator_weights.size()));
         j++) {
      std::cout << "\n\tValidator " << j + 1;
      std::cout << "\n\t\tPublic Key: "
                << auction_result.auction_state.era_validators[i]
                       .validator_weights[j]
                       .public_key
                << "\n\t\tWeight: "
                << auction_result.auction_state.era_validators[i]
                       .validator_weights[j]
                       .weight.toString();
    }
    std::cout << "\n";
  }

  std::cout << "\n";

  std::cout << "\nbids.size = " << auction_result.auction_state.bids.size();
  // limited by 2 to improve readability
  for (size_t i = 0;
       i <
       std::min(2, static_cast<int>(auction_result.auction_state.bids.size()));
       i++) {
    Casper::ValidatorBid cur_validator_bid =
        auction_result.auction_state.bids[i];

    std::cout << "\nvalidator_public_key: "
              << cur_validator_bid.bid.validator_public_key
              << "\nbonding_purse: "
              << cur_validator_bid.bid.bonding_purse.ToString()
              << "\nstaked_amount: "
              << cur_validator_bid.bid.staked_amount.toString()
              << "\ndelegation_rate: "
              << unsigned(cur_validator_bid.bid.delegation_rate);
    if (cur_validator_bid.bid.vesting_schedule.has_value()) {
      Casper::VestingSchedule cur_vesting_schedule =
          cur_validator_bid.bid.vesting_schedule.value();
      std::cout << "\nvesting_schedule initial_release_timestamp_millis: "
                << cur_vesting_schedule.initial_release_timestamp_millis
                << " locked_amounts: \n";
      for (size_t j = 0; j < cur_vesting_schedule.locked_amounts.size(); j++) {
        std::cout << j + 1 << ". "
                  << cur_vesting_schedule.locked_amounts[j].toString() << "\n";
      }
    }
    std::cout << "\ninactive: " << std::boolalpha
              << cur_validator_bid.bid.inactive << "\n";
  }

  std::cout << std::endl;
}

int main() {
  // infoGetPeers();

  // chainGetStateRootHash();

  // Milestone 2
  // infoGetDeploy();

  infoGetStatus();

  // chainGetBlockTransfers();

  // chainGetBlock();

  // chainGetEraInfoBySwitchBlock();

  // stateGetItem();

  // stateGetDictionaryItem();

  // stateGetBalance();

  // stateGetAuctionInfo();

  // Milestone 3
  // PutDeploy(); TODO: implement
}