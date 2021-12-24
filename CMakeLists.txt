cmake_minimum_required(VERSION 2.8)
project(CasperSDK)

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

