set(EXE_NAME serf)

set(SOURCE_FILES
    main.cpp
    arghandler.cpp
    )

set(HEADER_FILES
    arghandler.hpp
    )


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(src_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink  ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/src/compile_commands.json)


add_executable(${EXE_NAME} ${SOURCE_FILES} ${HEADER_FILES})

add_dependencies(${EXE_NAME} ${LIB_NAME})
add_dependencies(${EXE_NAME} ${ARGPARSE_NAME})
message(STATUS "ARGPARSE_NAME = ${ARGPARSE_NAME}")


target_include_directories(${EXE_NAME} SYSTEM PRIVATE ${CONAN_INCLUDE_DIRS_SPDLOG})
target_include_directories(${EXE_NAME} SYSTEM PRIVATE ${LIB_DIR})
target_include_directories(${EXE_NAME} SYSTEM PRIVATE ${ARGPARSE_DIR})

target_link_libraries(
        ${EXE_NAME}
        PRIVATE project_options
        ${LIB_NAME}
        ${ARGPARSE_NAME}
        CONAN_PKG::spdlog
        )
