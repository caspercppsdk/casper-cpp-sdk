#include <iostream>

#include <algorithm>
#include "../src/include/CasperClient.h"  // To use Casper::Client features
#include "../src/include/Types/GlobalStateKey.h"
/// Construct a Casper::Client object
Casper::Client casper_client(CASPER_TEST_ADDRESS);

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

  std::cout << std::endl;
}

void infoGetStatus() {
  std::cout << "-----------------------------------------------";
  std::cout << "\ninfo_get_status\n";

  /// Call GetStatusInfo function.
  Casper::GetStatusResult status_result = casper_client.GetStatusInfo();
  std::cout << "\napi_version: " << status_result.api_version;
  std::cout << "\nchainspec_name: " << status_result.chainspec_name;
  std::cout << "\nstarting_state_root_hash: "
            << status_result.starting_state_root_hash;

  std::cout << "\n";

  std::cout << "\npeers.size = " << status_result.peers.size() << "\n";
  // limited by 2 to improve readability
  for (std::size_t i = 0;
       i < std::min(2, static_cast<int>(status_result.peers.size())); i++) {
    std::cout << "Peer " << std::to_string(i + 1)
              << "\n\tnode_id: " << status_result.peers[i].node_id
              << "\n\taddress: " << status_result.peers[i].address << "\n";
  }

  if (status_result.last_added_block_info.has_value()) {
    Casper::BlockInfo last_added_block_info =
        status_result.last_added_block_info.value();

    std::cout << "\nBlock info: creator: " << last_added_block_info.creator
              << "\nera_id: " << last_added_block_info.era_id
              << "\nhash: " << last_added_block_info.hash
              << "\nheight: " << last_added_block_info.height
              << "\nstate_root_hash: " << last_added_block_info.state_root_hash
              << "\ntimestamp: " << last_added_block_info.timestamp;
  }

  std::cout << "\n";

  if (status_result.our_public_signing_key.has_value()) {
    std::cout << "\nour_public_signing_key: "
              << status_result.our_public_signing_key.value() << "\n";
  }

  if (status_result.round_length.has_value()) {
    std::cout << "\nround_length: " << status_result.round_length.value()
              << "\n";
  }

  if (status_result.next_upgrade.has_value()) {
    std::cout << "\next_upgrade: " << status_result.next_upgrade.value()
              << "\n";
  }

  std::cout << "\nbuild_version: " << status_result.build_version;
  std::cout << "\nuptime: " << status_result.uptime;

  std::cout << std::endl;
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
          "acc4646f35cc1d59b24381547a4d2dc1c992a202b6165f3bf68d3f23c2b93330");
  std::cout << "\napi_version: " << eraInfoResult.api_version;

  if (eraInfoResult.era_summary.has_value()) {
    Casper::EraSummary eraSummary = eraInfoResult.era_summary.value();

    std::cout << "\nblock_hash: " << eraSummary.block_hash
              << "\nera_id: " << eraSummary.era_id
              << "\nmerkle_proof: " << eraSummary.merkle_proof
              << "\nstate_root_hash: " << eraSummary.state_root_hash
              << "\nstored_value: ";
    // TODO: add a toString function to the stored value class
    // << eraInfoResult.era_summary.stored_value;  // TODO: std::visit
    // ToString
  }

  std::cout << std::endl;
}

void stateGetItem() {
  // TODO: implement
  std::cout << "-----------------------------------------------\n";
  std::cout << "state_get_item" << std::endl;

  std::cout << std::endl;
}

void stateGetDictionaryItem() {
  // TODO: implement
  std::cout << "-----------------------------------------------\n";
  std::cout << "state_get_dictionary_item" << std::endl;

  std::cout << std::endl;
}

void stateGetBalance() {
  std::cout << "-----------------------------------------------\n";
  std::cout << "state_get_balance" << std::endl;

  /// Call state_get_balance rpc function.
  Casper::GetBalanceResult balanceResult = casper_client.GetAccountBalance(
      "uref-ca7f8a20800e189b3509952c84db91efa04df7bb73c43ae34a5598d88ac7a783-"
      "007",
      "f5abb3964382e0dde4bc3ec38414f43f325f5dcc6493d5a7c4037972793fb302");
  std::cout << "\nbalanceResult: " << balanceResult.balance_value;

  std::cout << std::endl;
}

void stateGetAuctionInfo() {
  // TODO: implement
  std::cout << "-----------------------------------------------\n";
  std::cout << "state_get_auction_info" << std::endl;

  /// Call GetStateRootHash function with the height of the block.
  Casper::GetAuctionInfoResult auction_result = casper_client.GetAuctionInfo(
      "9f246c64116b5c686c8e6a6829fce36c86bb32437866b617d91ed7de9f6a8a16");

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
    if (cur_validator_bid.public_key.empty()) {
      std::cout << "\nvalidator_public_key: "
                << cur_validator_bid.bid.validator_public_key
                << "\nbonding_purse: "
                << cur_validator_bid.bid.bonding_purse.ToString()
                << "\nstaked_amount: "
                << cur_validator_bid.bid.staked_amount.toString()
                << "\ndelegation_rate: "
                << (uint8_t)cur_validator_bid.bid.delegation_rate;
      if (cur_validator_bid.bid.vesting_schedule.has_value()) {
        std::cout << "\nvesting_schedule initial_release_timestamp_millis: "
                  << cur_validator_bid.bid.vesting_schedule.value()
                         .initial_release_timestamp_millis
                  << " locked_amounts: "
                  << cur_validator_bid.bid.vesting_schedule.value()
                         .locked_amounts.toString();
      }
      std::cout << "\ninactive: " << std::boolalpha
                << cur_validator_bid.bid.inactive;

    } else {
      std::cout << "\npublic_key: " << cur_validator_bid.public_key;
    }
  }

  std::cout << std::endl;
}

int main() {
  // infoGetPeers();

  // chainGetStateRootHash();

  // Milestone 2
  // infoGetDeploy();

  // infoGetStatus();

  chainGetBlockTransfers();

  // chainGetBlock();

  // chainGetEraInfoBySwitchBlock();

  // stateGetItem();

  // stateGetDictionaryItem();

  // stateGetBalance();

  // stateGetAuctionInfo();

  // Milestone 3
  // PutDeploy(); TODO: implement
}