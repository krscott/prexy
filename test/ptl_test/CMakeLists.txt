file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "test_*.c")

foreach(src IN LISTS TEST_SRCS)
    get_filename_component(name ${src} NAME_WE)   # filename without extension
    set(codegen_name ${name}_codegen)

    set(src_path ${CMAKE_CURRENT_SOURCE_DIR}/${src})
    set(src_h_path ${CMAKE_CURRENT_SOURCE_DIR}/${name}.h)
    set(prexy_h_path ${CMAKE_CURRENT_SOURCE_DIR}/${name}_prexy.h)
    set(codegen_path ${CMAKE_CURRENT_SOURCE_DIR}/codegen_${name}.c)

    # Dummy target so command is always run
    add_custom_target(dummy_taget_${name} ALL DEPENDS ${prexy_h_path})

    add_custom_command(
        OUTPUT ${prexy_h_path}
        COMMAND $ENV{PREXY} "${src_h_path}" -o "${prexy_h_path}"
        DEPENDS ${src_path} always_rebuild
        VERBATIM
    )

    # Dummy no-op command
    add_custom_command(
        OUTPUT always_rebuild
        COMMAND cmake -E echo
    )

    # Normal test

    add_executable(${name} ${src} ${prexy_h_path})
    include_directories(${CMAKE_SOURCE_DIR}/include)
    include_directories(${CMAKE_SOURCE_DIR}/ptl/include)
    add_test(NAME ${name} COMMAND ${CMAKE_SOURCE_DIR}/test/test_runner.sh ${name} ${CMAKE_CURRENT_SOURCE_DIR})

    # Expanded codegen test

    add_custom_command(
        OUTPUT ${codegen_path}
        COMMAND $ENV{PREXY} -E
            -I${CMAKE_SOURCE_DIR}/include
            -I${CMAKE_SOURCE_DIR}/ptl/include
            -I${CMAKE_CURRENT_SOURCE_DIR}
            ${src_path}
            -o ${codegen_path}
        DEPENDS ${src_path} ${src_h_path} ${prexy_h_path}
        VERBATIM
    )

    add_executable(${codegen_name} ${codegen_path} ${prexy_h_path})
    include_directories(${CMAKE_SOURCE_DIR}/include)
    include_directories(${CMAKE_SOURCE_DIR}/ptl/include)
    add_test(NAME ${codegen_name} COMMAND ${CMAKE_SOURCE_DIR}/test/test_runner.sh ${codegen_name} ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()
