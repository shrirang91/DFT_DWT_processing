# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.4.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.4.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/shrirang/Documents/openCV codes/cse408phase3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/shrirang/Documents/openCV codes/cse408phase3"

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.4.0/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.4.0/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start "/Users/shrirang/Documents/openCV codes/cse408phase3/CMakeFiles" "/Users/shrirang/Documents/openCV codes/cse408phase3/CMakeFiles/progress.marks"
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start "/Users/shrirang/Documents/openCV codes/cse408phase3/CMakeFiles" 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named task1

# Build rule for target.
task1: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 task1
.PHONY : task1

# fast build rule for target.
task1/fast:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/build
.PHONY : task1/fast

#=============================================================================
# Target rules for targets named task2

# Build rule for target.
task2: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 task2
.PHONY : task2

# fast build rule for target.
task2/fast:
	$(MAKE) -f CMakeFiles/task2.dir/build.make CMakeFiles/task2.dir/build
.PHONY : task2/fast

#=============================================================================
# Target rules for targets named task3

# Build rule for target.
task3: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 task3
.PHONY : task3

# fast build rule for target.
task3/fast:
	$(MAKE) -f CMakeFiles/task3.dir/build.make CMakeFiles/task3.dir/build
.PHONY : task3/fast

task1-blockprocessor.o: task1-blockprocessor.cpp.o

.PHONY : task1-blockprocessor.o

# target to build an object file
task1-blockprocessor.cpp.o:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1-blockprocessor.cpp.o
.PHONY : task1-blockprocessor.cpp.o

task1-blockprocessor.i: task1-blockprocessor.cpp.i

.PHONY : task1-blockprocessor.i

# target to preprocess a source file
task1-blockprocessor.cpp.i:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1-blockprocessor.cpp.i
.PHONY : task1-blockprocessor.cpp.i

task1-blockprocessor.s: task1-blockprocessor.cpp.s

.PHONY : task1-blockprocessor.s

# target to generate assembly for a file
task1-blockprocessor.cpp.s:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1-blockprocessor.cpp.s
.PHONY : task1-blockprocessor.cpp.s

task1-dctprocessor.o: task1-dctprocessor.cpp.o

.PHONY : task1-dctprocessor.o

# target to build an object file
task1-dctprocessor.cpp.o:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1-dctprocessor.cpp.o
.PHONY : task1-dctprocessor.cpp.o

task1-dctprocessor.i: task1-dctprocessor.cpp.i

.PHONY : task1-dctprocessor.i

# target to preprocess a source file
task1-dctprocessor.cpp.i:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1-dctprocessor.cpp.i
.PHONY : task1-dctprocessor.cpp.i

task1-dctprocessor.s: task1-dctprocessor.cpp.s

.PHONY : task1-dctprocessor.s

# target to generate assembly for a file
task1-dctprocessor.cpp.s:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1-dctprocessor.cpp.s
.PHONY : task1-dctprocessor.cpp.s

task1-dwtprocessor.o: task1-dwtprocessor.cpp.o

.PHONY : task1-dwtprocessor.o

# target to build an object file
task1-dwtprocessor.cpp.o:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1-dwtprocessor.cpp.o
.PHONY : task1-dwtprocessor.cpp.o

task1-dwtprocessor.i: task1-dwtprocessor.cpp.i

.PHONY : task1-dwtprocessor.i

# target to preprocess a source file
task1-dwtprocessor.cpp.i:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1-dwtprocessor.cpp.i
.PHONY : task1-dwtprocessor.cpp.i

task1-dwtprocessor.s: task1-dwtprocessor.cpp.s

.PHONY : task1-dwtprocessor.s

# target to generate assembly for a file
task1-dwtprocessor.cpp.s:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1-dwtprocessor.cpp.s
.PHONY : task1-dwtprocessor.cpp.s

task1-histogramprocessor.o: task1-histogramprocessor.cpp.o

.PHONY : task1-histogramprocessor.o

