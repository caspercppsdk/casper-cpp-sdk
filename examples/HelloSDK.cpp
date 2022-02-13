#include "../src/include/CasperClient.h"  // To use Casper::Client features
#include <iostream>
#define CASPER_TEST_ADDRESS "http://185.246.84.43:7777"

int main() {
  /// Construct a Casper::Client object
  Casper::Client casper_client(CASPER_TEST_ADDRESS);

  /// Call GetNodePeers function from the client object.
  Casper::InfoGetPeersResult peers_result = casper_client.GetNodePeers();

  /// Print the nodes in the network.
  for (int i = 0; i < peers_result.peers.size(); i++) {
    /// Print the node ID.
    std::cout << i + 1 << ". Node ID: " << peers_result.peers[i].node_id;

    /// Print the node IP address.
    std::cout << " Address: " << peers_result.peers[i].address << std::endl;
  }

  /// Call GetStateRootHash function with the height of the block.
  Casper::GetStateRootHashResult height_result =
      casper_client.GetStateRootHash(10);
  std::cout << "\nstate_root_hash: " << height_result.state_root_hash;

  /// Call GetStateRootHash function with the block hash of the block.
  Casper::GetStateRootHashResult hash_result = casper_client.GetStateRootHash();
  std::cout << "\nstate_root_hash: " << hash_result.state_root_hash;
  std::cout << "\n\nResponse of API Version: " << hash_result.api_version;

  /// Call GetStatusInfo function.
  Casper::GetStatusInfoResult status_result = casper_client.GetStatusInfo();
  std::cout << "\napi_version: " << status_result.api_version;
  std::cout << "\nchainspec_name: " << status_result.chainspec_name;
  std::cout << "\nstarting_state_root_hash: " << status_result.starting_state_root_hash;
  for (std::size_t i = 0; i < status_result.peerList.size(); i++) {
    std::cout << std::to_string(i + 1) << "\nPeer: Address: " << status_result.peerList[i].address << " Node id:" << status_result.peerList[i].node_id;
  }
  std::cout << "\nBlock info: creator: " << status_result.last_added_block_info.creator << " era_id: " << status_result.last_added_block_info.era_id
    << " hash: " << status_result.last_added_block_info.hash << " height: " << status_result.last_added_block_info.height
    << " state_root_hash: " << status_result.last_added_block_info.state_root_hash << " timestamp: " << status_result.last_added_block_info.timestamp;
  std::cout << "\nour_public_signing_key: " << status_result.our_public_signing_key;
  std::cout << "\nround_length: " << status_result.round_length;
  std::cout << "\nnext_upgrade: " << status_result.next_upgrade;
  std::cout << "\nbuild_version: " << status_result.build_version;
  std::cout << "\nuptime: " << status_result.uptime;

  /// Call GetBlockTransfers function.
  Casper::GetBlockTransfersResult transfersResult = casper_client.GetBlockTransfers();
  std::cout << "\ntransfers: api_version: " << transfersResult.api_version << " block_hash: " << transfersResult.block_hash;
  for (std::size_t i = 0; i < transfersResult.transfers.size(); i++) {
    std::cout
      << std::to_string(i + 1)
      << "\nTransfer: deploy_hash: " << transfersResult.transfers[i].deploy_hash
      << " from:" << transfersResult.transfers[i].from
      << " to: " << transfersResult.transfers[i].to
      << " source: " << transfersResult.transfers[i].source
      << " target: " << transfersResult.transfers[i].target
      << " amount: " << transfersResult.transfers[i].amount
      << " gas: " << transfersResult.transfers[i].gas
      << " id: " << transfersResult.transfers[i].id;
  }

  /// Call GetBlockResult rpc function.
  Casper::GetBlockResult blockResult = casper_client.GetBlock(Casper::BlockIdentifier(status_result.last_added_block_info.hash, 1));
    std::cout << "\nblockresult\napi_version: " << blockResult.api_version;

    if (!blockResult.block.body.proposer.empty()) {
      std::cout << "\nproposer: " << blockResult.block.body.proposer
        << "\nhash: " << blockResult.block.hash
        << "\naccumulated_seed: " << blockResult.block.header.accumulated_seed
        << "\nbody_hash: " << blockResult.block.header.body_hash
        << "\nera_end: " << blockResult.block.header.era_end
        << "\nera_id: " << blockResult.block.header.era_id
        << "\nheight: " << blockResult.block.header.height
        << "\nparent_hash: " << blockResult.block.header.parent_hash
        << "\nprotocol_version: " << blockResult.block.header.protocol_version
        << "\nrandom_bit: " << blockResult.block.header.random_bit
        << "\nstate_root_hash: " << blockResult.block.header.state_root_hash
        << "\ntimestamp: " << blockResult.block.header.timestamp;

      for (std::size_t i = 0; i < blockResult.block.body.deploy_hashes.size(); i++) {
        std::cout << "\nDeploy hash: " << blockResult.block.body.deploy_hashes[i];
      }

      for (std::size_t i = 0; i < blockResult.block.body.transfer_hashes.size(); i++) {
        std::cout << "\nTransfer hash: " << blockResult.block.body.transfer_hashes[i];
      }

      for (std::size_t i = 0; i < blockResult.block.proofs.size(); i++) {
        std::cout << "\nProof: PK: " << blockResult.block.proofs[i].public_key << " Signature: " << blockResult.block.proofs[i].signature;
      }
    }

  /// Call chain_get_era_info_by_switch_block rpc function.
  Casper::GetEraInfoResult eraInfoResult = casper_client.GetEraInfoBySwitchBlock(Casper::BlockIdentifier(status_result.last_added_block_info.hash, 1));
  std::cout << "\neraInfoResult: " << eraInfoResult.api_version;
  std::cout << "\nblock_hash: " << eraInfoResult.era_summary.block_hash
    << "\nera_id: " << eraInfoResult.era_summary.era_id
    << "\nmarker_proof: " << eraInfoResult.era_summary.merkle_proof
    << "\nstate_root_hash: " << eraInfoResult.era_summary.state_root_hash
    << "\nstored_value: " << eraInfoResult.era_summary.stored_value;


  std::cout << "\n";
  std::cout << "\nExamples have successfully run.\n";
}
