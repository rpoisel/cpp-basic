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
    basic_interpreter_print
    Catch
)

ParseAndAddCatchTests(lexerTestApp)

add_executable(interpreterTestApp
    test_interpreter.cpp
)

target_link_libraries(interpreterTestApp PRIVATE
    basic_interpreter_print
    posix_facilities
    Catch
)

ParseAndAddCatchTests(interpreterTestApp)

add_executable(sourceTestApp
    test_source.cpp
)

target_link_libraries(sourceTestApp PRIVATE
    basic_interpreter
    Catch
)

ParseAndAddCatchTests(sourceTestApp)
