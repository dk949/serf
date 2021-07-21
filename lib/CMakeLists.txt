link_compile_commands()

set(LIB_NAME gitpac)

set(SOURCE_FILES gitpac.cpp)

set(HEADER_FILES gitpac.hpp)

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${LIB_NAME} SYSTEM PRIVATE ${CONAN_INCLUDE_DIRS_SPDLOG})
target_include_directories(${LIB_NAME} SYSTEM PRIVATE ${CONAN_INCLUDE_DIRS_NLOHMANN_JSON})
target_include_directories(${LIB_NAME} SYSTEM PRIVATE ${CONAN_INCLUDE_DIRS_LIBGIT2})

target_link_libraries(
    ${LIB_NAME}
    PRIVATE
        project_options
        project_warnings
        CONAN_PKG::spdlog
        CONAN_PKG::nlohmann_json
        CONAN_PKG::libgit2
    )
