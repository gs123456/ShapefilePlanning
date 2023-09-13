#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "shp" for configuration ""
set_property(TARGET shp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(shp PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "-lm"
  IMPORTED_LOCATION_NOCONFIG "/usr/local/lib/libshp.so.1.5.0"
  IMPORTED_SONAME_NOCONFIG "libshp.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS shp )
list(APPEND _IMPORT_CHECK_FILES_FOR_shp "/usr/local/lib/libshp.so.1.5.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
