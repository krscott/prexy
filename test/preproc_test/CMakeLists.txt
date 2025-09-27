file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.c")

foreach(src IN LISTS TEST_SRCS)
    get_filename_component(name ${src} NAME_WE)   # filename without extension

    set(c_path ${CMAKE_CURRENT_SOURCE_DIR}/${src})
    set(h_path ${CMAKE_CURRENT_SOURCE_DIR}/${name}_prexy.h)

    # Dummy target so command is always run
    add_custom_target(dummy_taget_${name} ALL DEPENDS ${h_path})

    add_custom_command(
        OUTPUT ${h_path}
        COMMAND $ENV{PREXYP} "${c_path}" -o "${h_path}"
        DEPENDS ${c_path} always_rebuild
        VERBATIM
    )

    # Dummy no-op command
    add_custom_command(
        OUTPUT always_rebuild
        COMMAND cmake -E echo
    )

    add_executable(${name} ${src} ${h_path})

    # target_link_libraries(${name} PRIVATE mylib)

    # Header only tests
    include_directories(${CMAKE_SOURCE_DIR}/include)
    include_directories(${CMAKE_SOURCE_DIR}/prexylib/include)

    add_test(NAME ${name} COMMAND ${CMAKE_SOURCE_DIR}/test/test_runner.sh ${name} ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()
