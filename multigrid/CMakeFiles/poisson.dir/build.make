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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nathan/git/multigrid

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nathan/git/multigrid

# Include any dependencies generated for this target.
include CMakeFiles/poisson.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/poisson.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/poisson.dir/flags.make

CMakeFiles/poisson.dir/fdarray.cpp.o: CMakeFiles/poisson.dir/flags.make
CMakeFiles/poisson.dir/fdarray.cpp.o: fdarray.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nathan/git/multigrid/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/poisson.dir/fdarray.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/poisson.dir/fdarray.cpp.o -c /home/nathan/git/multigrid/fdarray.cpp

CMakeFiles/poisson.dir/fdarray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/poisson.dir/fdarray.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nathan/git/multigrid/fdarray.cpp > CMakeFiles/poisson.dir/fdarray.cpp.i

CMakeFiles/poisson.dir/fdarray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/poisson.dir/fdarray.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nathan/git/multigrid/fdarray.cpp -o CMakeFiles/poisson.dir/fdarray.cpp.s

CMakeFiles/poisson.dir/fdarray.cpp.o.requires:
.PHONY : CMakeFiles/poisson.dir/fdarray.cpp.o.requires

CMakeFiles/poisson.dir/fdarray.cpp.o.provides: CMakeFiles/poisson.dir/fdarray.cpp.o.requires
	$(MAKE) -f CMakeFiles/poisson.dir/build.make CMakeFiles/poisson.dir/fdarray.cpp.o.provides.build
.PHONY : CMakeFiles/poisson.dir/fdarray.cpp.o.provides

CMakeFiles/poisson.dir/fdarray.cpp.o.provides.build: CMakeFiles/poisson.dir/fdarray.cpp.o

CMakeFiles/poisson.dir/settings.cpp.o: CMakeFiles/poisson.dir/flags.make
CMakeFiles/poisson.dir/settings.cpp.o: settings.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nathan/git/multigrid/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/poisson.dir/settings.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/poisson.dir/settings.cpp.o -c /home/nathan/git/multigrid/settings.cpp

CMakeFiles/poisson.dir/settings.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/poisson.dir/settings.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nathan/git/multigrid/settings.cpp > CMakeFiles/poisson.dir/settings.cpp.i

CMakeFiles/poisson.dir/settings.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/poisson.dir/settings.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nathan/git/multigrid/settings.cpp -o CMakeFiles/poisson.dir/settings.cpp.s

CMakeFiles/poisson.dir/settings.cpp.o.requires:
.PHONY : CMakeFiles/poisson.dir/settings.cpp.o.requires

CMakeFiles/poisson.dir/settings.cpp.o.provides: CMakeFiles/poisson.dir/settings.cpp.o.requires
	$(MAKE) -f CMakeFiles/poisson.dir/build.make CMakeFiles/poisson.dir/settings.cpp.o.provides.build
.PHONY : CMakeFiles/poisson.dir/settings.cpp.o.provides

CMakeFiles/poisson.dir/settings.cpp.o.provides.build: CMakeFiles/poisson.dir/settings.cpp.o

CMakeFiles/poisson.dir/multigrid_base.cpp.o: CMakeFiles/poisson.dir/flags.make
CMakeFiles/poisson.dir/multigrid_base.cpp.o: multigrid_base.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nathan/git/multigrid/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/poisson.dir/multigrid_base.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/poisson.dir/multigrid_base.cpp.o -c /home/nathan/git/multigrid/multigrid_base.cpp

CMakeFiles/poisson.dir/multigrid_base.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/poisson.dir/multigrid_base.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nathan/git/multigrid/multigrid_base.cpp > CMakeFiles/poisson.dir/multigrid_base.cpp.i

CMakeFiles/poisson.dir/multigrid_base.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/poisson.dir/multigrid_base.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nathan/git/multigrid/multigrid_base.cpp -o CMakeFiles/poisson.dir/multigrid_base.cpp.s

CMakeFiles/poisson.dir/multigrid_base.cpp.o.requires:
.PHONY : CMakeFiles/poisson.dir/multigrid_base.cpp.o.requires

