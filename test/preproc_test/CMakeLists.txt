# Dummy no-op command
add_custom_command(
    OUTPUT always_rebuild
    COMMAND cmake -E echo
)

# Special files

set(trait_template ${CMAKE_CURRENT_SOURCE_DIR}/07_trait.h)
set(trait_codegen ${CMAKE_CURRENT_SOURCE_DIR}/08_codegen.h)
add_custom_target(dummy_target_08 ALL DEPENDS ${trait_codegen})
add_custom_command(
    OUTPUT ${trait_codegen}
    COMMAND $ENV{PREXY} -E
        -I${CMAKE_SOURCE_DIR}/include
        -I${CMAKE_SOURCE_DIR}/prexylib/include
        -I${CMAKE_CURRENT_SOURCE_DIR}
        ${trait_template}
        -o ${trait_codegen}
    DEPENDS ${c_path} always_rebuild
    COMMENT "Expanding 08_codegen.h from 07_trait.h"
    VERBATIM
)

# Common files

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.c")

set(USE_HEADERS
    "07_trait"
)

foreach(src IN LISTS TEST_SRCS)
    get_filename_component(name ${src} NAME_WE)   # filename without extension

    if(name IN_LIST USE_HEADERS)
        set(c_path ${CMAKE_CURRENT_SOURCE_DIR}/${name}.h)
    else()
        set(c_path ${CMAKE_CURRENT_SOURCE_DIR}/${src})
    endif()

    set(h_path ${CMAKE_CURRENT_SOURCE_DIR}/${name}_prexy.h)

    # Dummy target so command is always run
    add_custom_target(dummy_target_${name} ALL DEPENDS ${h_path})

    add_custom_command(
        OUTPUT ${h_path}
        COMMAND $ENV{PREXY} "${c_path}" -o "${h_path}"
        DEPENDS ${c_path} always_rebuild
        VERBATIM
    )

    add_executable(${name} ${src} ${h_path})

    # target_link_libraries(${name} PRIVATE mylib)

    # Header only tests
    include_directories(${CMAKE_SOURCE_DIR}/include)
    include_directories(${CMAKE_SOURCE_DIR}/prexylib/include)

    add_test(NAME ${name} COMMAND ${CMAKE_SOURCE_DIR}/test/test_runner.sh ${name} ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()
