
function(add_warning_flag_to_target target)
    if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
        target_compile_options(${target} PRIVATE /W4 /MP)
        if(ENABLE_WERROR)
            target_compile_options(${target} PRIVATE /WX)
        endif()
    elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR(CMAKE_CXX_COMPILER_ID STREQUAL "QCC") OR(CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"))
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wnon-virtual-dtor -Wformat=2
            -Wformat-security -Werror=format-security -Wcast-align -Wcast-qual -Wconversion
            -Wdouble-promotion -Wfloat-equal -Wold-style-cast
            -Wredundant-decls -Wshadow -Wsign-conversion -Wswitch -Wuninitialized
            -Wunused-parameter -Walloca -Wunused-result -Wunused-local-typedefs
            -Wwrite-strings -Wpointer-arith -Wfloat-conversion -Wnull-dereference -Wdiv-by-zero
            -Wswitch-default -Wno-switch-bool -Wunknown-pragmas 
        )

        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            if((NOT(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "11")) AND(NOT CMAKE_CROSSCOMPILING))
                target_compile_options(${target} PRIVATE -Wformat-signedness -Walloc-zero -Wduplicated-branches -Wduplicated-cond -Wimplicit-fallthrough=5 -Wlogical-op
                    -Wenum-conversion -Wno-switch-unreachable -Wliteral-suffix -Wno-builtin-macro-redefined -Wno-unknown-warning-option -Wdeprecated-copy
                )
            endif()
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
            target_compile_options(${target} PRIVATE -Wenum-conversion)
        endif()

        if(ENABLE_WERROR)
            target_compile_options(${target} PRIVATE -Werror)
        endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Tasking")
        if(ENABLE_WERROR)
            target_compile_options(${target} --warnings-as-errors)
        endif()
    endif()
endfunction()