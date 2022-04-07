# Casper C++ SDK
Casper C++ SDK provides an interface to establish a connection between the Casper Blockchain and a client. Currently, the SDK is compatible with Linux systems.

## Dependencies
1. [CMake Version 3.0.0 or newer](https://cmake.org)
2. [Doxygen Version 1.8.8 or newer](https://www.doxygen.nl)

## How to clone the SDK
    git clone https://github.com/yusufketen/casper-cpp-sdk.git

## Build

### Debug
    cmake -DCMAKE_BUILD_TYPE=Debug .
    make all

### Release
    cmake -DCMAKE_BUILD_TYPE=Release .
    make all

## Test
    cmake -DCMAKE_BUILD_TYPE=Debug .
    make all
    ./test/CasperSDK_test

## Run Examples
    cmake -DCMAKE_BUILD_TYPE=Debug .
    make all
    ./examples/example

## Install
    cmake -DCMAKE_BUILD_TYPE=Release .
    make all
    sudo make install

---
## How to integrate Casper C++ SDK into your project
    1. Include the header file to the application file.
        #include "CasperClient.h"
    2. Link the installed SDK to the application. A CMake example is given below.
        add_executable(ApplicationName main.cpp)
        target_link_libraries(ApplicationName PUBLIC CasperSDK)

## How to use the Casper C++ SDK
    Usage of the RPC functions are described in the examples/HelloSDK.cpp file.

    1. Define a CasperClient object and connect to the Casper Blockchain. Replace the IP address and port number to the IP address and port number of any Casper Blockchain node.
        Casper::Client client("http://127.0.0.1:7777");

    2. Call the client object member functions listed with their return types below to perform RPC functions.
| **Client Function**     	| **Return Type**                 	|
|-------------------------	|---------------------------------	|
| GetNodePeers            	| Casper::InfoGetPeersResult      	|
| GetStateRootHash        	| Casper::GetStateRootHashResult  	|
| GetDeployInfo           	| Casper::GetDeployInfoResult     	|
| GetStatusInfo           	| Casper::GetStatusResult         	|
| GetBlockTransfers       	| Casper::GetBlockTransfersResult 	|
| GetBlock                	| Casper::GetBlockResult          	|
| GetEraInfoBySwitchBlock 	| Casper::GetEraInfoResult        	|
| GetItem                 	| Casper::GetItemResult           	|
| GetDictionaryItem       	| Casper::GetDictionaryItemResult 	|
| GetAccountBalance       	| Casper::GetBalanceResult        	|
| GetAuctionInfo          	| Casper::GetAuctionInfoResult    	|

## How to install doxygen for documentation
On Ubuntu and Debian:
    sudo apt-get install doxygen

On CentOS and Rocky Linux:
    sudo dnf config-manager --set-enabled powertools
    sudo dnf install doxygen

## Documentation
    cd docs
    doxygen Doxyfile
    
    The documentation will be available in the "docs/html/index.html" file.

## External Libraries
1. https://github.com/nlohmann/json
2. https://github.com/jsonrpcx/json-rpc-cxx
3. https://github.com/yhirose/cpp-httplib
4. https://github.com/weidai11/cryptopp
5. https://github.com/Neargye/magic_enum

## TODO
1. C++ version of CLType primitives(Milestone 3)
2. C++ version for Casper Domain Specific Objects(Milestone 3)
3. Serialization of Casper Domain Specific Objects(Milestone 3)
4. ED25519/SECP256K1 key pairs  Wrappers(Milestone 3)
5. PutDeploy RPC call implemented(Milestone 3)
