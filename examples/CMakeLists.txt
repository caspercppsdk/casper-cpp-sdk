# Check the CasperSDK installation.
find_library(CASPERSDK CasperSDK)
message(STATUS ${CASPERSDK})

# Link the CasperSDK library to the example project.
add_executable(HelloSDK HelloSDK.cpp)
target_link_libraries(HelloSDK PUBLIC CasperSDK)