CMakeFiles/poisson.dir/multigrid_base.cpp.o.provides: CMakeFiles/poisson.dir/multigrid_base.cpp.o.requires
	$(MAKE) -f CMakeFiles/poisson.dir/build.make CMakeFiles/poisson.dir/multigrid_base.cpp.o.provides.build
.PHONY : CMakeFiles/poisson.dir/multigrid_base.cpp.o.provides

CMakeFiles/poisson.dir/multigrid_base.cpp.o.provides.build: CMakeFiles/poisson.dir/multigrid_base.cpp.o

CMakeFiles/poisson.dir/fdvecarray.cpp.o: CMakeFiles/poisson.dir/flags.make
CMakeFiles/poisson.dir/fdvecarray.cpp.o: fdvecarray.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nathan/git/multigrid/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/poisson.dir/fdvecarray.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/poisson.dir/fdvecarray.cpp.o -c /home/nathan/git/multigrid/fdvecarray.cpp

CMakeFiles/poisson.dir/fdvecarray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/poisson.dir/fdvecarray.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nathan/git/multigrid/fdvecarray.cpp > CMakeFiles/poisson.dir/fdvecarray.cpp.i

CMakeFiles/poisson.dir/fdvecarray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/poisson.dir/fdvecarray.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nathan/git/multigrid/fdvecarray.cpp -o CMakeFiles/poisson.dir/fdvecarray.cpp.s

CMakeFiles/poisson.dir/fdvecarray.cpp.o.requires:
.PHONY : CMakeFiles/poisson.dir/fdvecarray.cpp.o.requires

CMakeFiles/poisson.dir/fdvecarray.cpp.o.provides: CMakeFiles/poisson.dir/fdvecarray.cpp.o.requires
	$(MAKE) -f CMakeFiles/poisson.dir/build.make CMakeFiles/poisson.dir/fdvecarray.cpp.o.provides.build
.PHONY : CMakeFiles/poisson.dir/fdvecarray.cpp.o.provides

CMakeFiles/poisson.dir/fdvecarray.cpp.o.provides.build: CMakeFiles/poisson.dir/fdvecarray.cpp.o

CMakeFiles/poisson.dir/boundary_conditions.cpp.o: CMakeFiles/poisson.dir/flags.make
CMakeFiles/poisson.dir/boundary_conditions.cpp.o: boundary_conditions.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nathan/git/multigrid/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/poisson.dir/boundary_conditions.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/poisson.dir/boundary_conditions.cpp.o -c /home/nathan/git/multigrid/boundary_conditions.cpp

CMakeFiles/poisson.dir/boundary_conditions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/poisson.dir/boundary_conditions.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nathan/git/multigrid/boundary_conditions.cpp > CMakeFiles/poisson.dir/boundary_conditions.cpp.i

CMakeFiles/poisson.dir/boundary_conditions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/poisson.dir/boundary_conditions.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nathan/git/multigrid/boundary_conditions.cpp -o CMakeFiles/poisson.dir/boundary_conditions.cpp.s

CMakeFiles/poisson.dir/boundary_conditions.cpp.o.requires:
.PHONY : CMakeFiles/poisson.dir/boundary_conditions.cpp.o.requires

CMakeFiles/poisson.dir/boundary_conditions.cpp.o.provides: CMakeFiles/poisson.dir/boundary_conditions.cpp.o.requires
	$(MAKE) -f CMakeFiles/poisson.dir/build.make CMakeFiles/poisson.dir/boundary_conditions.cpp.o.provides.build
.PHONY : CMakeFiles/poisson.dir/boundary_conditions.cpp.o.provides

CMakeFiles/poisson.dir/boundary_conditions.cpp.o.provides.build: CMakeFiles/poisson.dir/boundary_conditions.cpp.o

CMakeFiles/poisson.dir/multigrid_linear.cpp.o: CMakeFiles/poisson.dir/flags.make
CMakeFiles/poisson.dir/multigrid_linear.cpp.o: multigrid_linear.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nathan/git/multigrid/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/poisson.dir/multigrid_linear.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/poisson.dir/multigrid_linear.cpp.o -c /home/nathan/git/multigrid/multigrid_linear.cpp

