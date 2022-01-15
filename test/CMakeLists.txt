set(BINARY ${CMAKE_PROJECT_NAME}_test)

add_executable(${BINARY} ClientTest.cpp)

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME})

add_test(NAME ${BINARY} COMMAND ./${BINARY})
