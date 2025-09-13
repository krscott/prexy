file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.c")

foreach(src IN LISTS TEST_SRCS)
    get_filename_component(name ${src} NAME_WE)   # filename without extension

    set(c_path ${CMAKE_CURRENT_SOURCE_DIR}/${src})
    set(h_path ${CMAKE_CURRENT_SOURCE_DIR}/${name}_prexy.h)

    add_custom_command(
        OUTPUT ${h_path}
        COMMAND $ENV{PREXYP} "${c_path}" -o "${h_path}"
        DEPENDS ${c_path}
        VERBATIM
    )

    add_executable(${name} ${src} ${h_path})

    # target_link_libraries(${name} PRIVATE mylib)

    # Header only tests
    include_directories(../../prexylib/include)

    add_test(NAME ${name} COMMAND ${CMAKE_SOURCE_DIR}/test/test_runner.sh ${name} preproc_test)
endforeach()
