add_library(basic_interpreter_print STATIC
    print.cpp
)

target_include_directories(basic_interpreter_print INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(basic_interpreter_print PUBLIC
    basic_interpreter
)

set_target_properties(basic_interpreter_print PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
