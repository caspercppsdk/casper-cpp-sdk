#include <iostream>

#include "../src/include/CasperClient.h"  // To use Casper::Client features
#include "../src/include/Types/GlobalStateKey.h"

/// Construct a Casper::Client object
Casper::Client casper_client(CASPER_TEST_ADDRESS);

/// “info_get_peers” RPC.
void infoGetPeers() {
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "info_get_peers" << std::endl;
  /// Call GetNodePeers function from the client object.
  Casper::InfoGetPeersResult peers_result = casper_client.GetNodePeers();

  /// Print the nodes in the network.
  for (int i = 0; i < peers_result.peers.size(); i++) {
    /// Print the node ID.
    std::cout << i + 1 << ". Node ID: " << peers_result.peers[i].node_id;

    /// Print the node IP address.
    std::cout << " Address: " << peers_result.peers[i].address << "\n";
  }

  std::cout << std::endl;
}

/// “chain_get_state_root_hash” RPC.
void chainGetStateRootHash() {
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "chain_get_state_root_hash" << std::endl;

  /// Call GetStateRootHash function with the height of the block.
  Casper::GetStateRootHashResult height_result =
      casper_client.GetStateRootHash(10);
  std::cout << "state_root_hash for block height 10: "
            << height_result.state_root_hash << "\n";

  /// Call GetStateRootHash function with the block hash of the block.
  Casper::GetStateRootHashResult hash_result = casper_client.GetStateRootHash(
      "acc4646f35cc1d59b24381547a4d2dc1c992a202b6165f3bf68d3f23c2b93330");
  std::cout << "state_root_hash for given block hash: "
            << hash_result.state_root_hash << "\n";

  /// Call GetStateRootHash function with empty string.
  Casper::GetStateRootHashResult recent_hash_result =
      casper_client.GetStateRootHash();
  std::cout << "most recent state_root_hash: "
            << recent_hash_result.state_root_hash << "\n";

  std::cout << std::endl;
}

void infoGetDeploy() {
  // TODO: fill in this function
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "info_get_deploy" << std::endl;

  std::cout << std::endl;
}

void infoGetStatus() {
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "info_get_status" << std::endl;

  /// Call GetStatusInfo function.
  Casper::GetStatusInfoResult status_result = casper_client.GetStatusInfo();
  std::cout << "\napi_version: " << status_result.api_version;
  std::cout << "\nchainspec_name: " << status_result.chainspec_name;
  std::cout << "\nstarting_state_root_hash: "
            << status_result.starting_state_root_hash;
  for (std::size_t i = 0; i < status_result.peerList.size(); i++) {
    std::cout << std::to_string(i + 1)
              << "\nPeer: Address: " << status_result.peerList[i].address
              << " - Node id:" << status_result.peerList[i].node_id;
  }
  std::cout << "\nBlock info: creator: "
            << status_result.last_added_block_info.creator
            << "\nera_id: " << status_result.last_added_block_info.era_id
            << "\nhash: " << status_result.last_added_block_info.hash
            << "\nheight: " << status_result.last_added_block_info.height
            << "\nstate_root_hash: "
            << status_result.last_added_block_info.state_root_hash
            << "\ntimestamp: " << status_result.last_added_block_info.timestamp;
  std::cout << "\nour_public_signing_key: "
            << status_result.our_public_signing_key;
  std::cout << "\nround_length: " << status_result.round_length;
  std::cout << "\nnext_upgrade: " << status_result.next_upgrade;
  std::cout << "\nbuild_version: " << status_result.build_version;
  std::cout << "\nuptime: " << status_result.uptime;

  std::cout << std::endl;
}

void chainGetBlockTransfers() {
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "chain_get_block_transfers" << std::endl;

  /// Call GetBlockTransfers function.
  Casper::GetBlockTransfersResult transfersResult =
      casper_client.GetBlockTransfers(
          {"acc4646f35cc1d59b24381547a4d2dc1c992a202b6165f3bf68d3f23c2b93330",
           532041});
  std::cout << "\napi_version: " << transfersResult.api_version
            << "\nblock_hash: " << transfersResult.block_hash;
  for (std::size_t i = 0; i < transfersResult.transfers.size(); i++) {
    std::cout << std::to_string(i + 1) << "\nTransfer: deploy_hash: "
              << transfersResult.transfers[i].deploy_hash
              << "\nfrom:" << transfersResult.transfers[i].from
              << "\nto: " << transfersResult.transfers[i].to
              << "\nsource: " << transfersResult.transfers[i].source.ToString()
              << "\ntarget: " << transfersResult.transfers[i].target.ToString()
              << "\namount: " << transfersResult.transfers[i].amount
              << "\ngas: " << transfersResult.transfers[i].gas
              << "\nid: " << transfersResult.transfers[i].id;
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

    for (std::size_t i = 0; i < blockResult.block.body.deploy_hashes.size();
         i++) {
      std::cout << "\nDeploy hash: " << blockResult.block.body.deploy_hashes[i];
    }

    for (std::size_t i = 0; i < blockResult.block.body.transfer_hashes.size();
         i++) {
      std::cout << "\nTransfer hash: "
                << blockResult.block.body.transfer_hashes[i];
    }

    for (std::size_t i = 0; i < blockResult.block.proofs.size(); i++) {
      std::cout << "\nProof: PK: " << blockResult.block.proofs[i].public_key
                << "\nSignature: " << blockResult.block.proofs[i].signature
                << "\n";
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
  std::cout << "\nblock_hash: " << eraInfoResult.era_summary.block_hash
            << "\nera_id: " << eraInfoResult.era_summary.era_id
            << "\nmarker_proof: " << eraInfoResult.era_summary.merkle_proof
            << "\nstate_root_hash: "
            << eraInfoResult.era_summary.state_root_hash << "\nstored_value: "
            << eraInfoResult.era_summary.stored_value.value.type;

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

  std::cout << std::endl;
}

int main() {
  // infoGetPeers();

  // chainGetStateRootHash();

  // Milestone 2
  // infoGetDeploy();

  infoGetStatus();

  // chainGetBlockTransfers();

  chainGetBlock();

  chainGetEraInfoBySwitchBlock();

  // stateGetItem();

  // stateGetDictionaryItem();

  // stateGetBalance();

  // stateGetAuctionInfo();

  // Milestone 3
  // PutDeploy(); TODO: implement
}