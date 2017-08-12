add_executable(basic
    main.cpp
)

target_link_libraries(basic PRIVATE
    basic_parser_print
)

set_target_properties(basic PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

