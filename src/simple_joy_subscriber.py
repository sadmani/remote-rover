#!/usr/bin/env python
import roslib 
import rospy
from std_msgs.msg import Float64
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist,Vector3
from math import sqrt

output = Joy()
mvt = Twist()
lin_vel = Vector3()

def callback(data):
	# pubPWM = rospy.Publisher('mvt_PWM',Float64)
	# pubDir = rospy.Publisher('mvt_direction',Float64)
	pubTwist = rospy.Publisher('twist_rover',Twist)
	# lr_msg = data.axes[0]
	# fb_msg = data.axes[1]

	lin_vel.x = data.axes[1]
	lin_vel.y = data.axes[0]
	lin_vel.z = 0

	if lin_vel.x != 0 and lin_vel.y != 0:
		wz = 1
	else:
		wz = 0

	mvt = Twist(lin_vel,Vector3(0,0,wz))
	#print('mvt twist: ', mvt)
	pubTwist.publish(mvt)

def listener():
	rospy.init_node('listener', anonymous = True)
	rospy.Subscriber("joy",Joy,callback)
	rospy.spin()

if __name__ == '__main__':
	try:
#		talker()
		listener()
	except rospy.ROSInterruptException: 
		pass