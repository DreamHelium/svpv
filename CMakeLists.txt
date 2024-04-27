CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT( svpv )

set(CMAKE_BUILD_TYPE Debug)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig)

pkg_search_module(GIO REQUIRED gio-2.0)
pkg_search_module(dhutil REQUIRED libdhutil)
pkg_search_module(XML REQUIRED tinyxml2)

add_subdirectory(src)
