cmake_minimum_required( VERSION 2.8 )

project(vrm_test)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set( EXE_NAME test_write )
add_executable( ${EXE_NAME} test_write.cpp )
set_property( TARGET ${EXE_NAME} PROPERTY CXX_STANDARD 11 )
if(MSVC)
    target_compile_options(${EXE_NAME} PRIVATE /W4 /WX)
    add_definitions( -D_CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(${EXE_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
install( TARGETS ${EXE_NAME} RUNTIME DESTINATION bin )

