#!/usr/bin/env python

import roslib
import rospy
import cv2
from cv2 import *
import urllib
import numpy as np
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

#ros_opencv_webcam: when the host computer is connected to the wifi module on
#the rover, this script will capture images from the webcam on the rover and
#stream it to a rostopic using opencv. The purpose of this piece of code is to
#see the world through the rover's "eyes"

##Note: I found out how to do a lot of this through a few stackexchange.com
##questions that were asked previously

def wifi_camera():
	#Create a publisher for the images
	pub = rospy.Publisher('/camera/image_raw',Image)
	#Initialize the node
	rospy.init_node('wifi_camera',anonymous=True)
	#Open the mjpeg stream using the below line; this address was found when I
	#went through the Windows GUI that was developed by the company who built
	#the rover. Originally, it was written to show snapshots, but I edited so
	#it produces a video stream instead
	cam = cv2.VideoCapture("http://192.168.1.1:8080/?action=stream&amp;type=.mjpg")
	print cam.isOpened()
	bridge = CvBridge()
	while(True):
	        ret, frame = cam.read()
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