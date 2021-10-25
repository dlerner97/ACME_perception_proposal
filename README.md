# ACME_perception_proposal
[![Build Status](https://app.travis-ci.com/dlerner97/ACME_perception_proposal.svg?branch=dev)](https://app.travis-ci.com/dlerner97/ACME_perception_proposal)
[![Coverage Status](https://coveralls.io/repos/github/dlerner97/ACME_perception_proposal/badge.svg?branch=main)](https://coveralls.io/github/dlerner97/ACME_perception_proposal?branch=dev)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

### Authors

- Dani Lerner (dlerner97)
* Dani Lerner graduated University of Maryland, College Park with a B.S. in Mechanical Engineering. Unhappy with the hardware life, Dani decided to pursue a Masters in Robotics at UMD as a steady transition to the realm of software.
- Diane Ngo (dngo13)
* Diane Ngo graduated from Kennesaw State University from Georgia with a B.S. in Mechatronics Engineering, having specialized in a mix of Mech E., Elec E., and Controls she has decided to pursue AI/Machine Learning and programming experience at the University of Maryland's Master's program in Robotics Engineering.

### Project Overview and Description

This repo contains coursework for the ENPM808X Midterm project for Fall 2021.
ACME Robotics has reached out in regards to needing a new module for their robots. The module that is implemented in this project is a perception module for human detection and tracking. This can be used on any of the ACME robots that work alongside humans and can be added with a front-facing camera. Essentially, the robot working in the dynamic environment can detect if a human is in its path and can alter its path or stop if necessary to avoid any possible accidents and collisions. The program can be broken down into a few main features: dataset preparation for the neural network, position estimation of humans, human detection, abd  distance calculation of the human from the robot. The program has to scale all the images to the proper dimensions needed for the neural network input, which is 416x416 pixels. The pre-trained neural network from YOLOv4 already has a set of weights that has been configured so we don't need to create a network from scratch. Then, the robot frame has to be transformed into the camera and world frame, so that the robot can calculate the position of the human in the correct frame and calculate the distance of how far away the human is (or if there is multiple humans, then the one closest to the robot).

For each image in the dataset, each image with a human/(s) has a label with the top-left and bottom-right coordinate for a box to correspond to the detected human. The detection structure stores these coordinates and also the width and height of the box.  The Position Estimator has a probability threshold for classificaiton to determine if a human is detected or not, a rough estimate of the average human height, a transformation of the camera frame to the robot frame, and an estimate of the xyz position of the human (or a vector containing multiple humans if there is more than 1 in an image). The Vision API wraps up the human detector and the position estimator into a stack that runs the whole program nicely. The neural network runs off of the CPU backend, so it runs relatively fast with a decent computer processor. GPU Acceleration with CUDA is not enabled so the program won't be as fast in performance, since not everyone has a NVIDIA GPU. The main functionality of the program when running is that it reads in an image from the dataset, runs the stack, and prints out if a human was detected, the human's x, y, z position, and the distance of how far away the human was. The distance is read into a range of thresholds where the robot action will be determined if the human then the robot will stop, or else the robot will continue or alter its path accordingly. 

### Midterm Phase 2 Deliverables

- The most recent activity diagram and UML can be found in the [visual reps](/visual_reps) folder while the original UML can be found in the [Original UML](/original_UML) folder.
- Agile Iterative Process (AIP): Please see this link to find our [AIP implementation document](https://docs.google.com/spreadsheets/d/1gBVo8C_xLlcH5OcivV810-puy338YpDrUkYAftgQPH4/edit?usp=sharing).

### Required Libraries and Software

  1. **C++ Version C++14**. This program requires C++14.
  2. **OpenCV**. Please install the OpenCV package using the following link: [OpenCV Installation](https://docs.opencv.org/3.4.15/d7/d9f/tutorial_linux_install.html)
  3. **Boost/filesystem**. Please install the boost library if not already installed. [Boost installation](https://stackoverflow.com/questions/12578499/how-to-install-boost-on-ubuntu)
  4. **Eigen**. This library should already be installed on a standard linux system.
  5. **math**. This library should already be installed on a standard linux system.
  6. **C++ std libs**. This library is certainly installed on a standard linux system.
  7. **CMake**. This software should already be installed on a standard linux system.
  8. **YOLOv4**. Please download the weights file from the link [weights] (https://drive.google.com/file/d/125kKy-FkMWs8C2s9kK0rVBYtv7kOsNwq/view?usp=sharing) and place in the /robot_params directory. This file is too large to place on github.

### Running the code
To run the code, open a terminal and follow these steps:

1. Clone the repo.

  FOR HTTPS CLONES:

```bash
git clone https://github.com/dlerner97/ACME_perception_proposal.git
```

  FOR SSH CLONES:

```bash
git clone git@github.com:dlerner97/ACME_perception_proposal.git
```

2. Download the [yolov4.weights](https://drive.google.com/file/d/125kKy-FkMWs8C2s9kK0rVBYtv7kOsNwq/view?usp=sharing) file and store it int the ACME_perception_proposal/robot_params directory.

3. Build the repo.

```bash
cd <absolute path>/ACME_perception_proposal
mkdir build && cd build
cmake ..
make
```

4. To run the main script,

```bash
./app/shell-app
```

5. To run the tests,

```bash
./test/cpp-test
```

### Doxygen Documentation Generation
The documentation is already pre-generated in the docs(/docs) folder however if for some reason the files cannot be previewed, then you can generate it as seen below.
```bash
cd <absolute path>/ACME_perception_proposal/docs
doxygen Doxyfile
```
To view the documentation, navigate to /html/index.html and open it in a browser. From there, you can navigate to Classes > Class List and click on any respective class for its documentation for each method.

### Code Check Results
[Code Coverage results](/code-check-results/code_coverage.txt)

[Cppcheck results](/code-check-results/cppcheck.txt)

[Cpplint results](/code-check-results/cpplint.txt)

[Unit Test results](/code-check-results/unit_tests.txt)

[Valgrind results](/code-check-results/valgrind.txt)

### Visual Representations of Code

The following Activity Diagram and UML's are jpg files and will not work well with zoom. See the [visual representation pdf](/visual_reps/activity_and_UML.drawio.pdf) for a higher quality image.

#### Activity Diagram

![Original activity diagram of the perception stack.](/visual_reps/activity_diagram.jpg?raw=true "Activity Diagram")

#### UML

![Original UML of the perception stack.](/visual_reps/UML.jpg?raw=true "UML")

Note that the LabelParser is not in the UML. This is because it is only used within the testing app. It is not a part of the main code base.

### Unit Tests

There are 3 testing suites in our codebase:

1. HumanDetectorTests: tests each individual method as well as construction of a given Human Detector instance with the proper inputs. 3 most important tests:
 - CorrectFrameSizeTest -> Applies a specific/unique width and height and tests if the prep_frame() method outputs an image of that size.
 - HumanDetectionAccuracyTest -> Runs through 50 labeled images and compares the detect() method with the true outputs. Tests accuracy by looking at the number of detections then also tests the accuracy of the x, y, width, and height that it outpus.
 - NoDetectionsPresentTest -> Runs through 50 images with no humans in sight and measures accuracy by counting the number of images a human was not detected.
2. PositionEstimatorTests: tests each individual method as well as construction of a given Position Estimator instance with the proper inputs. 2 most important tests:
 - ApproximateZTest -> Takes Detection and robot_params input and returns the estimated "z" in the camera frame. We compare this value with the result of a by-hand calculation.
 - EstimateAllXYZTest -> Similarly, this test takes multiple detections and a robot_params input and returns all estimated xyz positions of any detections. These are once again compared to a by-hand calculation.
3. ParamParserTest: Tests the robustness of the robot ParamParser class. Most important tests:
 - VariousInputsTest -> Tests valid and invalid inputs to the robot_params text file.

Given more time, we would have liked to test the full stack and take an image with a person at a known xyz distance from the camera. This would allow us to test the accuracy of the whole system. However, since each individual section contains a unit test, our code coverage is technically 100%. Note that the LabelParser class is not included in the test coverage include. This is because the class is only used within the testing suite (i.e. to parse the labels for images). Therefore, it does not need to be tested.

### Input Robot Parameters

Since our vision system is hardware agnostic, one must simply edit the [robot_params](/robot_params/robot_params.txt) text file to input their respective robot parameters. The robot parameters include: 
- Partial transform (in x, y, z, pitch) between the robot's center of mass (or any other desired model center). 
- Average height of humans in order to estimate the z-location of a detected human. [Source](https://www.worlddata.info/average-bodyheight.php).
- The probability threshold for classification. Any image with a probability threshold less than this value will be considered noise and subsequently discarded. If the probability is larger than the threshold we will consider there to be a human in sight.
- The non-max suppression threshold is used for grouping almost identical detections of humans.
- Score threshold is also used in the detection.
- Image height and width. This parameter depends on the specific detection algorithm we will be using. 
- Low and high alert thresholds. The robot should have different reactions to humans at different distances. If the distance < high_alert, the robot should stop. If the the high_alert < distance < low_alert, the robot should plan new path and if the human is further than the low alert, we should ignore them until they come within the given distances.
- Camera focal length and pixel density are needed for position estimation. See Position Estimation Methods below.
    
Many of these parameters are arbitrary since we do not have a physical robot to test. However, some are carefully selected to provide a realistic system. For example, while the distances between the camera and robot center are selected at random, the pitch is 90 deg. This is because robot "x" generally corresponds to a camera's "z." Additionally, the proposal specifies that the camera is "front-facing" and therefore, we prevent any roll or yaw from occuring. We believe that this is realistic in the real world as well since cameras are nearly always horizontal and front facing. However, the pitch can still be selected in case the user would like to change this parameter. If changing, please remember that the value must be 90 + *desired pitch* to account for the change in coordinate system.

#### Visual of Camera Position

![Camera Position visual](/visual_reps/Physical_Robot.jpg?raw=true "Camera Position")

### Position Estimation Methods
In this section, we will briefly describe our world frame position estimation methods. We will start with a diagram and equations we used to derive the equations and will then solve one of the cases we used in our position estimation unit tests. Note that the actual code in the PositionEstimation class uses matrix multiplication to solve the camera to robot transform.

The pinhole model of a camera can be seen below and this simplification gives us the following derivations.

![Pinhole Model](/visual_reps/position_estimation-CDE.drawio.png?raw=true "Pinhole Model") 
---
<img src="/visual_reps/LaTex_Imgs/deriving_camera_z_eq0.png" width="200">
<img src="/visual_reps/LaTex_Imgs/deriving_camera_z_eq.png" width="600">
<img src="/visual_reps/LaTex_Imgs/deriving_camera_xy.png" width="800">
---

We will now use these derivation to solve one of the unit test scenarios.

![Unit Test Scenario](/visual_reps/position_estimation-scenario.drawio.png?raw=true "Unit Test Scenario")
---
<img src="/visual_reps/LaTex_Imgs/z_camera.png" width="400">
<img src="/visual_reps/LaTex_Imgs/x_camera.png" width="600">
<img src="/visual_reps/LaTex_Imgs/y_robot.png" width="600">
<img src="/visual_reps/LaTex_Imgs/x_robot.png" width="300">
<img src="/visual_reps/LaTex_Imgs/z_robot.png" width="300">
---

### Citations
1. [YOLOv4](https://github.com/AlexeyAB/darknet)
2. [YOLO Object Detection Example](https://learnopencv.com/deep-learning-based-object-detection-using-yolov3-with-opencv-python-c/#disqus_thread)
3. [Stack Overflow iterate over string](https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string)
4. [Stack Overflow string ends with function](https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c)
