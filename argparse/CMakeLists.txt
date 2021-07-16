set(ARGPARSE_NAME argparse)


set(SOURCE_FILES
    argparse.cpp
    )

set(HEADER_FILES
    argparse.hpp
    )


add_library(${ARGPARSE_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(argparse_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink  ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/argparse/compile_commands.json)


target_include_directories(${ARGPARSE_NAME} SYSTEM PRIVATE
    ${CONAN_INCLUDE_DIRS_SPDLOG}
    )

target_link_libraries(
    ${ARGPARSE_NAME}
    PRIVATE project_options
    project_warnings
    CONAN_PKG::spdlog
    )
