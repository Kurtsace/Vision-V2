# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /opt/clion-2016.2.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2016.2.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/kurt/ClionProjects/Vision V2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/kurt/ClionProjects/Vision V2"

# Include any dependencies generated for this target.
include CMakeFiles/Vision_V2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Vision_V2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Vision_V2.dir/flags.make

CMakeFiles/Vision_V2.dir/main.cpp.o: CMakeFiles/Vision_V2.dir/flags.make
CMakeFiles/Vision_V2.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/kurt/ClionProjects/Vision V2/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Vision_V2.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Vision_V2.dir/main.cpp.o -c "/home/kurt/ClionProjects/Vision V2/main.cpp"

CMakeFiles/Vision_V2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Vision_V2.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/kurt/ClionProjects/Vision V2/main.cpp" > CMakeFiles/Vision_V2.dir/main.cpp.i

CMakeFiles/Vision_V2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Vision_V2.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/kurt/ClionProjects/Vision V2/main.cpp" -o CMakeFiles/Vision_V2.dir/main.cpp.s

CMakeFiles/Vision_V2.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Vision_V2.dir/main.cpp.o.requires

CMakeFiles/Vision_V2.dir/main.cpp.o.provides: CMakeFiles/Vision_V2.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Vision_V2.dir/build.make CMakeFiles/Vision_V2.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Vision_V2.dir/main.cpp.o.provides

CMakeFiles/Vision_V2.dir/main.cpp.o.provides.build: CMakeFiles/Vision_V2.dir/main.cpp.o


CMakeFiles/Vision_V2.dir/Vision.cpp.o: CMakeFiles/Vision_V2.dir/flags.make
CMakeFiles/Vision_V2.dir/Vision.cpp.o: Vision.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/kurt/ClionProjects/Vision V2/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Vision_V2.dir/Vision.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Vision_V2.dir/Vision.cpp.o -c "/home/kurt/ClionProjects/Vision V2/Vision.cpp"

CMakeFiles/Vision_V2.dir/Vision.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Vision_V2.dir/Vision.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/kurt/ClionProjects/Vision V2/Vision.cpp" > CMakeFiles/Vision_V2.dir/Vision.cpp.i

CMakeFiles/Vision_V2.dir/Vision.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Vision_V2.dir/Vision.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/kurt/ClionProjects/Vision V2/Vision.cpp" -o CMakeFiles/Vision_V2.dir/Vision.cpp.s

CMakeFiles/Vision_V2.dir/Vision.cpp.o.requires:

.PHONY : CMakeFiles/Vision_V2.dir/Vision.cpp.o.requires

CMakeFiles/Vision_V2.dir/Vision.cpp.o.provides: CMakeFiles/Vision_V2.dir/Vision.cpp.o.requires
	$(MAKE) -f CMakeFiles/Vision_V2.dir/build.make CMakeFiles/Vision_V2.dir/Vision.cpp.o.provides.build
.PHONY : CMakeFiles/Vision_V2.dir/Vision.cpp.o.provides

CMakeFiles/Vision_V2.dir/Vision.cpp.o.provides.build: CMakeFiles/Vision_V2.dir/Vision.cpp.o


# Object files for target Vision_V2
Vision_V2_OBJECTS = \
"CMakeFiles/Vision_V2.dir/main.cpp.o" \
"CMakeFiles/Vision_V2.dir/Vision.cpp.o"

# External object files for target Vision_V2
Vision_V2_EXTERNAL_OBJECTS =

Vision_V2: CMakeFiles/Vision_V2.dir/main.cpp.o
Vision_V2: CMakeFiles/Vision_V2.dir/Vision.cpp.o
Vision_V2: CMakeFiles/Vision_V2.dir/build.make
Vision_V2: /opt/ros/kinetic/lib/libopencv_xphoto3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_xobjdetect3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_tracking3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_surface_matching3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_structured_light3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_stereo3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_saliency3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_rgbd3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_reg3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_plot3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_optflow3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_line_descriptor3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_hdf3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_fuzzy3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_dpm3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_dnn3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_datasets3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_cvv3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_ccalib3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_bioinspired3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_bgsegm3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_aruco3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_viz3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_videostab3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_superres3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_stitching3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_photo3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_text3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_face3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_ximgproc3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_xfeatures2d3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_shape3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_video3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_objdetect3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_calib3d3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_features2d3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_ml3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_highgui3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_videoio3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_imgcodecs3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_imgproc3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_flann3.so.3.1.0
Vision_V2: /opt/ros/kinetic/lib/libopencv_core3.so.3.1.0
Vision_V2: CMakeFiles/Vision_V2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/kurt/ClionProjects/Vision V2/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Vision_V2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Vision_V2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Vision_V2.dir/build: Vision_V2

.PHONY : CMakeFiles/Vision_V2.dir/build

CMakeFiles/Vision_V2.dir/requires: CMakeFiles/Vision_V2.dir/main.cpp.o.requires
CMakeFiles/Vision_V2.dir/requires: CMakeFiles/Vision_V2.dir/Vision.cpp.o.requires

.PHONY : CMakeFiles/Vision_V2.dir/requires

CMakeFiles/Vision_V2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Vision_V2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Vision_V2.dir/clean

CMakeFiles/Vision_V2.dir/depend:
	cd "/home/kurt/ClionProjects/Vision V2" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/kurt/ClionProjects/Vision V2" "/home/kurt/ClionProjects/Vision V2" "/home/kurt/ClionProjects/Vision V2" "/home/kurt/ClionProjects/Vision V2" "/home/kurt/ClionProjects/Vision V2/CMakeFiles/Vision_V2.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Vision_V2.dir/depend

