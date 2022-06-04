# Link the CasperSDK library to the example project.

set(BINARY example)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -m64 -Wa,-mbig-obj")

add_executable(${BINARY} HelloSDK.cpp)

target_link_libraries(${BINARY} ${CMAKE_PROJECT_NAME})
