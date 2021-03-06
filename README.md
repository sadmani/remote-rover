#Overview:

The goal of this project is to a control an Arduino-based rover through an obstacle course with ROS by user input (Leap Motion, Joystick, keyboard, etc.) remotely by using robot web tools.

There are a few different milestones for this project:

1. Setting up Arduino and ROS communication through rosserial
2. Controlling the rover through keyboard input
3. Creating a rover teleop package
4. Getting onboard webcam video onto user's screen
5. Interfacing with robot web tools

#Usage:
##Hardware:
Note: this program is based on the use of the [Linksprite WiFi rover] (http://www.linksprite.com/wp-content/uploads/2015/02/rover-assembling-instruction.pdf). After obtaining and building it, procede with the following instructions:

1. Have your xbees hooked up to the host computer and the rover, configured with a baud rate equal to 57600
2. Turn the rover on
3. Connect to the wifi module 'wifi-robots'

##Sofware:

###Dependencies:

There are a few packages that you need to install if you want to use this package:

* Rosserial- for communication with Arduino:
```
sudo apt-get install ros-indigo-rosserial-arduino
sudo apt-get install ros-indigo-rosserial
```
* Joy- for interfacing with PS3 controller:
```
sudo apt-get install joy
```
* OpenCV- to capture video from the rover's webcam:
```
sudo apt-get install opencv
```
* Image Transport- to convert the video format to one that can be streamed using web video server as well:
```
sudo apt-get install image-transport
```
The following are needed for Robot Web Tools use:

* Rosbridge Server
```
sudo apt-get install ros-indigo-rosbridge-server
```
* Rosbridge Suite
```
sudo apt-get install ros-indigo-rosbridge-suite
```
* Web Republisher

```
sudo apt-get install ros-indigo-tf2-web-republisher
```
###Launch File:
Use the launch file that is included (rover.launch)--> This can be used to control the rover simply with a PS3 joystick. *Note: within this file, you should modify the port that your Arduino is hooked up to (mine alternates between ACM0 and ACM1).

The online-control is currently in progress, but if you'd like to see:

Use the launch file above and the type the following command:
```
roslaunch rosbridge_server rosbridge_websocket.launch
```
Click on the html file to see the current code that publishes a twist to move the rover

#Next Steps:
I am in the process of refining this package as well as moving forward with the development of the robot web tools portion. Stay tuned!!!
