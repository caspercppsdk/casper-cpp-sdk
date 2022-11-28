cmake_minimum_required(VERSION 3.10)

set(SRC_PATH .)
set(SOURCES
    ${SRC_PATH}/cryptopp/x509cert.cpp
    ${SRC_PATH}/cryptopp/pem_write.cpp
    ${SRC_PATH}/cryptopp/pem_read.cpp
    ${SRC_PATH}/cryptopp/pem_common.cpp)
add_library(cryptopp_pem STATIC ${SOURCES})
target_include_directories(cryptopp_pem PUBLIC ${SRC_PATH})
target_link_libraries(cryptopp_pem
    PUBLIC
    ${CRYPTOPP_LIBRARIES}
)

add_executable(pem_tests_app ${SRC_PATH}/cryptopp/pem_test.cxx)
target_link_libraries(pem_tests_app
    PUBLIC
    cryptopp_pem
)

add_executable(pem_eol_app ${SRC_PATH}/cryptopp/pem_eol.cxx)
target_link_libraries(pem_eol_app
    PUBLIC
    cryptopp_pem
)

add_executable(badcert_app ${SRC_PATH}/cryptopp/badcert.cxx)
target_link_libraries(badcert_app
    PUBLIC
    cryptopp_pem
)
