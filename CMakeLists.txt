#cmake file

cmake_minimum_required(VERSION 3.5)

project(tetris)

set(SRC_MAIN sources/main.cpp)
set(LIBRARY_TETRIS "tet")
file(GLOB SRC_TETRIS "sources/libtetris/*.cpp")

set(CMAKE_CXX_COMPILER clang++)
add_definitions(-Wall -std=c++14 -g)

include_directories(include)

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_library(${LIBRARY_TETRIS} SHARED ${SRC_TETRIS})

add_executable(${PROJECT_NAME} ${SRC_MAIN})

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES} ${LIBRARY_TETRIS} ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS ${LIBRARY_TETRIS} DESTINATION /usr/lib)
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)

# uninstall target
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
