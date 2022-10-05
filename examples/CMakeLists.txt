# Link the CasperSDK library to the example project.

set(BINARY example)

include_directories(
    ${SDK_ROOT}/lib/cryptopp-pem
)

add_executable(${BINARY} HelloSDK.cpp)

target_link_libraries(${BINARY} 
    PRIVATE
    spdlog::spdlog
    ${LIB_NAME})
