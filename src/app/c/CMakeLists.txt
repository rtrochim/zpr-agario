macro(add_app _NAME)
    add_executable(${_NAME} ${_NAME}.cpp)
    target_link_libraries(${_NAME} seasocks "${ZLIB_LIBRARIES}")
    include_directories(${SQLITE3_INCLUDE_DIRS})
    target_link_libraries(${_NAME} sqlite3 "${SQLITE3_LIBRARIES}")
endmacro()


add_app(agario)

add_custom_command(TARGET agario POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/src/agario $<TARGET_FILE_DIR:agario>/src/agario)
