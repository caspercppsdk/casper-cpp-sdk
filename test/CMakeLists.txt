cmake_minimum_required(VERSION 3.15)

set(BINARY casper_cpp_sdk_tests)

include_directories(
    ${SDK_ROOT}/lib/cryptopp-pem
)

add_executable(${BINARY}
    ClientTest.cpp
    RpcTest.cpp
    CLValueByteSerializerTest.cpp
    DeployItemByteSerializerTest.cpp
        ServerEventsTest.cpp ServerEventsTest.h)

target_link_libraries(${BINARY} 
    PRIVATE
    spdlog::spdlog
    ${LIB_NAME}
    ${CRYPTOPP_LIBRARIES})

add_test(NAME ${BINARY} COMMAND ./${BINARY})
