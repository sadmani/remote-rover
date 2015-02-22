#!/usr/bin/env python
import roslib
import rospy
import cv2
from cv2 import *
import urllib
import numpy as np
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

def wifi_camera():
	pub = rospy.Publisher('robot_vision',Image)
	rospy.init_node('wifi_camera',anonymous=True)
	cam = cv2.VideoCapture("http://192.168.1.1:8080/?action=stream&amp;type=.mjpg")
	print cam.isOpened()
	bridge = CvBridge()
	while(True):
	        ret, frame = cam.read()
	        #cv2.imshow('frame', frame)
	        image_message = bridge.cv2_to_imgmsg(frame,encoding="bgr8")
	        pub.publish(image_message)
	        if cv2.waitKey(1) & 0xFF == ord('q'):
	            break

	cam.release()
	cv2.destroyAllWindows()

if __name__ == '__main__':
	try:
		wifi_camera()
	except rospy.ROSInterruptException: 
		pass