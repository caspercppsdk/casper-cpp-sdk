set(BINARY ${CMAKE_PROJECT_NAME}_test)
if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT> #---------|
        $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
        $<$<CONFIG:Release>:/MT> #--|
    )
endif()

add_executable(${BINARY} ClientTest.cpp RpcTest.cpp CLValueByteSerializerTest.cpp DeployItemByteSerializerTest.cpp)

target_link_libraries(${BINARY} PRIVATE ${CMAKE_PROJECT_NAME})

add_test(NAME ${BINARY} COMMAND ./${BINARY})
