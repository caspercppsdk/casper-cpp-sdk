set(LIB_NAME "CasperSDK")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/JsonRpc
    ${CMAKE_CURRENT_SOURCE_DIR}/include/JsonRpc/Connection
    ${CMAKE_CURRENT_SOURCE_DIR}/include/JsonRpc/ResultTypes
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Types
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/cryptopp
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/
)

file(GLOB all_SRCS
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.cpp"

        "${CMAKE_CURRENT_SOURCE_DIR}/include/ByteSerializers/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/ByteSerializers/*.cpp"

        "${CMAKE_CURRENT_SOURCE_DIR}/include/JsonRpc/Connection/*.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/include/JsonRpc/ResultTypes/*.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/include/Types/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/Types/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/Types/*.cpp"

        "${CMAKE_CURRENT_SOURCE_DIR}/include/Utils/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/Utils/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/Utils/*.cpp"
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -m64 -Wa,-mbig-obj")


add_library(${LIB_NAME} SHARED CasperClient.cpp ${all_SRCS})

find_package(OpenSSL REQUIRED)

target_link_libraries(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib/cryptopp/libcryptopp.a OpenSSL::SSL)
if(WIN32)
  target_link_libraries(${LIB_NAME} PUBLIC wsock32 ws2_32)
endif()