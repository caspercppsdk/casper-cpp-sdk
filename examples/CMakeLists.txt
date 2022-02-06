# Link the CasperSDK library to the example project.

set(BINARY example)

add_executable(${BINARY} HelloSDK.cpp)

target_link_libraries(${BINARY} ${CMAKE_PROJECT_NAME})
