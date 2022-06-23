# Link the CasperSDK library to the example project.

set(BINARY example)

if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT> #---------|
        $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
        $<$<CONFIG:Release>:/MT> #--|
    )
endif()

add_executable(${BINARY} HelloSDK.cpp)

target_link_libraries(${BINARY} ${CMAKE_PROJECT_NAME})
