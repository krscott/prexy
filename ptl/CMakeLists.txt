cmake_minimum_required(VERSION 3.16)

add_library(ptl)

target_include_directories(ptl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# target_sources(ptl PRIVATE
#     prexy_cli.c
# )

