# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar"

# Include any dependencies generated for this target.
include CMakeFiles/foobar.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/foobar.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/foobar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/foobar.dir/flags.make

CMakeFiles/foobar.dir/foobar.c.o: CMakeFiles/foobar.dir/flags.make
CMakeFiles/foobar.dir/foobar.c.o: foobar.c
CMakeFiles/foobar.dir/foobar.c.o: CMakeFiles/foobar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/foobar.dir/foobar.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/foobar.dir/foobar.c.o -MF CMakeFiles/foobar.dir/foobar.c.o.d -o CMakeFiles/foobar.dir/foobar.c.o -c "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar/foobar.c"

CMakeFiles/foobar.dir/foobar.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/foobar.dir/foobar.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar/foobar.c" > CMakeFiles/foobar.dir/foobar.c.i

CMakeFiles/foobar.dir/foobar.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/foobar.dir/foobar.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar/foobar.c" -o CMakeFiles/foobar.dir/foobar.c.s

CMakeFiles/foobar.dir/foo.c.o: CMakeFiles/foobar.dir/flags.make
CMakeFiles/foobar.dir/foo.c.o: foo.c
CMakeFiles/foobar.dir/foo.c.o: CMakeFiles/foobar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/foobar.dir/foo.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/foobar.dir/foo.c.o -MF CMakeFiles/foobar.dir/foo.c.o.d -o CMakeFiles/foobar.dir/foo.c.o -c "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar/foo.c"

CMakeFiles/foobar.dir/foo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/foobar.dir/foo.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar/foo.c" > CMakeFiles/foobar.dir/foo.c.i

CMakeFiles/foobar.dir/foo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/foobar.dir/foo.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar/foo.c" -o CMakeFiles/foobar.dir/foo.c.s

CMakeFiles/foobar.dir/bar.c.o: CMakeFiles/foobar.dir/flags.make
CMakeFiles/foobar.dir/bar.c.o: bar.c
CMakeFiles/foobar.dir/bar.c.o: CMakeFiles/foobar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/foobar.dir/bar.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/foobar.dir/bar.c.o -MF CMakeFiles/foobar.dir/bar.c.o.d -o CMakeFiles/foobar.dir/bar.c.o -c "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar/bar.c"

CMakeFiles/foobar.dir/bar.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/foobar.dir/bar.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar/bar.c" > CMakeFiles/foobar.dir/bar.c.i

CMakeFiles/foobar.dir/bar.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/foobar.dir/bar.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar/bar.c" -o CMakeFiles/foobar.dir/bar.c.s

# Object files for target foobar
foobar_OBJECTS = \
"CMakeFiles/foobar.dir/foobar.c.o" \
"CMakeFiles/foobar.dir/foo.c.o" \
"CMakeFiles/foobar.dir/bar.c.o"

# External object files for target foobar
foobar_EXTERNAL_OBJECTS =

foobar: CMakeFiles/foobar.dir/foobar.c.o
foobar: CMakeFiles/foobar.dir/foo.c.o
foobar: CMakeFiles/foobar.dir/bar.c.o
foobar: CMakeFiles/foobar.dir/build.make
foobar: CMakeFiles/foobar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable foobar"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/foobar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/foobar.dir/build: foobar
.PHONY : CMakeFiles/foobar.dir/build

CMakeFiles/foobar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/foobar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/foobar.dir/clean

CMakeFiles/foobar.dir/depend:
	cd "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar" "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar" "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar" "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar" "/net/cremi/kbalavoine/Bureau/espaces/travail/FAC/L2 Info/Projet Technologique/Semaine 4/foobar/CMakeFiles/foobar.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/foobar.dir/depend

