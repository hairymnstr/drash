cmake_minimum_required(VERSION 3.0.0)

set(PROJ_NAME "drash_demo")

project(${PROJ_NAME} LANGUAGES C)

add_executable(${PROJ_NAME}
                main.c)

find_package(drash REQUIRED PATHS ../)

target_compile_definitions(${PROJ_NAME} PRIVATE
                            -DDRASH_CAN_EXIT)
