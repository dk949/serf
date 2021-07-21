link_compile_commands()
# Automatically enable catch2 to generate ctest targets
if (CONAN_CATCH2_ROOT_DEBUG)
    include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else ()
    include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif ()

# setup files to be dested
set(TEST_EXTRA_LIBS CONAN_PKG::spdlog)
message(STATUS "ARGPARSE_LIB = ${ARGPARSE_NAME}")

include_directories(
    ${ARGPARSE_DIR}
    ${LIB_DIR}
    ${EXE_DIR}
    ${CONAN_INCLUDE_DIRS_SPDLOG}
    )

add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC CONAN_PKG::catch2 ${TEST_EXTRA_LIBS})
target_link_libraries(catch_main PRIVATE project_options)


# ############### Arghandler ################
set(ARGHANDLER_TEST_FILES arghandler_test.cpp ../src/arghandler.cpp ../src/arghandler.hpp)

add_executable(arghandler_tests ${ARGHANDLER_TEST_FILES})
target_link_libraries(
    arghandler_tests
    PRIVATE
        project_warnings
        project_options
        catch_main
        ${ARGPARSE_NAME}
    )

catch_discover_tests(
    arghandler_tests
    TEST_PREFIX
    "arghandler."
    REPORTER
    xml
    OUTPUT_DIR
    .
    OUTPUT_PREFIX
    "arghandler."
    OUTPUT_SUFFIX
    .xml
    )

# ############### ArgParse ################
set(ARGPARSE_TEST_FILES argparse_test.cpp ../argparse/argparse.cpp ../argparse/argparse.hpp)

add_executable(argparse_test ${ARGPARSE_TEST_FILES})
target_link_libraries(argparse_test PRIVATE project_warnings project_options catch_main)

catch_discover_tests(
    argparse_test
    TEST_PREFIX
    "argparse."
    REPORTER
    xml
    OUTPUT_DIR
    .
    OUTPUT_PREFIX
    "argparse."
    OUTPUT_SUFFIX
    .xml
    )
