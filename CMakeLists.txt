cmake_minimum_required(VERSION 3.0)
project(CasperSDK VERSION 1.0.0)

message("CasperSDK Version: ${CMAKE_PROJECT_VERSION}")

# Set C++17 as the default C++ standard
set(CMAKE_CXX_STANDARD 20)
set(LIB_NAME "casper_sdk")
set(SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
    set(CMAKE_CXX_FLAGS "/EHsc /bigobj")
    set(CMAKE_EXE_LINKER_FLAGS "/MTd")
else()
    set(CMAKE_CXX_FLAGS "-Werror -Wno-missing-declarations -O3 -fPIC")
endif()

# TODO the rest of deps should be moved outside of the project too (if possible)
MESSAGE("using deps from vcpkg or system")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Boost 1.75.0 REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(CryptoPP REQUIRED)
find_package(spdlog REQUIRED)

# Set the include paths.
include_directories(
    src/include
    lib
    test/TestLibrary
    ${Boost_INCLUDE_DIR}
)

if(NOT EXTERNAL_INCLUDES_DIR)
    set(EXTERNAL_INCLUDES_DIR ${SDK_ROOT}/include)
    file(MAKE_DIRECTORY ${EXTERNAL_INCLUDES_DIR})
endif()

add_subdirectory(lib/cryptopp-pem)
add_subdirectory(src)

# TODO under linux gcc compiler crashes if we build both examples and tests; so build either this or that (memory exhaustion?)
# builds fine under windows
IF(CASPER_SDK_TESTS)
    MESSAGE("building tests")
    enable_testing()
    add_subdirectory(test)
endif()
IF(CASPER_SDK_EXAMPLES)
    MESSAGE("building examples")
    add_subdirectory(examples)
endif()

if(NOT LIBRARIES_DIR)
    set(LIBRARIES_DIR ${SDK_ROOT}/libs)
    file(MAKE_DIRECTORY ${LIBRARIES_DIR})
endif()

file(COPY "${SDK_ROOT}/src/include/" DESTINATION "${EXTERNAL_INCLUDES_DIR}/casper_sdk")
file(COPY "${SDK_ROOT}/lib/" DESTINATION "${EXTERNAL_INCLUDES_DIR}")
install(TARGETS ${LIB_NAME} DESTINATION ${LIBRARIES_DIR})
install(DIRECTORY "${SDK_ROOT}/src/include/" DESTINATION ${EXTERNAL_INCLUDES_DIR})
