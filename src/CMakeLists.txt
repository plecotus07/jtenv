set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if (CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-Wall -Weffc++ -Wextra -Wold-style-cast")
elseif (MSVC)
  set(COMPILE_OPTIONS "/W4")
endif()

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/projectconf_jtenv.cpp.in
                ${CMAKE_BINARY_DIR}/projectconf_jtenv.cpp
                @ONLY)

add_executable (jtenv
	main.cpp
	workspace_jtenv.cpp
	project_jtenv.cpp
	mvcapp_jtenv.cpp
	addressparser_jtenv.cpp
	mvcviewclicommon_jtenv.cpp
	mvcviewcliproject_jtenv.cpp
	mvcviewcliconfig_jtenv.cpp
	mvcviewclimain_jtenv.cpp
	mvcctrlmain_jtenv.cpp
	mvcctrlconfigedit_jtenv.cpp
  mvcctrlprojectedit_jtenv.cpp
	mvcmodelconfig_jtenv.cpp
	mvcmodelconfigedit_jtenv.cpp
	mvcmodelitemselection_jtenv.cpp
	mvcmodelprojectedit_jtenv.cpp
	mvcmodelworkspaces_jtenv.cpp
  mvceditorcliconfig_jtenv.cpp
  mvceditorcliitem_jtenv.cpp
	${CMAKE_BINARY_DIR}/projectconf_jtenv.cpp
  jkpp/mvcapp_jkpp.cpp
  jkpp/mvcviewcli_jkpp.cpp
	jkpp/mvcmodelimpl_jkpp.cpp
	jkpp/filesystem_jkpp.cpp
	jkpp/gitsubproc_jkpp.cpp)

find_package(Boost COMPONENTS system filesystem REQUIRED)
target_link_libraries(jtenv
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
target_include_directories(jtenv PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
target_include_directories(jtenv PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/jkpp>)

find_package(Catch REQUIRED)
add_executable (utjtenv EXCLUDE_FROM_ALL
	test.cpp
	project_jtenv.cpp
	workspace_jtenv.cpp
	addressparser_jtenv.cpp
	addressparser_test_jtenv.cpp
	${CMAKE_BINARY_DIR}/projectconf_jtenv.cpp
	jkpp/filesystem_jkpp.cpp
  jkpp/gitsubproc_jkpp.cpp)

target_include_directories(utjtenv PRIVATE ${Catch_INCLUDE_DIRS})
target_include_directories(utjtenv PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(utjtenv PRIVATE ${CMAKE_CURRENT_LIST_DIR}/jkpp)
target_link_libraries(utjtenv
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)

add_test (NAME test_jtenv
          COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/utjtenv
				WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../tmp )
set_tests_properties(test_jtenv PROPERTIES DEPENDS utjtenv)

install (TARGETS jtenv
         DESTINATION ${CMAKE_INSTALL_BINDIR})
