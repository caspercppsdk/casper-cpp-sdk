cmake_minimum_required(VERSION 3.0)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/JsonRpc
    ${CMAKE_CURRENT_SOURCE_DIR}/include/JsonRpc/Connection
    ${CMAKE_CURRENT_SOURCE_DIR}/include/JsonRpc/ResultTypes
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Types
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Algorithm
    ${SDK_ROOT}/lib/cryptopp-pem
    ${SDK_ROOT}/lib/
)

add_library(${LIB_NAME} STATIC
    CasperClient.cpp
    include/Types/CLValue.cpp
    include/Types/CLType.cpp
    include/Types/CLTypeParsed.cpp
    include/Types/GlobalStateKey.cpp
    include/Types/URef.cpp
    include/Types/ED25519Key.cpp
    include/Types/Secp256k1Key.cpp
    include/Utils/CryptoUtil.cpp
    include/Utils/StringUtil.cpp
    include/Utils/CEP57Checksum.cpp
    include/Utils/LogConfigurator.cpp
    include/Types/CLConverter.cpp
    include/Types/Deploy.cpp
    include/ByteSerializers/BaseByteSerializer.cpp
)

# openssl comes from vcpkg or system
# cryptopp-static comes from vcpkg or system
# cryptopp_pem comes from local source tree
# linking PUBLIC as we want headers from all those libs be accessible to all clients
target_link_libraries(${LIB_NAME}
    PUBLIC
    OpenSSL::SSL
    ${CRYPTOPP_LIBRARIES}
    cryptopp_pem
    spdlog::spdlog_header_only
)
