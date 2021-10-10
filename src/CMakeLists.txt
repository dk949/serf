link_compile_commands()

set(EXE_NAME serf)

include_files()

add_executable(${EXE_NAME} ${SOURCE_FILES} ${HEADER_FILES})

add_dependencies(${EXE_NAME} ${LIB_NAME})
add_dependencies(${EXE_NAME} ${ARGPARSE_NAME})

target_include_directories(
    ${EXE_NAME} SYSTEM
    PRIVATE
        ${CONAN_INCLUDE_DIRS_SPDLOG}
        ${CONAN_INCLUDE_DIRS_LIBGIT2}
        ${LIB_DIR}
        ${ARGPARSE_DIR}
        ${CONAN_INCLUDE_DIRS_CTRE}
    )

target_link_libraries(
    ${EXE_NAME}
    PRIVATE
        project_options
        ${LIB_NAME}
        ${ARGPARSE_NAME}
        CONAN_PKG::spdlog
        CONAN_PKG::libgit2
    )
