cmake_minimum_required(VERSION 3.20)
project(TTesting)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(ENTRY "main" CACHE STRING "命令吧.")

add_executable(
    ${ENTRY}
    main.cpp
)
