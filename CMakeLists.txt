cmake_minimum_required (VERSION 3.2)
project (jtenv VERSION 0.0.0.1)
set (PROJECT_FULL_NAME "jtEnv")
set (PROJECT_RELEASE_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
set (RELEASE_DATE "2017-07-08")

include (GNUInstallDirs)
include (CTest)

set (CMAKE_EXPORT_COMPILE_COMMANDS 1)
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_subdirectory("src")

add_custom_target(tests COMMAND ${CMAKE_CTEST_COMMAND}
                  DEPENDS utjtenv)

configure_file(${CMAKE_SOURCE_DIR}/uninstall.cmake.in
               ${CMAKE_BINARY_DIR}/cmake/uninstall.cmake
               @ONLY)

add_custom_target(uninstall
                  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake/uninstall.cmake)
