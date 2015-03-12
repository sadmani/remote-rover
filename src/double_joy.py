#!/usr/bin/env python
import roslib 
import rospy
from std_msgs.msg import Float64
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist,Vector3
from math import sqrt

output = Joy()
mvt = Twist()
prev_mvt = Twist()
lin_vel = Vector3()
prev_lin_vel = Vector3()

prev_lin_vel.x = 0
prev_lin_vel.y = 0
prev_lin_vel.z = 0
prev_wz = 0

prev_mvt = Twist(prev_lin_vel,Vector3(0,0,prev_wz))


def joy_buffer(data):
	#print(prev_mvt)
	pubBuffJoy = rospy.Publisher('buffered_joy',Joy)
	buff_data = data

	pubBuffJoy.publish(buff_data)
	rospy.Rate(20)


def send_mvt(data):
	pubBuffTwist = rospy.Publisher('buffered_twist',Twist)
	
	global prev_lin_vel
	global prev_wz
	global prev_mvt
	
	lin_vel.x = data.axes[0]
	lin_vel.y = data.axes[1]
	lin_vel.z = 0

	if lin_vel.x != 0 and lin_vel.y != 0:
		wz = 1
	else:
		wz = 0

	mvt = Twist(lin_vel,Vector3(0,0,wz))
	#print('mvt twist: ', mvt)

	if prev_mvt != mvt:
		twist_to_send = mvt
		pubBuffTwist.publish(twist_to_send)
	
	#prev_mvt = mvt
	prev_lin_vel.x = lin_vel.x
	prev_lin_vel.y = lin_vel.y
	prev_wz = wz

#	prev_mvt = Twist(prev_lin_vel,Vector3(0,0,wz))

#	pubBuffTwist.publish(twist_to_send)

#	pubBuffTwist.publish(mvt)
	rospy.Rate(20)


def raw_joy_listener():
	rospy.init_node('raw_joy_listener', anonymous = True)
	rospy.Subscriber("joy",Joy,joy_buffer)
	rospy.Subscriber("buffered_joy",Joy,send_mvt)
	rospy.spin()

if __name__ == '__main__':
	try:
		raw_joy_listener()
	except rospy.ROSInterruptException: 
		pass