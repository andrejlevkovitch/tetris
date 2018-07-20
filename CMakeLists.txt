#cmake file

cmake_minimum_required(VERSION 3.5)

project(tetris)

if(${UNIX})
    message(STATUS "UNIX system")
else()
    message(FATAL_ERROR "The system is not supported")
endif()

option(set_clang "set clang default compiler and linker" 0)
option(cros_compile "cros compile for win32" 0)

if(set_clang)
    set(CMAKE_CXX_COMPILER clang++)
endif()
if(cros_compile)
    set(PROJECT_NAME ${PROJECT_NAME}.exe)
    set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++-posix)
    set(CMAKE_CXX_FLAGS "-static-libstdc++ -static-libgcc")
endif()

add_definitions(-Wall -std=c++14)

message(STATUS "CXX_Compiler is " ${CMAKE_CXX_COMPILER})
message(STATUS "CXX_Compiler's flags are " ${CMAKE_CXX_FLAGS})

message(STATUS "Project name is " ${PROJECT_NAME})

set(SRC_MAIN sources/main.cpp)
set(LIBRARY_TETRIS "tet")
file(GLOB SRC_TETRIS "sources/libtetris/*.cpp")

include_directories(include)

find_package(Threads REQUIRED)
include_directories(${THREADS_INCLUDE_DIR})

if(cros_compile)
    find_package(PDCurses REQUIRED)
else()
    find_package(Curses REQUIRED)
endif(cros_compile)

include_directories(${CURSES_INCLUDE_DIR})

add_library(${LIBRARY_TETRIS} STATIC ${SRC_TETRIS})

add_executable(${PROJECT_NAME} ${SRC_MAIN})

target_link_libraries(${PROJECT_NAME} ${LIBRARY_TETRIS} ${CURSES_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS ${LIBRARY_TETRIS} DESTINATION /usr/lib)
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)

if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P
        ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif(NOT TARGET uninstall)
