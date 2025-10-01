file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.c")

foreach(src IN LISTS TEST_SRCS)
    get_filename_component(name ${src} NAME_WE)   # filename without extension

    set(template_path ${CMAKE_CURRENT_SOURCE_DIR}/${name}_template.h)
    set(prexy_h_path ${CMAKE_CURRENT_SOURCE_DIR}/${name}_prexy.h)
    set(codegen_path ${CMAKE_CURRENT_SOURCE_DIR}/${name}.h)

    # Dummy target so command is always run
    add_custom_target(dummy_taget_${name} ALL DEPENDS ${prexy_h_path})

    add_custom_command(
        OUTPUT ${prexy_h_path}
        COMMAND $ENV{PREXY} "${template_path}" -o "${prexy_h_path}"
        DEPENDS ${template_path} always_rebuild
        VERBATIM
    )

    # Dummy no-op command
    add_custom_command(
        OUTPUT always_rebuild
        COMMAND cmake -E echo
    )

    add_custom_command(
        OUTPUT ${codegen_path}
        COMMAND $ENV{PREXY} -E
            -I${CMAKE_SOURCE_DIR}/include
            -I${CMAKE_SOURCE_DIR}/ptl/include
            -I${CMAKE_CURRENT_SOURCE_DIR}
            ${template_path}
            -o ${codegen_path}
        DEPENDS ${template_path} ${prexy_h_path}
        VERBATIM
    )

    add_executable(${name} ${src} ${prexy_h_path} ${codegen_path})

    include_directories(${CMAKE_SOURCE_DIR}/include)
    include_directories(${CMAKE_SOURCE_DIR}/ptl/include)

    add_test(NAME ${name} COMMAND ${CMAKE_SOURCE_DIR}/test/test_runner.sh ${name} ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()
