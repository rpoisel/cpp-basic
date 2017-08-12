list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/Catch/contrib")
include(ParseAndAddCatchTests)

add_library(Catch INTERFACE)

target_include_directories(Catch INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/Catch/single_include
)

add_executable(lexerTestApp
    test_lexer.cpp
)

target_link_libraries(lexerTestApp PRIVATE
    basic_parser_print
    Catch
)

ParseAndAddCatchTests(lexerTestApp)

add_executable(parserTestApp
    test_parser.cpp
)

target_link_libraries(parserTestApp PRIVATE
    basic_parser_print
    Catch
)

ParseAndAddCatchTests(parserTestApp)
