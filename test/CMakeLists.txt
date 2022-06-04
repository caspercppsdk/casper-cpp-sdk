set(BINARY ${CMAKE_PROJECT_NAME}_test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -m64 -Wa,-mbig-obj")

add_executable(${BINARY} ClientTest.cpp RpcTest.cpp CLValueByteSerializerTest.cpp DeployItemByteSerializerTest.cpp)

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME})

add_test(NAME ${BINARY} COMMAND ./${BINARY})
