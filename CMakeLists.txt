cmake_minimum_required(VERSION 3.3)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(zpr-agario VERSION 0.1)

message(STATUS "${PROJECT_NAME} ${PROJECT_VERSION}")


include(Compiler)
include(GNUInstallDirs)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.h.in internal/Config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_compile_options(-Wall -Wextra -pedantic)

find_package(Threads)

find_package(SQLite3)

if (NOT SQLITE3_FOUND)
    message(SEND_ERROR "Sqlite3 not found")
else()
    message(STATUS "Sqlite3 found")
endif ()


add_subdirectory("src")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}/
)