# target to build an object file
task1-histogramprocessor.cpp.o:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1-histogramprocessor.cpp.o
.PHONY : task1-histogramprocessor.cpp.o

task1-histogramprocessor.i: task1-histogramprocessor.cpp.i

.PHONY : task1-histogramprocessor.i

# target to preprocess a source file
task1-histogramprocessor.cpp.i:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1-histogramprocessor.cpp.i
.PHONY : task1-histogramprocessor.cpp.i

task1-histogramprocessor.s: task1-histogramprocessor.cpp.s

.PHONY : task1-histogramprocessor.s

# target to generate assembly for a file
task1-histogramprocessor.cpp.s:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1-histogramprocessor.cpp.s
.PHONY : task1-histogramprocessor.cpp.s

task1.o: task1.cpp.o

.PHONY : task1.o

# target to build an object file
task1.cpp.o:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1.cpp.o
.PHONY : task1.cpp.o

task1.i: task1.cpp.i

.PHONY : task1.i

# target to preprocess a source file
task1.cpp.i:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1.cpp.i
.PHONY : task1.cpp.i

task1.s: task1.cpp.s

.PHONY : task1.s

# target to generate assembly for a file
task1.cpp.s:
	$(MAKE) -f CMakeFiles/task1.dir/build.make CMakeFiles/task1.dir/task1.cpp.s
.PHONY : task1.cpp.s

task2.o: task2.cpp.o

.PHONY : task2.o

# target to build an object file
task2.cpp.o:
	$(MAKE) -f CMakeFiles/task2.dir/build.make CMakeFiles/task2.dir/task2.cpp.o
.PHONY : task2.cpp.o

task2.i: task2.cpp.i

.PHONY : task2.i

# target to preprocess a source file
task2.cpp.i:
	$(MAKE) -f CMakeFiles/task2.dir/build.make CMakeFiles/task2.dir/task2.cpp.i
.PHONY : task2.cpp.i

task2.s: task2.cpp.s

.PHONY : task2.s

# target to generate assembly for a file
task2.cpp.s:
	$(MAKE) -f CMakeFiles/task2.dir/build.make CMakeFiles/task2.dir/task2.cpp.s
.PHONY : task2.cpp.s

task3.o: task3.cpp.o

.PHONY : task3.o

# target to build an object file
task3.cpp.o:
	$(MAKE) -f CMakeFiles/task3.dir/build.make CMakeFiles/task3.dir/task3.cpp.o
.PHONY : task3.cpp.o

task3.i: task3.cpp.i

.PHONY : task3.i

# target to preprocess a source file
task3.cpp.i:
	$(MAKE) -f CMakeFiles/task3.dir/build.make CMakeFiles/task3.dir/task3.cpp.i
.PHONY : task3.cpp.i

task3.s: task3.cpp.s

.PHONY : task3.s

# target to generate assembly for a file
task3.cpp.s:
	$(MAKE) -f CMakeFiles/task3.dir/build.make CMakeFiles/task3.dir/task3.cpp.s
.PHONY : task3.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... task3"
	@echo "... task2"
	@echo "... task1"
	@echo "... task1-blockprocessor.o"
	@echo "... task1-blockprocessor.i"
	@echo "... task1-blockprocessor.s"
	@echo "... task1-dctprocessor.o"
	@echo "... task1-dctprocessor.i"
	@echo "... task1-dctprocessor.s"
	@echo "... task1-dwtprocessor.o"
	@echo "... task1-dwtprocessor.i"
	@echo "... task1-dwtprocessor.s"
	@echo "... task1-histogramprocessor.o"
	@echo "... task1-histogramprocessor.i"
	@echo "... task1-histogramprocessor.s"
	@echo "... task1.o"
	@echo "... task1.i"
	@echo "... task1.s"
	@echo "... task2.o"
	@echo "... task2.i"
	@echo "... task2.s"
	@echo "... task3.o"
	@echo "... task3.i"
	@echo "... task3.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
