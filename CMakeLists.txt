cmake_minimum_required(VERSION 3.20)

# Set the project name to your project name, my project isn't very descriptive
project(SerfProject CXX)
set(LIB_NAME gitpac)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)

set(EXE_NAME serf)
set(EXE_DIR ${CMAKE_SOURCE_DIR}/src)

set(ARGPARSE_NAME argparse)
set(ARGPARSE_DIR ${CMAKE_SOURCE_DIR}/argparse)

include(cmake/CompileCommands.cmake)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(
        ENABLE_BUILD_WITH_TIME_TRACE
        "Enable -ftime-trace to generate time tracing .json files on clang" OFF
        )
    if (ENABLE_BUILD_WITH_TIME_TRACE)
        target_compile_options(project_options INTERFACE -ftime-trace)
    endif ()
endif ()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# enable cache system
include(cmake/Cache.cmake)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/SetBuildTypeProperties.cmake)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" ON)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
    # This sets a global PCH parameter, each project will build its own PCH, which is a good idea if
    # any #define's change
    #
    # consider breaking this out per project as necessary
    target_precompile_headers(
        project_options
        INTERFACE
        <vector>
        <string>
        <map>
        <utility>
        )
endif ()

# These Libs are needed by the project
set(CONAN_EXTRA_REQUIRES "libgit2/1.1.0" "nlohmann_json/3.9.1")

set(CONAN_EXTRA_OPTIONS "")

include(cmake/Conan.cmake)
run_conan()

add_subdirectory(argparse)
add_subdirectory(lib)
add_subdirectory(src)

if (ENABLE_TESTING)
    enable_testing()
    message(STATUS "Building Tests.")
    add_subdirectory(test)
endif ()
