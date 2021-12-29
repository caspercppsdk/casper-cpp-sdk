set(LIB_NAME "CasperSDK")
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/JsonRpc
    ${CMAKE_CURRENT_SOURCE_DIR}/include/JsonRpc/Connection
    ${CMAKE_CURRENT_SOURCE_DIR}/include/JsonRpc/ResultTypes
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Types
)

add_library(${LIB_NAME} SHARED CasperClient.cpp)

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/JsonRpc
    ${CMAKE_CURRENT_SOURCE_DIR}/include/JsonRpc/Connection
    ${CMAKE_CURRENT_SOURCE_DIR}/include/JsonRpc/ResultTypes
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Types)

install(TARGETS ${LIB_NAME} DESTINATION /usr/lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
