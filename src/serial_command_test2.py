#!/usr/bin/env python
import roslib; 
import rospy
from std_msgs.msg import Float64

def talker():
	pubHL = rospy.Publisher('led_chat', Float64)
	pubLR = rospy.Publisher('servoLR_chat', Float64)
	pubUD = rospy.Publisher('servoUD_chat', Float64)
	pubMS = rospy.Publisher('move_chat', Float64)
	rospy.init_node('serial_command_test2')
	while not rospy.is_shutdown():
		headlights = input('Please enter a 7 to turn the lights on and 9 to turn them off: ')
		#headlights = input()
		pubHL.publish(headlights)
		servolr = input('Please type 1 to move camera left and 3 to move it right')
		pubLR.publish(servolr)
		servoud = input('Please type 2 to move camera up and 0 to move it down')
		pubUD.publish(servoud)
		move = input('Please type 4 to move left, 6 to move right, 8 to move forward, and 5 to move back')
		pubMS.publish(move)
		rospy.sleep(1.0)

if __name__ == '__main__':
	try:
		talker()
	except rospy.ROSInterruptException: 
		pass