# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gs/Shapfileplanning/thirdparty/shapelib-1.5.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gs/Shapfileplanning/thirdparty/shapelib-1.5.0/build

# Include any dependencies generated for this target.
include CMakeFiles/dbfcreate.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/dbfcreate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dbfcreate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dbfcreate.dir/flags.make

CMakeFiles/dbfcreate.dir/dbfcreate.c.o: CMakeFiles/dbfcreate.dir/flags.make
CMakeFiles/dbfcreate.dir/dbfcreate.c.o: ../dbfcreate.c
CMakeFiles/dbfcreate.dir/dbfcreate.c.o: CMakeFiles/dbfcreate.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gs/Shapfileplanning/thirdparty/shapelib-1.5.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/dbfcreate.dir/dbfcreate.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/dbfcreate.dir/dbfcreate.c.o -MF CMakeFiles/dbfcreate.dir/dbfcreate.c.o.d -o CMakeFiles/dbfcreate.dir/dbfcreate.c.o -c /home/gs/Shapfileplanning/thirdparty/shapelib-1.5.0/dbfcreate.c

CMakeFiles/dbfcreate.dir/dbfcreate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dbfcreate.dir/dbfcreate.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gs/Shapfileplanning/thirdparty/shapelib-1.5.0/dbfcreate.c > CMakeFiles/dbfcreate.dir/dbfcreate.c.i

CMakeFiles/dbfcreate.dir/dbfcreate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dbfcreate.dir/dbfcreate.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gs/Shapfileplanning/thirdparty/shapelib-1.5.0/dbfcreate.c -o CMakeFiles/dbfcreate.dir/dbfcreate.c.s

# Object files for target dbfcreate
dbfcreate_OBJECTS = \
"CMakeFiles/dbfcreate.dir/dbfcreate.c.o"

# External object files for target dbfcreate
dbfcreate_EXTERNAL_OBJECTS =

dbfcreate: CMakeFiles/dbfcreate.dir/dbfcreate.c.o
dbfcreate: CMakeFiles/dbfcreate.dir/build.make
dbfcreate: libshp.so.1.5.0
dbfcreate: CMakeFiles/dbfcreate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gs/Shapfileplanning/thirdparty/shapelib-1.5.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable dbfcreate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dbfcreate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dbfcreate.dir/build: dbfcreate
.PHONY : CMakeFiles/dbfcreate.dir/build

CMakeFiles/dbfcreate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dbfcreate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dbfcreate.dir/clean

CMakeFiles/dbfcreate.dir/depend:
	cd /home/gs/Shapfileplanning/thirdparty/shapelib-1.5.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gs/Shapfileplanning/thirdparty/shapelib-1.5.0 /home/gs/Shapfileplanning/thirdparty/shapelib-1.5.0 /home/gs/Shapfileplanning/thirdparty/shapelib-1.5.0/build /home/gs/Shapfileplanning/thirdparty/shapelib-1.5.0/build /home/gs/Shapfileplanning/thirdparty/shapelib-1.5.0/build/CMakeFiles/dbfcreate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dbfcreate.dir/depend