CMakeFiles/poisson.dir/multigrid_linear.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/poisson.dir/multigrid_linear.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nathan/git/multigrid/multigrid_linear.cpp > CMakeFiles/poisson.dir/multigrid_linear.cpp.i

CMakeFiles/poisson.dir/multigrid_linear.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/poisson.dir/multigrid_linear.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nathan/git/multigrid/multigrid_linear.cpp -o CMakeFiles/poisson.dir/multigrid_linear.cpp.s

CMakeFiles/poisson.dir/multigrid_linear.cpp.o.requires:
.PHONY : CMakeFiles/poisson.dir/multigrid_linear.cpp.o.requires

CMakeFiles/poisson.dir/multigrid_linear.cpp.o.provides: CMakeFiles/poisson.dir/multigrid_linear.cpp.o.requires
	$(MAKE) -f CMakeFiles/poisson.dir/build.make CMakeFiles/poisson.dir/multigrid_linear.cpp.o.provides.build
.PHONY : CMakeFiles/poisson.dir/multigrid_linear.cpp.o.provides

CMakeFiles/poisson.dir/multigrid_linear.cpp.o.provides.build: CMakeFiles/poisson.dir/multigrid_linear.cpp.o

CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o: CMakeFiles/poisson.dir/flags.make
CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o: multigrid_nonlinear.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nathan/git/multigrid/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o -c /home/nathan/git/multigrid/multigrid_nonlinear.cpp

CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nathan/git/multigrid/multigrid_nonlinear.cpp > CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.i

CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nathan/git/multigrid/multigrid_nonlinear.cpp -o CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.s

CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o.requires:
.PHONY : CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o.requires

CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o.provides: CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o.requires
	$(MAKE) -f CMakeFiles/poisson.dir/build.make CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o.provides.build
.PHONY : CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o.provides

CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o.provides.build: CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o

CMakeFiles/poisson.dir/stack.cpp.o: CMakeFiles/poisson.dir/flags.make
CMakeFiles/poisson.dir/stack.cpp.o: stack.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nathan/git/multigrid/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/poisson.dir/stack.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/poisson.dir/stack.cpp.o -c /home/nathan/git/multigrid/stack.cpp

CMakeFiles/poisson.dir/stack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/poisson.dir/stack.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nathan/git/multigrid/stack.cpp > CMakeFiles/poisson.dir/stack.cpp.i

CMakeFiles/poisson.dir/stack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/poisson.dir/stack.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nathan/git/multigrid/stack.cpp -o CMakeFiles/poisson.dir/stack.cpp.s

CMakeFiles/poisson.dir/stack.cpp.o.requires:
.PHONY : CMakeFiles/poisson.dir/stack.cpp.o.requires

CMakeFiles/poisson.dir/stack.cpp.o.provides: CMakeFiles/poisson.dir/stack.cpp.o.requires
	$(MAKE) -f CMakeFiles/poisson.dir/build.make CMakeFiles/poisson.dir/stack.cpp.o.provides.build
.PHONY : CMakeFiles/poisson.dir/stack.cpp.o.provides

CMakeFiles/poisson.dir/stack.cpp.o.provides.build: CMakeFiles/poisson.dir/stack.cpp.o

CMakeFiles/poisson.dir/main.cpp.o: CMakeFiles/poisson.dir/flags.make
CMakeFiles/poisson.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nathan/git/multigrid/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/poisson.dir/main.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/poisson.dir/main.cpp.o -c /home/nathan/git/multigrid/main.cpp

CMakeFiles/poisson.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/poisson.dir/main.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nathan/git/multigrid/main.cpp > CMakeFiles/poisson.dir/main.cpp.i

CMakeFiles/poisson.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/poisson.dir/main.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nathan/git/multigrid/main.cpp -o CMakeFiles/poisson.dir/main.cpp.s

