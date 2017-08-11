cmake_minimum_required(VERSION 3.5)
project(CPP-BASIC)

add_library(basic_parser STATIC
    token.cpp
    basic_lexer.cpp
    parser.cpp
)

add_library(basic_parser_print STATIC
    print.cpp
)

add_executable(basic
    main.cpp
)

target_link_libraries(basic PRIVATE
    basic_parser
    basic_parser_print
)

add_library(Catch INTERFACE)

target_include_directories(Catch INTERFACE
    Catch/single_include
)

add_executable(basicTestApp
    test.cpp
)

target_link_libraries(basicTestApp PRIVATE
    basic_parser
    basic_parser_print
    Catch
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Catch/contrib")
enable_testing(true)

include(ParseAndAddCatchTests)
ParseAndAddCatchTests(basicTestApp)
