link_compile_commands()

set(ARGPARSE_NAME argparse)

include_files()

add_library(${ARGPARSE_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${ARGPARSE_NAME} SYSTEM PRIVATE ${CONAN_INCLUDE_DIRS_SPDLOG})

target_link_libraries(${ARGPARSE_NAME} PRIVATE project_options project_warnings CONAN_PKG::spdlog)
