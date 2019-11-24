macro(add_app _NAME)
    add_executable(${_NAME} ${_NAME}.cpp)
    target_link_libraries(${_NAME} seasocks "${ZLIB_LIBRARIES}")
endmacro()


add_app(agario)

add_custom_command(TARGET agario POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/src/agario $<TARGET_FILE_DIR:agario>/src/agario)
