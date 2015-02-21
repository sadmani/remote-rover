import cv2
from cv2 import *
import urllib
import numpy as np

cam = cv2.VideoCapture("http://192.168.1.1:8080/?action=stream&amp;type=.mjpg")
print cam.isOpened()

while(True):
        ret, frame = cam.read()
        cv2.imshow('frame', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

cam.release()
cv2.destroyAllWindows()