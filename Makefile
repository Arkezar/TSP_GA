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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arkezar/cpp/TSP_GA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arkezar/cpp/TSP_GA

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/arkezar/cpp/TSP_GA/CMakeFiles /home/arkezar/cpp/TSP_GA/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/arkezar/cpp/TSP_GA/CMakeFiles 0
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
# Target rules for targets named TSP_GA

# Build rule for target.
TSP_GA: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 TSP_GA
.PHONY : TSP_GA

# fast build rule for target.
TSP_GA/fast:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/build
.PHONY : TSP_GA/fast

data.o: data.cpp.o

.PHONY : data.o

# target to build an object file
data.cpp.o:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/data.cpp.o
.PHONY : data.cpp.o

data.i: data.cpp.i

.PHONY : data.i

# target to preprocess a source file
data.cpp.i:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/data.cpp.i
.PHONY : data.cpp.i

data.s: data.cpp.s

.PHONY : data.s

# target to generate assembly for a file
data.cpp.s:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/data.cpp.s
.PHONY : data.cpp.s

dataloader.o: dataloader.cpp.o

.PHONY : dataloader.o

# target to build an object file
dataloader.cpp.o:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/dataloader.cpp.o
.PHONY : dataloader.cpp.o

dataloader.i: dataloader.cpp.i

.PHONY : dataloader.i

# target to preprocess a source file
dataloader.cpp.i:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/dataloader.cpp.i
.PHONY : dataloader.cpp.i

dataloader.s: dataloader.cpp.s

.PHONY : dataloader.s

# target to generate assembly for a file
dataloader.cpp.s:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/dataloader.cpp.s
.PHONY : dataloader.cpp.s

genetic.o: genetic.cpp.o

.PHONY : genetic.o

# target to build an object file
genetic.cpp.o:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/genetic.cpp.o
.PHONY : genetic.cpp.o

genetic.i: genetic.cpp.i

.PHONY : genetic.i

# target to preprocess a source file
genetic.cpp.i:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/genetic.cpp.i
.PHONY : genetic.cpp.i

genetic.s: genetic.cpp.s

.PHONY : genetic.s

# target to generate assembly for a file
genetic.cpp.s:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/genetic.cpp.s
.PHONY : genetic.cpp.s

test.o: test.cpp.o

.PHONY : test.o

# target to build an object file
test.cpp.o:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/test.cpp.o
.PHONY : test.cpp.o

test.i: test.cpp.i

.PHONY : test.i

# target to preprocess a source file
test.cpp.i:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/test.cpp.i
.PHONY : test.cpp.i

test.s: test.cpp.s

.PHONY : test.s

# target to generate assembly for a file
test.cpp.s:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/test.cpp.s
.PHONY : test.cpp.s

tsp.o: tsp.cpp.o

.PHONY : tsp.o

# target to build an object file
tsp.cpp.o:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/tsp.cpp.o
.PHONY : tsp.cpp.o

tsp.i: tsp.cpp.i

.PHONY : tsp.i

# target to preprocess a source file
tsp.cpp.i:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/tsp.cpp.i
.PHONY : tsp.cpp.i

tsp.s: tsp.cpp.s

.PHONY : tsp.s

# target to generate assembly for a file
tsp.cpp.s:
	$(MAKE) -f CMakeFiles/TSP_GA.dir/build.make CMakeFiles/TSP_GA.dir/tsp.cpp.s
.PHONY : tsp.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... TSP_GA"
	@echo "... data.o"
	@echo "... data.i"
	@echo "... data.s"
	@echo "... dataloader.o"
	@echo "... dataloader.i"
	@echo "... dataloader.s"
	@echo "... genetic.o"
	@echo "... genetic.i"
	@echo "... genetic.s"
	@echo "... test.o"
	@echo "... test.i"
	@echo "... test.s"
	@echo "... tsp.o"
	@echo "... tsp.i"
	@echo "... tsp.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
