cmake_minimum_required(VERSION 3.15)

set(BINARY casper_cpp_sdk_tests)

find_package(GTest REQUIRED)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include_directories(
    ${SDK_ROOT}/lib/cryptopp-pem
)

add_executable(${BINARY}
    CLValueByteSerializerTest.cpp
    DeployItemByteSerializerTest.cpp
)

target_link_libraries(${BINARY} 
    PRIVATE
    GTest::gtest_main
    spdlog::spdlog
    ${LIB_NAME}
    ${CRYPTOPP_LIBRARIES})

enable_testing()


include(GoogleTest)
gtest_discover_tests(${BINARY})

