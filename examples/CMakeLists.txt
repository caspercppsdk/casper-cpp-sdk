cmake_minimum_required(VERSION 2.8.0)
project (HelloSDK)

set(CMAKE_CXX_STANDARD 17)

# Check the CasperSDK installation.
find_library(CASPERSDK_LIB CasperSDK_lib)
message(STATUS ${CASPERSDK_LIB})

# Link the CasperSDK library to the example project.
add_executable(HelloSDK HelloSDK.cpp)
target_link_libraries(HelloSDK PUBLIC CasperSDK_lib)