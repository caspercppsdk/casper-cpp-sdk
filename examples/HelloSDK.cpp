#include <CasperClient.h>  // To use Casper::Client features
#include <iostream>

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

  std::cout << "\n\nResponse of API Version: " << hash_result.api_version
            << "\n";
}