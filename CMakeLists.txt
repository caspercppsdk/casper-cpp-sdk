cmake_minimum_required(VERSION 3.0)
project(CasperSDK VERSION 1.0.0)

message("CasperSDK Version: ${CMAKE_PROJECT_VERSION}")

# Set C++17 as the default C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Werror -Wno-missing-declarations -O3 -fPIC")
set(LIB_NAME "casper_sdk")
set(SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Set the include paths.
include_directories(
    src/include
    lib
    test/TestLibrary
    lib/cryptopp
)

find_program(
    MAKE_EXECUTABLE
    NAMES gmake mingw32-make make
    NAMES_PER_DIR
    DOC "GNU Make"
)

include(ExternalProject)
ExternalProject_Add(
    LIBCRYPTOPP
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/cryptopp
    UPDATE_DISCONNECTED true
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE TRUE
    INSTALL_COMMAND ""
    CMAKE_ARGS ""
)

execute_process(
    COMMAND bash -c "cd ${CMAKE_CURRENT_SOURCE_DIR}/lib/cryptopp && make -j8"
    OUTPUT_VARIABLE outVar
)

add_subdirectory(src)

if(CASPER_SDK_TESTS)
    enable_testing()
    add_subdirectory(test)
    add_subdirectory(examples)
endif()

if(NOT LIBRARIES_DIR)
    set(LIBRARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
    file(MAKE_DIRECTORY ${LIBRARIES_DIR})
endif()

if(NOT EXTERNAL_INCLUDES_DIR)
    set(EXTERNAL_INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
    file(MAKE_DIRECTORY ${EXTERNAL_INCLUDES_DIR})
endif()

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/src/include/" DESTINATION "${EXTERNAL_INCLUDES_DIR}/casper_sdk")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/lib/" DESTINATION "${EXTERNAL_INCLUDES_DIR}")
install(TARGETS ${LIB_NAME} DESTINATION ${LIBRARIES_DIR})
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/include/" DESTINATION ${EXTERNAL_INCLUDES_DIR})
