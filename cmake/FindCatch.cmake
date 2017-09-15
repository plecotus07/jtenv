#.rst:
# FindCatch
# ---------
#
# Finds Catch test framework
#
# This will define the following variables:
#
# Catch_FOUND       - True if the system ha the Catch library
# Catch_INCLUDE_DIRS - Directory containing the header files.

find_path(Catch_INCLUDE_DIR
  NAMES catch/catch.hpp)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Catch
  FOUND_VAR Catch_FOUND
  REQUIRED_VARS Catch_INCLUDE_DIR)
if (Catch_FOUND)
  set (Catch_INCLUDE_DIRS ${Catch_INCLUDE_DIR})
  message("-- Found: Catch test framework.")
endif()

mark_as_advanced(Catch_INCLUDE_DIR)
