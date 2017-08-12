add_library(basic_parser_print STATIC
    print.cpp
)

target_include_directories(basic_parser_print INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(basic_parser_print PUBLIC
    basic_parser
)

set_target_properties(basic_parser_print PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
