cmake_minimum_required(VERSION 3.10)
project(Course_Project_2026 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)

add_executable(untitled main.c)

target_link_libraries(untitled m)
