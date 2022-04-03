# Casper C++ SDK
Casper C++ SDK provides an interface to establish a connection between the Casper Blockchain and a client. Currently, the SDK is compatible with Linux systems.

## Dependencies
1. [CMake Version 3.0.0 or newer](https://cmake.org)
2. [Doxygen Version 1.8.8 or newer](https://www.doxygen.nl)


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
    make test

## Run Example
    cmake -DCMAKE_BUILD_TYPE=Debug .
    make all
    ./examples/HelloSDK

## Install
    cmake -DCMAKE_BUILD_TYPE=Release .
    make all
    sudo make install

---
## How to use
    1. Include the header file to the application file.
        #include "CasperClient.h"
    2. Link the installed SDK to the application. A CMake example is given below.
        add_executable(ApplicationName main.cpp)
        target_link_libraries(ApplicationName PUBLIC CasperSDK)

## Documentation
    cd docs
    doxygen Doxyfile

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
