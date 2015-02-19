#!/usr/bin/env python
import roslib 
import rospy
from std_msgs.msg import Float64
from sensor_msgs.msg import Joy
output = Joy()


def callback(data):
#	rospy.loginfo(rospy.get_caller_id() + "I heard the info")
	pubJoy = rospy.Publisher('joy_control',Float64)
	
	fr_msg = data.axes[1]
#	forward = data.axes[0]
#	backward = data.axes[1]
#	pubJoy.publish(fr_msg)
	if fr_msg > 0:
		forward = fr_msg*255
		pubJoy.publish(forward)
	if fr_msg < 0:
		backward = fr_msg*-255
		pubJoy.publish(backward)
	#print("Data axes 0: ",output1)
	#print("Data axes 1: ",output2)

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