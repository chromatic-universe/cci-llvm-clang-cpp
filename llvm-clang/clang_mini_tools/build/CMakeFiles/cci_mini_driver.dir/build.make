# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /cci/dev_t/bin/cmake

# The command to remove a file.
RM = /cci/dev_t/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools/build

# Include any dependencies generated for this target.
include CMakeFiles/cci_mini_driver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cci_mini_driver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cci_mini_driver.dir/flags.make

CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o: CMakeFiles/cci_mini_driver.dir/flags.make
CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o: ../clang_mini_driver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o"
	/cci/dev_t/bin/clang++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o -c /cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools/clang_mini_driver.cpp

CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.i"
	/cci/dev_t/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools/clang_mini_driver.cpp > CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.i

CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.s"
	/cci/dev_t/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools/clang_mini_driver.cpp -o CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.s

CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o.requires:

.PHONY : CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o.requires

CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o.provides: CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o.requires
	$(MAKE) -f CMakeFiles/cci_mini_driver.dir/build.make CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o.provides.build
.PHONY : CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o.provides

CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o.provides.build: CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o


CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o: CMakeFiles/cci_mini_driver.dir/flags.make
CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o: ../mini_driver_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o"
	/cci/dev_t/bin/clang++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o -c /cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools/mini_driver_main.cpp

CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.i"
	/cci/dev_t/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools/mini_driver_main.cpp > CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.i

CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.s"
	/cci/dev_t/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools/mini_driver_main.cpp -o CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.s

CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o.requires:

.PHONY : CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o.requires

CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o.provides: CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o.requires
	$(MAKE) -f CMakeFiles/cci_mini_driver.dir/build.make CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o.provides.build
.PHONY : CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o.provides

CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o.provides.build: CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o


# Object files for target cci_mini_driver
cci_mini_driver_OBJECTS = \
"CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o" \
"CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o"

# External object files for target cci_mini_driver
cci_mini_driver_EXTERNAL_OBJECTS =

cci_mini_driver: CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o
cci_mini_driver: CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o
cci_mini_driver: CMakeFiles/cci_mini_driver.dir/build.make
cci_mini_driver: CMakeFiles/cci_mini_driver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable cci_mini_driver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cci_mini_driver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cci_mini_driver.dir/build: cci_mini_driver

.PHONY : CMakeFiles/cci_mini_driver.dir/build

CMakeFiles/cci_mini_driver.dir/requires: CMakeFiles/cci_mini_driver.dir/clang_mini_driver.cpp.o.requires
CMakeFiles/cci_mini_driver.dir/requires: CMakeFiles/cci_mini_driver.dir/mini_driver_main.cpp.o.requires

.PHONY : CMakeFiles/cci_mini_driver.dir/requires

CMakeFiles/cci_mini_driver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cci_mini_driver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cci_mini_driver.dir/clean

CMakeFiles/cci_mini_driver.dir/depend:
	cd /cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools /cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools /cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools/build /cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools/build /cci/cci_src/master/git_repo_1/llvm-clang/clang_mini_tools/build/CMakeFiles/cci_mini_driver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cci_mini_driver.dir/depend

