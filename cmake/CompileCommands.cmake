set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

macro (link_compile_commands)
    if (CMAKE_EXPORT_COMPILE_COMMANDS)
        set(current_list_path ${CMAKE_CURRENT_LIST_DIR})

        string(
            REGEX
            REPLACE
                "\:|\/|\\|\ "
                "_"
                dir
                ${current_list_path}
            )

        if (CMAKE_EXPORT_COMPILE_COMMANDS)
            add_custom_target(
                ${dir}_compile_commands ALL
                COMMAND
                    ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/compile_commands.json
                    ${current_list_path}/compile_commands.json
                )
        endif ()

        unset(current_list_path)
        unset(dir)
    endif (CMAKE_EXPORT_COMPILE_COMMANDS)
endmacro (link_compile_commands)
