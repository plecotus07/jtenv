set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if (CMAKE_COMPILER_IS_GNUCXX)
  set(COMPIILE_OPTIONS "-Wall -Weffc++ -Wextra -Wold-style-cast")
elseif (MSVC)
  set(COMPIILE_OPTIONS "/W4")
endif()

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/projectconf_jtenv.cpp.in
                ${CMAKE_BINARY_DIR}/projectconf_jtenv.cpp
                @ONLY)

add_executable (jtenv
	main.cpp
	item_jtenv.cpp
	itemfactory_jtenv.cpp
	mvcapp_jtenv.cpp
	mvcviewclimain_jtenv.cpp
	mvcctrlmain_jtenv.cpp
	mvcmodelconfig_jtenv.cpp
	config_jtenv.cpp
	${CMAKE_BINARY_DIR}/projectconf_jtenv.cpp
	jkpp/mvcmodelimpl_jkpp.cpp
	jkpp/config_jkpp.cpp
	jkpp/filesystem_jkpp.cpp)

find_package(Boost COMPONENTS system filesystem REQUIRED)
target_link_libraries(jtenv
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
target_include_directories(jtenv PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
target_include_directories(jtenv PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/jkpp>)

find_package(Catch REQUIRED)
add_executable (utjtenv EXCLUDE_FROM_ALL test.cpp)
target_include_directories(utjtenv PRIVATE ${Catch_INCLUDE_DIRS})
target_compile_options(utjtenv PRIVATE ${COMPILE_OPTIONS})

add_test (NAME test_jtenv
          COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/utjtenv)
set_tests_properties(test_jtenv PROPERTIES DEPENDS utjtenv)

install (TARGETS jtenv
         DESTINATION ${CMAKE_INSTALL_BINDIR})
