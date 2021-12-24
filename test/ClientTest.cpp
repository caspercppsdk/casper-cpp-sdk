#include "CasperClient.h"
#include "gtest/gtest.h"

/**
 * @brief Construct a new TEST object for "info_get_peers" rpc call. Compare the
 * count of peers with 0.
 *
 */
TEST(ClientTest, GetPeers) {
  Casper::Client client(CASPER_TEST_ADDRESS);
  ASSERT_NE(client.GetNodePeers().peers.size(), 0);
}

/**
 * @brief Construct a new TEST object for "get_state_root_hash" rpc call with a
 * uint64_t typed block height. Compare the state root hash with an empty
 * string.
 *
 */
TEST(ClientTest, GetStateRootHashWithHeight) {
  Casper::Client client(CASPER_TEST_ADDRESS);
  ASSERT_NE(client.GetStateRootHash(10).state_root_hash, "");
}

/**
 * @brief Construct a new TEST object for "get_state_root_hash" rpc call with
 * empty valued block hash string. Compare the state root hash with an empty
 * string.
 *
 */
TEST(ClientTest, GetStateRootHashWithBlockHash) {
  Casper::Client client(CASPER_TEST_ADDRESS);
  ASSERT_NE(client.GetStateRootHash().state_root_hash, "");
}