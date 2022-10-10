# Casper C++ SDK
Casper C++ SDK provides an interface to establish a connection between the Casper Blockchain and a client.

## Dependencies
1. [CMake Version 3.0.0 or newer](https://cmake.org)
2. [Doxygen Version 1.8.8 or newer](https://www.doxygen.nl)
3. [OpenSSL Version 1.1.1 or newer](https://www.openssl.org)
4. [cryptopp Version 8.6.0 or newer](https://www.cryptopp.com/)

## How to clone the SDK

    git clone https://github.com/yusufketen/casper-cpp-sdk.git

## Install Instructions for Dependencies

    sudo apt-get install build-essential cmake libssl-dev
    sudo apt-get install graphviz
    sudo apt-get install doxygen
## Install Spdlog

```
git clone https://github.com/gabime/spdlog.git
cd spdlog && mkdir build && cd build
cmake -DCMAKE_CXX_FLAGS=-fPIC .. && make -j && sudo make install
```

**or via package manager:** <br/>

```
sudo dnf install spdlog-devel
```
**TODO** cryptopp for Fedora-based distros.

### Install instructions for doxygen for CentOS
On CentOS and Rocky Linux:

    sudo dnf config-manager --set-enabled powertools
    sudo dnf install doxygen

### Install instructions for vcpkg
Can be used for Windows, Linux and MacOS (fix your paths in the examples)  

#### Prepare vcpkg:
    git clone git@github.com:microsoft/vcpkg.git
    cd vcpkg
    git checkout 2022.08.15

#### Build deps:
    windows:
    vcpkg install @mydir\casper-cpp-sdk\vcpkg\vcpkg.txt --triplet=x64-windows --clean-after-build

    linux:
    ./vcpkg install @mydir/casper-cpp-sdk/vcpkg/vcpkg.txt --triplet=x64-linux --clean-after-build

    macos:
    ./vcpkg install @mydir/casper-cpp-sdk/vcpkg/vcpkg.txt --triplet=x64-osx --clean-after-build

#### Export deps:
    windows:  
    vcpkg export @mydir\casper-cpp-sdk\vcpkg\vcpkg.txt --raw --triplet=x64-windows  --output-dir=mydir\vcpkg-bin-win-casper-cpp-sdk --output=01  

    linux:  
    ./vcpkg export @mydir/casper-cpp-sdk/vcpkg/vcpkg.txt --raw --triplet=x64-linux --output-dir=mydir  
    vcpkg-bin-lin-casper-cpp-sdk --output=01

    macos:
    ./vcpkg export @mydir/casper-cpp-sdk/vcpkg/vcpkg.txt --raw --triplet=x64-osx --output-dir=mydir/vcpkg-bin-mac-casper-cpp-sdk --output=01

## Building

### Debug
Using deps from system (linux only)

    mkdir build && cd build
    cmake -GNinja -DCMAKE_BUILD_TYPE=Debug ..
    ninja

Using deps from vcpkg (linux, windows, macos)

    mkdir build && cd build
    
    windows:
    cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=mydir/vcpkg-bin-win-casper-cpp-sdk/01/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows ..
    
    linux:
    cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=mydir/vcpkg-bin-lin-casper-cpp-sdk/01/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-linux ..

    macos:
    cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=mydir/vcpkg-bin-mac-casper-cpp-sdk/01/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-osx ..

    cmake --build .

### Release
Using deps from system (linux only)

    mkdir build && cd build
    cmake -GNinja -DCMAKE_BUILD_TYPE=Release ..
    ninja

## Test
Using deps from system (linux only)

    mkdir build && cd build
    cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DCASPER_SDK_TESTS=ON ..
    ninja
    ./test/casper_cpp_sdk_tests

## Run Examples
    mkdir build && cd build
    cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DCASPER_SDK_TESTS=ON ..
    ninja
    ./examples/example

## Install
    mkdir build && cd build
    cmake -GNinja -DCMAKE_BUILD_TYPE=Release ..
    ninja
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
| PutDeploy               	| Casper::PutDeployResult        	|

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
6. https://github.com/codeinred/recursive-variant
7. https://github.com/ckormanyos/wide-integer
8. https://github.com/mity/acutest

## Projects Built on Casper C++ SDK
1. https://matterfi.com
