file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.c")

foreach(src IN LISTS TEST_SRCS)
    get_filename_component(name ${src} NAME_WE)   # filename without extension

    set(src_h_path ${CMAKE_CURRENT_SOURCE_DIR}/${name}.h)
    set(out_h_path ${CMAKE_CURRENT_SOURCE_DIR}/${name}_prexy.h)

    # Dummy target so command is always run
    add_custom_target(dummy_taget_${name} ALL DEPENDS ${out_h_path})

    add_custom_command(
        OUTPUT ${out_h_path}
        COMMAND $ENV{PREXY} "${src_h_path}" -o "${out_h_path}"
        DEPENDS ${src_h_path} always_rebuild
        VERBATIM
    )

    # Dummy no-op command
    add_custom_command(
        OUTPUT always_rebuild
        COMMAND cmake -E echo
    )

    add_executable(${name} ${src} ${out_h_path})

    # target_link_libraries(${name} PRIVATE mylib)

    # Header only tests
    include_directories(${CMAKE_SOURCE_DIR}/include)
    include_directories(${CMAKE_SOURCE_DIR}/ptl/include)

    add_test(NAME ${name} COMMAND ${CMAKE_SOURCE_DIR}/test/test_runner.sh ${name} ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()
