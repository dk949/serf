macro (include_files)
    file(
        GLOB
        SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "*.cpp"
        )
    file(
        GLOB
        HEADER_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "*.hpp"
        )
endmacro (include_files)
