#include "CasperClient.h"
#include "Types/GlobalStateKey.cpp"
#include "Utils/CryptoUtil.h"
#include "acutest.h"

/**
 * @brief Check the "info_get_peers" rpc function. Size of the resulting array
 * shouldn't be 0.
 *
 */
void get_peers_test(void) {
  Casper::Client client(CASPER_TEST_ADDRESS);
  TEST_ASSERT(client.GetNodePeers().peers.size() != 0);
}

/**
 * @brief Check the "get_state_root_hash" rpc function with a variable. Compare
 * the result with an empty string.
 *
 */
void get_state_root_hash_block_height_test(void) {
  Casper::Client client(CASPER_TEST_ADDRESS);
  uint64_t block_height = 10;
  TEST_ASSERT(client.GetStateRootHash(block_height).state_root_hash != "");
}

/**
 * @brief Check the "get_state_root_hash" rpc function without a variable.
 * Compare the result with an empty string.
 *
 */
void get_state_root_hash_test() {
  Casper::Client client(CASPER_TEST_ADDRESS);
  TEST_ASSERT(client.GetStateRootHash().state_root_hash != "");
}

/**
 * @brief Check the "info_get_status" rpc function. Check the result variables.
 *
 */
void get_status_info_test() {
  Casper::Client client(CASPER_TEST_ADDRESS);
  Casper::GetStatusResult result = client.GetStatusInfo();

  TEST_ASSERT(result.api_version != "");
  TEST_ASSERT(result.chainspec_name != "");
  TEST_ASSERT(result.starting_state_root_hash != "");
  TEST_ASSERT(result.peers.size() != 0);
  TEST_ASSERT(result.build_version != "");
  TEST_ASSERT(result.uptime != "");
}

/**
 * @brief Check the "info_get_status" rpc function. Check the result variables.
 *
 */
void get_block_transfers_test() {
  Casper::Client client(CASPER_TEST_ADDRESS);
  Casper::GetBlockTransfersResult result = client.GetBlockTransfers();

  TEST_ASSERT(result.api_version != "");
}

TEST_LIST = {{"peers", get_peers_test},
             {"root hash 1", get_state_root_hash_block_height_test},
             {"root hash 2", get_state_root_hash_test},
             {"get status info", get_status_info_test},
             {"get block transfers", get_block_transfers_test},
             {NULL, NULL}};
