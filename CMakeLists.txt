cmake_minimum_required(VERSION 3.21)
project(ShapefileCppLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the path to the directory containing libshp.so
set(SHAPELIB_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/thirdparty/shapelib-1.5.0/build)


# Find libshp.so
find_library(SHAPELIB_LIBRARIES NAMES libshp.so PATHS ${SHAPELIB_LIBRARY_DIR})
find_library(SHAPELIB_LIBRARIES NAMES libshp.so.1 PATHS ${SHAPELIB_LIBRARY_DIR})
find_library(SHAPELIB_LIBRARIES NAMES libshp.so.1.5.0 PATHS ${SHAPELIB_LIBRARY_DIR})
# Add your source files here
set(   ShapefileCppLib_SOURCES 
    src/ShapefileReader.cpp
	src/Schema.cpp
	src/FeatureIterator.cpp
	src/GeometryType.cpp
	src/Bounds.cpp
	src/Geometry.cpp
	src/Point.cpp
	src/Line.cpp
	src/Ring.cpp
	src/Polygon.cpp
	src/MultiPoint.cpp
	src/MultiLine.cpp
	src/MultiPolygon.cpp
	src/Feature.cpp
	src/FieldType.cpp
	src/Field.cpp
	src/DataGet.cpp
	src/coorconv.cpp
	src/WGS84toUTM.cpp
	src/UTMtoWGS84.cpp
)

add_library(ShapefileCppLib STATIC ${ShapefileCppLib_SOURCES})

target_include_directories(ShapefileCppLib
    PUBLIC include
    PRIVATE src
)

target_link_libraries(ShapefileCppLib ${SHAPELIB_LIBRARIES})

# Add an executable for your main function
add_executable(ShapefileReaderApp src/main.cpp)
target_link_libraries(ShapefileReaderApp ShapefileCppLib)