CMakeFiles/poisson.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/poisson.dir/main.cpp.o.requires

CMakeFiles/poisson.dir/main.cpp.o.provides: CMakeFiles/poisson.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/poisson.dir/build.make CMakeFiles/poisson.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/poisson.dir/main.cpp.o.provides

CMakeFiles/poisson.dir/main.cpp.o.provides.build: CMakeFiles/poisson.dir/main.cpp.o

CMakeFiles/poisson.dir/poisson.cpp.o: CMakeFiles/poisson.dir/flags.make
CMakeFiles/poisson.dir/poisson.cpp.o: poisson.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nathan/git/multigrid/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/poisson.dir/poisson.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/poisson.dir/poisson.cpp.o -c /home/nathan/git/multigrid/poisson.cpp

CMakeFiles/poisson.dir/poisson.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/poisson.dir/poisson.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nathan/git/multigrid/poisson.cpp > CMakeFiles/poisson.dir/poisson.cpp.i

CMakeFiles/poisson.dir/poisson.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/poisson.dir/poisson.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nathan/git/multigrid/poisson.cpp -o CMakeFiles/poisson.dir/poisson.cpp.s

CMakeFiles/poisson.dir/poisson.cpp.o.requires:
.PHONY : CMakeFiles/poisson.dir/poisson.cpp.o.requires

CMakeFiles/poisson.dir/poisson.cpp.o.provides: CMakeFiles/poisson.dir/poisson.cpp.o.requires
	$(MAKE) -f CMakeFiles/poisson.dir/build.make CMakeFiles/poisson.dir/poisson.cpp.o.provides.build
.PHONY : CMakeFiles/poisson.dir/poisson.cpp.o.provides

CMakeFiles/poisson.dir/poisson.cpp.o.provides.build: CMakeFiles/poisson.dir/poisson.cpp.o

CMakeFiles/poisson.dir/fdbase.cpp.o: CMakeFiles/poisson.dir/flags.make
CMakeFiles/poisson.dir/fdbase.cpp.o: fdbase.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nathan/git/multigrid/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/poisson.dir/fdbase.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/poisson.dir/fdbase.cpp.o -c /home/nathan/git/multigrid/fdbase.cpp

CMakeFiles/poisson.dir/fdbase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/poisson.dir/fdbase.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nathan/git/multigrid/fdbase.cpp > CMakeFiles/poisson.dir/fdbase.cpp.i

CMakeFiles/poisson.dir/fdbase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/poisson.dir/fdbase.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nathan/git/multigrid/fdbase.cpp -o CMakeFiles/poisson.dir/fdbase.cpp.s

CMakeFiles/poisson.dir/fdbase.cpp.o.requires:
.PHONY : CMakeFiles/poisson.dir/fdbase.cpp.o.requires

CMakeFiles/poisson.dir/fdbase.cpp.o.provides: CMakeFiles/poisson.dir/fdbase.cpp.o.requires
	$(MAKE) -f CMakeFiles/poisson.dir/build.make CMakeFiles/poisson.dir/fdbase.cpp.o.provides.build
.PHONY : CMakeFiles/poisson.dir/fdbase.cpp.o.provides

CMakeFiles/poisson.dir/fdbase.cpp.o.provides.build: CMakeFiles/poisson.dir/fdbase.cpp.o

# Object files for target poisson
poisson_OBJECTS = \
"CMakeFiles/poisson.dir/fdarray.cpp.o" \
"CMakeFiles/poisson.dir/settings.cpp.o" \
"CMakeFiles/poisson.dir/multigrid_base.cpp.o" \
"CMakeFiles/poisson.dir/fdvecarray.cpp.o" \
"CMakeFiles/poisson.dir/boundary_conditions.cpp.o" \
"CMakeFiles/poisson.dir/multigrid_linear.cpp.o" \
"CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o" \
"CMakeFiles/poisson.dir/stack.cpp.o" \
"CMakeFiles/poisson.dir/main.cpp.o" \
"CMakeFiles/poisson.dir/poisson.cpp.o" \
"CMakeFiles/poisson.dir/fdbase.cpp.o"

