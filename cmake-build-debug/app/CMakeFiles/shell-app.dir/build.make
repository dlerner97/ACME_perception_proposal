# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /snap/clion/169/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/169/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug"

# Include any dependencies generated for this target.
include app/CMakeFiles/shell-app.dir/depend.make
# Include the progress variables for this target.
include app/CMakeFiles/shell-app.dir/progress.make

# Include the compile flags for this target's objects.
include app/CMakeFiles/shell-app.dir/flags.make

app/CMakeFiles/shell-app.dir/main.cpp.o: app/CMakeFiles/shell-app.dir/flags.make
app/CMakeFiles/shell-app.dir/main.cpp.o: ../app/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object app/CMakeFiles/shell-app.dir/main.cpp.o"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shell-app.dir/main.cpp.o -c "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/main.cpp"

app/CMakeFiles/shell-app.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shell-app.dir/main.cpp.i"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/main.cpp" > CMakeFiles/shell-app.dir/main.cpp.i

app/CMakeFiles/shell-app.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shell-app.dir/main.cpp.s"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/main.cpp" -o CMakeFiles/shell-app.dir/main.cpp.s

app/CMakeFiles/shell-app.dir/ParamParser.cpp.o: app/CMakeFiles/shell-app.dir/flags.make
app/CMakeFiles/shell-app.dir/ParamParser.cpp.o: ../app/ParamParser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object app/CMakeFiles/shell-app.dir/ParamParser.cpp.o"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shell-app.dir/ParamParser.cpp.o -c "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/ParamParser.cpp"

app/CMakeFiles/shell-app.dir/ParamParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shell-app.dir/ParamParser.cpp.i"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/ParamParser.cpp" > CMakeFiles/shell-app.dir/ParamParser.cpp.i

app/CMakeFiles/shell-app.dir/ParamParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shell-app.dir/ParamParser.cpp.s"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/ParamParser.cpp" -o CMakeFiles/shell-app.dir/ParamParser.cpp.s

app/CMakeFiles/shell-app.dir/PositionEstimator.cpp.o: app/CMakeFiles/shell-app.dir/flags.make
app/CMakeFiles/shell-app.dir/PositionEstimator.cpp.o: ../app/PositionEstimator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object app/CMakeFiles/shell-app.dir/PositionEstimator.cpp.o"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shell-app.dir/PositionEstimator.cpp.o -c "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/PositionEstimator.cpp"

app/CMakeFiles/shell-app.dir/PositionEstimator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shell-app.dir/PositionEstimator.cpp.i"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/PositionEstimator.cpp" > CMakeFiles/shell-app.dir/PositionEstimator.cpp.i

app/CMakeFiles/shell-app.dir/PositionEstimator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shell-app.dir/PositionEstimator.cpp.s"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/PositionEstimator.cpp" -o CMakeFiles/shell-app.dir/PositionEstimator.cpp.s

app/CMakeFiles/shell-app.dir/VisionAPI.cpp.o: app/CMakeFiles/shell-app.dir/flags.make
app/CMakeFiles/shell-app.dir/VisionAPI.cpp.o: ../app/VisionAPI.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object app/CMakeFiles/shell-app.dir/VisionAPI.cpp.o"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shell-app.dir/VisionAPI.cpp.o -c "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/VisionAPI.cpp"

app/CMakeFiles/shell-app.dir/VisionAPI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shell-app.dir/VisionAPI.cpp.i"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/VisionAPI.cpp" > CMakeFiles/shell-app.dir/VisionAPI.cpp.i

app/CMakeFiles/shell-app.dir/VisionAPI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shell-app.dir/VisionAPI.cpp.s"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/VisionAPI.cpp" -o CMakeFiles/shell-app.dir/VisionAPI.cpp.s

