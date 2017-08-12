add_library(basic_parser STATIC
    token.cpp
    lexer.cpp
    basic_lexer.cpp
    basic_parser.cpp
    basic_interpreter.cpp
)

target_include_directories(basic_parser INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

set_target_properties(basic_parser PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

