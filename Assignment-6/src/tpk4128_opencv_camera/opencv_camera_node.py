import rclpy
import numpy
from rclpy.node import Node
from sensor_msgs.msg import Image
import cv_bridge as cvb
import cv2 as cv

class OpenCVCameraNode(Node):
    def __init__(self):
        super().__init__('opencv_camera_controller')
        self._pub = self.create_publisher(Image, 'image', 10)
        self.bridge = cvb.CvBridge()
        self._camera = cv.VideoCapture(0)
        self.timer = self.create_timer(1/10, self._callback)

        if not self._camera.isOpened():
            print("Cannot open camera")
            exit()
    
    def _callback(self):
        ret, frame = self._camera.read()
    
        if not ret:
            print("Cannot receive frame...")
            exit()

        try:
            self._pub.publish(self.bridge.cv2_to_imgmsg(frame, "bgr8"))
        except cvb.CvBridgeError as e:
            print(e)

def main(args=None):
    rclpy.init(args=args)

    opencv_camera_node = OpenCVCameraNode()
    rclpy.spin(opencv_camera_node)

    opencv_camera_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
