add_library(posix_facilities STATIC
    posix_facilities.cpp
)

target_link_libraries(posix_facilities PUBLIC
    basic_interpreter
)

target_include_directories(posix_facilities INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

set_target_properties(posix_facilities PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

add_executable(basic
    main.cpp
)

target_link_libraries(basic PRIVATE
    posix_facilities
)

set_target_properties(basic PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
