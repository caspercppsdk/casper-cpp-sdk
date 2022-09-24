cmake_minimum_required(VERSION 3.10)

set(SRC_PATH .)
set(SOURCES
    ${SRC_PATH}/cryptopp/pem_test.cxx
    ${SRC_PATH}/cryptopp/pem_eol.cxx
    ${SRC_PATH}/cryptopp/badcert.cxx
    ${SRC_PATH}/cryptopp/x509cert.cpp
    ${SRC_PATH}/cryptopp/pem_write.cpp
    ${SRC_PATH}/cryptopp/pem_read.cpp
    ${SRC_PATH}/cryptopp/pem_common.cpp)
add_library(cryptopp_pem STATIC ${SOURCES})
target_include_directories(cryptopp_pem PUBLIC ${SRC_PATH})
target_link_libraries(cryptopp_pem
    PUBLIC 
    cryptopp-static
)