app/CMakeFiles/shell-app.dir/HumanDetector.cpp.o: app/CMakeFiles/shell-app.dir/flags.make
app/CMakeFiles/shell-app.dir/HumanDetector.cpp.o: ../app/HumanDetector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object app/CMakeFiles/shell-app.dir/HumanDetector.cpp.o"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shell-app.dir/HumanDetector.cpp.o -c "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/HumanDetector.cpp"

app/CMakeFiles/shell-app.dir/HumanDetector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shell-app.dir/HumanDetector.cpp.i"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/HumanDetector.cpp" > CMakeFiles/shell-app.dir/HumanDetector.cpp.i

app/CMakeFiles/shell-app.dir/HumanDetector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shell-app.dir/HumanDetector.cpp.s"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app/HumanDetector.cpp" -o CMakeFiles/shell-app.dir/HumanDetector.cpp.s

# Object files for target shell-app
shell__app_OBJECTS = \
"CMakeFiles/shell-app.dir/main.cpp.o" \
"CMakeFiles/shell-app.dir/ParamParser.cpp.o" \
"CMakeFiles/shell-app.dir/PositionEstimator.cpp.o" \
"CMakeFiles/shell-app.dir/VisionAPI.cpp.o" \
"CMakeFiles/shell-app.dir/HumanDetector.cpp.o"

# External object files for target shell-app
shell__app_EXTERNAL_OBJECTS =

app/shell-app: app/CMakeFiles/shell-app.dir/main.cpp.o
app/shell-app: app/CMakeFiles/shell-app.dir/ParamParser.cpp.o
app/shell-app: app/CMakeFiles/shell-app.dir/PositionEstimator.cpp.o
app/shell-app: app/CMakeFiles/shell-app.dir/VisionAPI.cpp.o
app/shell-app: app/CMakeFiles/shell-app.dir/HumanDetector.cpp.o
app/shell-app: app/CMakeFiles/shell-app.dir/build.make
app/shell-app: /usr/local/lib/libopencv_gapi.so.4.5.4
app/shell-app: /usr/local/lib/libopencv_highgui.so.4.5.4
app/shell-app: /usr/local/lib/libopencv_ml.so.4.5.4
app/shell-app: /usr/local/lib/libopencv_objdetect.so.4.5.4
app/shell-app: /usr/local/lib/libopencv_photo.so.4.5.4
app/shell-app: /usr/local/lib/libopencv_stitching.so.4.5.4
app/shell-app: /usr/local/lib/libopencv_video.so.4.5.4
app/shell-app: /usr/local/lib/libopencv_videoio.so.4.5.4
app/shell-app: /usr/local/lib/libopencv_imgcodecs.so.4.5.4
app/shell-app: /usr/local/lib/libopencv_dnn.so.4.5.4
app/shell-app: /usr/local/lib/libopencv_calib3d.so.4.5.4
app/shell-app: /usr/local/lib/libopencv_features2d.so.4.5.4
app/shell-app: /usr/local/lib/libopencv_flann.so.4.5.4
app/shell-app: /usr/local/lib/libopencv_imgproc.so.4.5.4
app/shell-app: /usr/local/lib/libopencv_core.so.4.5.4
app/shell-app: app/CMakeFiles/shell-app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable shell-app"
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shell-app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
app/CMakeFiles/shell-app.dir/build: app/shell-app
.PHONY : app/CMakeFiles/shell-app.dir/build

app/CMakeFiles/shell-app.dir/clean:
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" && $(CMAKE_COMMAND) -P CMakeFiles/shell-app.dir/cmake_clean.cmake
.PHONY : app/CMakeFiles/shell-app.dir/clean

app/CMakeFiles/shell-app.dir/depend:
	cd "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal" "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/app" "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug" "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app" "/media/diane/My Passport/UMD Masters/Fall 2021/ENPM 808X/Assignments/Midterm/ACME_perception_proposal/cmake-build-debug/app/CMakeFiles/shell-app.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : app/CMakeFiles/shell-app.dir/depend

