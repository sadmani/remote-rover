#!/usr/bin/env python
import roslib 
import rospy
from geometry_msgs.msg import Twist,Vector3
from sensor_msgs.msg import Joy

#cam_mvt.py: subscribes to the joy topic of the joy_node and publishes values to 


cam_cont = Twist()
cam_mvtUD = Vector3()
cam_mvtLR = Vector3()

def cam_control(data):
	#Using a twist to send a message through rosserial to Arduino right now
	#because I could not figure out how to send an array of values over- once
	#I figure that out, I'll edit this portion of the code

	pubCamMvt = rospy.Publisher('cam_mvt',Twist)

	#The below four buttons will be used to control the servos that the webcam
	#sits on 
	##Move camera up
	cam_mvtUD.y = data.buttons[4]
	##Move camera down
	cam_mvtUD.x = data.buttons[6]
	##Move camera right
	cam_mvtLR.y = data.buttons[5]
	##Move camera left
	cam_mvtLR.x = data.buttons[7]

	cam_mvtUD.z = 0
	cam_mvtLR.z = 0

	cam_cont = Twist(cam_mvtUD,cam_mvtLR)

	pubCamMvt.publish(cam_cont)

	rospy.Rate(20)


def raw_joy_listener():
	rospy.init_node('cam_control_joy', anonymous = True)
	rospy.Subscriber("joy",Joy,cam_control)
	rospy.spin()

if __name__ == '__main__':
	try:
		raw_joy_listener()
	except rospy.ROSInterruptException: 
		pass		