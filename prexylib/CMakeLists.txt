cmake_minimum_required(VERSION 3.16)

add_library(prexylib)

target_include_directories(prexylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# target_sources(prexylib PRIVATE
#     prexy_cli.c
# )