# External object files for target poisson
poisson_EXTERNAL_OBJECTS =

poisson: CMakeFiles/poisson.dir/fdarray.cpp.o
poisson: CMakeFiles/poisson.dir/settings.cpp.o
poisson: CMakeFiles/poisson.dir/multigrid_base.cpp.o
poisson: CMakeFiles/poisson.dir/fdvecarray.cpp.o
poisson: CMakeFiles/poisson.dir/boundary_conditions.cpp.o
poisson: CMakeFiles/poisson.dir/multigrid_linear.cpp.o
poisson: CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o
poisson: CMakeFiles/poisson.dir/stack.cpp.o
poisson: CMakeFiles/poisson.dir/main.cpp.o
poisson: CMakeFiles/poisson.dir/poisson.cpp.o
poisson: CMakeFiles/poisson.dir/fdbase.cpp.o
poisson: CMakeFiles/poisson.dir/build.make
poisson: /usr/local/lib/libmultigrid.a
poisson: /usr/lib/libblitz.so
poisson: /usr/lib/libnetcdf_c++.so
poisson: /usr/lib/libnetcdf.so
poisson: /usr/lib/x86_64-linux-gnu/libcurl.so
poisson: /usr/lib/x86_64-linux-gnu/libhdf5.so
poisson: /usr/lib/x86_64-linux-gnu/libpthread.so
poisson: /usr/lib/x86_64-linux-gnu/libz.so
poisson: /usr/lib/x86_64-linux-gnu/libdl.so
poisson: /usr/lib/x86_64-linux-gnu/libm.so
poisson: /usr/lib/x86_64-linux-gnu/libz.so
poisson: /home/nathan/Downloads/boost_1_64_0/stage/lib/libboost_program_options-mt.so
poisson: /usr/lib/x86_64-linux-gnu/libdl.so
poisson: /usr/lib/x86_64-linux-gnu/libm.so
poisson: /home/nathan/Downloads/boost_1_64_0/stage/lib/libboost_program_options-mt.so
poisson: CMakeFiles/poisson.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable poisson"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/poisson.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/poisson.dir/build: poisson
.PHONY : CMakeFiles/poisson.dir/build

CMakeFiles/poisson.dir/requires: CMakeFiles/poisson.dir/fdarray.cpp.o.requires
CMakeFiles/poisson.dir/requires: CMakeFiles/poisson.dir/settings.cpp.o.requires
CMakeFiles/poisson.dir/requires: CMakeFiles/poisson.dir/multigrid_base.cpp.o.requires
CMakeFiles/poisson.dir/requires: CMakeFiles/poisson.dir/fdvecarray.cpp.o.requires
CMakeFiles/poisson.dir/requires: CMakeFiles/poisson.dir/boundary_conditions.cpp.o.requires
CMakeFiles/poisson.dir/requires: CMakeFiles/poisson.dir/multigrid_linear.cpp.o.requires
CMakeFiles/poisson.dir/requires: CMakeFiles/poisson.dir/multigrid_nonlinear.cpp.o.requires
CMakeFiles/poisson.dir/requires: CMakeFiles/poisson.dir/stack.cpp.o.requires
CMakeFiles/poisson.dir/requires: CMakeFiles/poisson.dir/main.cpp.o.requires
CMakeFiles/poisson.dir/requires: CMakeFiles/poisson.dir/poisson.cpp.o.requires
CMakeFiles/poisson.dir/requires: CMakeFiles/poisson.dir/fdbase.cpp.o.requires
.PHONY : CMakeFiles/poisson.dir/requires

CMakeFiles/poisson.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/poisson.dir/cmake_clean.cmake
.PHONY : CMakeFiles/poisson.dir/clean

CMakeFiles/poisson.dir/depend:
	cd /home/nathan/git/multigrid && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nathan/git/multigrid /home/nathan/git/multigrid /home/nathan/git/multigrid /home/nathan/git/multigrid /home/nathan/git/multigrid/CMakeFiles/poisson.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/poisson.dir/depend
