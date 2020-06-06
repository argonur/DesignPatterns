cmake_minimum_required (VERSION 3.14)

add_compile_options(
	-Wall
    -Wextra
    -Werror
    -Wpedantic
    -pedantic-errors
    -Wsign-conversion
    -Wshadow
    -Wcast-qual
    -Wcast-align
    -Wmissing-declarations
    -Wwrite-strings
    -fmessage-length=0
    -fexceptions
    -Weffc++
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILE_FEATURES
    cxx_constexpr
    cxx_final
    cxx_override
    cxx_nullptr
    cxx_alignas
    cxx_auto_type
    cxx_range_for
    cxx_attributes
    cxx_strong_enums
    cxx_user_literals
    cxx_inline_namespaces
    cxx_deleted_functions
    cxx_defaulted_functions
    cxx_delegating_constructors
    cxx_generalized_initializers
    )

add_subdirectory(apps/chapter1)