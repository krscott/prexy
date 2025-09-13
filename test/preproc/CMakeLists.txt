file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.c")

foreach(src IN LISTS TEST_SRCS)
    get_filename_component(name ${src} NAME_WE)   # filename without extension
    add_executable(${name} ${src})

    # target_link_libraries(${name} PRIVATE mylib)

    # Header only tests
    include_directories(../../prexylib/include)

    add_test(NAME ${name} COMMAND ${name})
endforeach()
