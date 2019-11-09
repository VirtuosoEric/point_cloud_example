#!/usr/bin/env python
import rospy
import struct

from sensor_msgs import point_cloud2
from sensor_msgs.msg import PointCloud2, PointField
from std_msgs.msg import Header


def read_cloud_msg(msg):
    for p in point_cloud2.read_points(msg, field_names = ("x", "y", "z","rgba","my_new_value"), skip_nans=True):
        print " x : %f  y: %f  z: %f rgba:%f my_value:%f" %(p[0],p[1],p[2],p[3],p[4])




if __name__ == '__main__':
    rospy.init_node('read_cloud')
    rospy.Subscriber("my_point",PointCloud2,read_cloud_msg)
    rospy.spin()
