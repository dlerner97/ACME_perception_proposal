# ACME_perception_proposal

### Authors
- Dani Lerner (dlerner97)
- Diane Ngo (dngo13)

### Information
In this proposal, we will develop a human obstacle detection prototype for mobile robots.

This repo contains coursework for the ENPM808X Midterm project. 

### Required Libraries
  1. OpenCV. Please install the OpenCV package as follows: (OpenCV Installation)[https://docs.opencv.org/3.4.15/d7/d9f/tutorial_linux_install.html]

### Visual Representations of Code
The following Activity Diagram and UML's are jpg files and will not work well with zoom. See the [visual representation pdf](/visual_reps/activity_and_UML.drawio.pdf) for a higher quality image.

#### Activity Diagram
![Original activity diagram of the perception stack.](/visual_reps/activity_diagram.jpg?raw=true "Activity Diagram")

#### UML
![Original UML of the perception stack.](/visual_reps/UML.jpg?raw=true "UML")

### Deliverables
- QuadChart and Proposal is in Phase 0 folder
- Activity diagram and UML can be found in the visual reps folder.
- Presentation (Slides) link: https://docs.google.com/presentation/d/1rxVNtMLtl6_6DkGCbjWONe4ORViMRBE8y-tto7cjHgU/edit?usp=sharing
- Video link: https://drive.google.com/file/d/1ZpRo9nZlphS_IJwaAQhYeR1XUmBKe5Q5/view?usp=sharing

### Input Robot Parameters
Since our vision system is hardware agnostic, one must simply edit the [robot_params](/robot_params/robot_params.txt) text file to input their respective robot parameters. The robot parameters include: 
- Full transform (in x, y, z, pitch, yaw) between the robot's center of mass (or any other desired model center). 
- Average height of humans in order to estimate the z-location of a detected human. [Source](https://www.worlddata.info/average-bodyheight.php).
- The probability threshold for classification. Any image with a probability threshold less than this value will be considered noise and subsequently discarded. If the probability is larger than the threshold we will consider there to be a human in sight.
- Image height and width. This parameter depends on the specific detection algorithm we will be using. 
- Low and high alert thresholds. The robot should have different reactions to humans at different distances. If the distance < high_alert, the robot should stop. If the the high_alert < distance < low_alert, the robot should plan new path and if the human is further than the low alert, we should ignore them until they come within the given distances.
    
Many of these parameters are arbitrary since we do not have a physical robot to test. However, some are carefully selected to provide a realistic system. For example, while the distances between the camera and robot center are selected at random, the pitch is 90 deg. This is because robot "x" generally corresponds to a camera's "z." Additionally, the proposal specifies that the camera is "front-facing" and therefore, we prevent any roll or yaw from occuring. We believe that this is realistic in the real world as well since cameras are nearly always horizontal and front facing. However, the pitch can still be selected in case the user would like to change this parameter. If changing, please remember that the value must be 90 + *desired pitch* to account for the change in coordinate system.

#### Visual of Camera Position
![Camera Position visual](/visual_reps/Physical_Robot.jpg?raw=true "Camera Position")
