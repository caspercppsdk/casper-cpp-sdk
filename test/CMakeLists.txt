set(BINARY ${CMAKE_PROJECT_NAME}_test)

add_executable(${BINARY} ClientTest.cpp)


find_library(LIBCRYPTOPP cryptopp)
message(STATUS "CRYPTO LIBRARY ===>" ${LIBCRYPTOPP})

target_link_libraries(${BINARY} PUBLIC ${LIBCRYPTOPP} ${CMAKE_PROJECT_NAME} )

add_test(NAME ${BINARY} COMMAND ./${BINARY})
