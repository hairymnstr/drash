target_include_directories(${PROJ_NAME} PRIVATE
                            ${CMAKE_CURRENT_LIST_DIR}/inc
                            ${CMAKE_CURRENT_LIST_DIR}/lib/optparse)
target_sources(${PROJ_NAME} PRIVATE
                ${CMAKE_CURRENT_LIST_DIR}/src/drash.c
                ${CMAKE_CURRENT_LIST_DIR}/src/drash_builtin_commands.c)