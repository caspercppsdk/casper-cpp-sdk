cmake_minimum_required(VERSION 3.0)
project(CasperSDK VERSION 1.0.0)

message("CasperSDK Version: ${CMAKE_PROJECT_VERSION}")

# Set C++17 as the default C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set the include paths for the SDK and the SDK's dependencies
include_directories(src/include)
include_directories(lib)

# Set the CMake lists for the SDK and the SDK's dependencies
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)
add_subdirectory(examples)
