add_library(basic_interpreter STATIC
    basic_variant.cpp
    basic_source.cpp
    basic_lexer.cpp
    basic_interpreter.cpp
    basic_commands.cpp
    lang_token.cpp
    lang_lexer.cpp
)

target_include_directories(basic_interpreter INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

set_target_properties(basic_interpreter PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

