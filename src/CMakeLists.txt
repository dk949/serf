set(SOURCE_FILES
        main.cpp
        )

set(HEADER_FILES
        )


add_executable(${EXE_NAME} ${SOURCE_FILES} ${HEADER_FILES})
add_dependencies(${EXE_NAME} ${LIB_NAME})


target_include_directories(${EXE_NAME} SYSTEM PRIVATE ${CONAN_INCLUDE_DIRS_SPDLOG})
target_include_directories(${EXE_NAME} SYSTEM PRIVATE ${CONAN_INCLUDE_DIRS_NLOHMANN_JSON})
target_include_directories(${EXE_NAME} SYSTEM PRIVATE ${CONAN_INCLUDE_DIRS_LIBGIT2})
target_include_directories(${EXE_NAME} SYSTEM PRIVATE ${LIB_DIR})

target_link_libraries(
        ${EXE_NAME}
        PRIVATE project_options
        ${LIB_NAME}
        CONAN_PKG::spdlog
        )

