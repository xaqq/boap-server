# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xaqq/Documents/boap-server/tp3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xaqq/Documents/boap-server/tp3/build

# Include any dependencies generated for this target.
include CMakeFiles/tp3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tp3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tp3.dir/flags.make

CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o: CMakeFiles/tp3.dir/flags.make
CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o: ../src/TcpProtocolHandler.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xaqq/Documents/boap-server/tp3/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o -c /home/xaqq/Documents/boap-server/tp3/src/TcpProtocolHandler.cpp

CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xaqq/Documents/boap-server/tp3/src/TcpProtocolHandler.cpp > CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.i

CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xaqq/Documents/boap-server/tp3/src/TcpProtocolHandler.cpp -o CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.s

CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o.requires:
.PHONY : CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o.requires

CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o.provides: CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o.requires
	$(MAKE) -f CMakeFiles/tp3.dir/build.make CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o.provides.build
.PHONY : CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o.provides

CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o.provides.build: CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o

CMakeFiles/tp3.dir/src/BoapFactory.cpp.o: CMakeFiles/tp3.dir/flags.make
CMakeFiles/tp3.dir/src/BoapFactory.cpp.o: ../src/BoapFactory.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xaqq/Documents/boap-server/tp3/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tp3.dir/src/BoapFactory.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tp3.dir/src/BoapFactory.cpp.o -c /home/xaqq/Documents/boap-server/tp3/src/BoapFactory.cpp

CMakeFiles/tp3.dir/src/BoapFactory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tp3.dir/src/BoapFactory.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/xaqq/Documents/boap-server/tp3/src/BoapFactory.cpp > CMakeFiles/tp3.dir/src/BoapFactory.cpp.i

CMakeFiles/tp3.dir/src/BoapFactory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tp3.dir/src/BoapFactory.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/xaqq/Documents/boap-server/tp3/src/BoapFactory.cpp -o CMakeFiles/tp3.dir/src/BoapFactory.cpp.s

CMakeFiles/tp3.dir/src/BoapFactory.cpp.o.requires:
.PHONY : CMakeFiles/tp3.dir/src/BoapFactory.cpp.o.requires

CMakeFiles/tp3.dir/src/BoapFactory.cpp.o.provides: CMakeFiles/tp3.dir/src/BoapFactory.cpp.o.requires
	$(MAKE) -f CMakeFiles/tp3.dir/build.make CMakeFiles/tp3.dir/src/BoapFactory.cpp.o.provides.build
.PHONY : CMakeFiles/tp3.dir/src/BoapFactory.cpp.o.provides

CMakeFiles/tp3.dir/src/BoapFactory.cpp.o.provides.build: CMakeFiles/tp3.dir/src/BoapFactory.cpp.o

# Object files for target tp3
tp3_OBJECTS = \
"CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o" \
"CMakeFiles/tp3.dir/src/BoapFactory.cpp.o"

# External object files for target tp3
tp3_EXTERNAL_OBJECTS =

libtp3.so: CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o
libtp3.so: CMakeFiles/tp3.dir/src/BoapFactory.cpp.o
libtp3.so: CMakeFiles/tp3.dir/build.make
libtp3.so: CMakeFiles/tp3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libtp3.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tp3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tp3.dir/build: libtp3.so
.PHONY : CMakeFiles/tp3.dir/build

CMakeFiles/tp3.dir/requires: CMakeFiles/tp3.dir/src/TcpProtocolHandler.cpp.o.requires
CMakeFiles/tp3.dir/requires: CMakeFiles/tp3.dir/src/BoapFactory.cpp.o.requires
.PHONY : CMakeFiles/tp3.dir/requires

CMakeFiles/tp3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tp3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tp3.dir/clean

CMakeFiles/tp3.dir/depend:
	cd /home/xaqq/Documents/boap-server/tp3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xaqq/Documents/boap-server/tp3 /home/xaqq/Documents/boap-server/tp3 /home/xaqq/Documents/boap-server/tp3/build /home/xaqq/Documents/boap-server/tp3/build /home/xaqq/Documents/boap-server/tp3/build/CMakeFiles/tp3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tp3.dir/depend

