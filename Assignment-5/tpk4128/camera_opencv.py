import numpy as np
import cv2 as cv


class Camera(object):

    def __init__(self):

        # Implement this constructor that opens a webcam and stores it in self._camera
        self._camera = cv.VideoCapture(0)

        if not self._camera.isOpened():
            print("Cannot open camera")
            exit()

    def capture(self):

        # Capture frame-by-frame
        ret, frame = self._camera.read()

        if not ret:
            print("Cannot receive frame...")
            exit()

        return frame 


    def __del__(self):
        self._camera.release()
        cv.destroyAllWindows()
"""
cam = Camera()

img = cam.capture()

print(img.dtype, img.shape, len(img.tostring()))


while True:
    gray = cv.cvtColor(cam.capture(), cv.COLOR_BGR2GRAY)

    cv.imshow('frame', gray)

    if cv.waitKey(1) == ord('q'):
        break
"""