set(BINARY casper_sdk_test)

add_executable(${BINARY}
    ClientTest.cpp
    RpcTest.cpp
    CLValueByteSerializerTest.cpp
    DeployItemByteSerializerTest.cpp
)

target_link_libraries(${BINARY} PUBLIC ${LIB_NAME})

add_test(NAME ${BINARY} COMMAND ./${BINARY})
