#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud2_iterator.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "point_clould_pub");
    ros::NodeHandle n;
    ros::Publisher point_pub = n.advertise<sensor_msgs::PointCloud2>("point_cloud", 5);

    using namespace sensor_msgs;
    PointCloud2Ptr points_msg = boost::make_shared<PointCloud2>();
    points_msg->header.frame_id = "map";
    points_msg->height = 1;
    points_msg->width = 10;
    points_msg->is_bigendian = false;
    points_msg->is_dense = false;
    sensor_msgs::PointCloud2Modifier pcd_modifier(*points_msg);
    // pcd_modifier.setPointCloud2FieldsByString(3, "xyz", "rgb","ring");
    pcd_modifier.setPointCloud2Fields(5,"x",1,sensor_msgs::PointField::FLOAT32,
    "y",1,sensor_msgs::PointField::FLOAT32,
    "z",1,sensor_msgs::PointField::FLOAT32,
    "intensity",1,sensor_msgs::PointField::INT16,
    "ring",1,sensor_msgs::PointField::INT16);

    sensor_msgs::PointCloud2Iterator<float> iter_x(*points_msg, "x");
    sensor_msgs::PointCloud2Iterator<float> iter_y(*points_msg, "y");
    sensor_msgs::PointCloud2Iterator<float> iter_z(*points_msg, "z");
    sensor_msgs::PointCloud2Iterator<uint8_t> iter_intensity(*points_msg, "intensity");
    sensor_msgs::PointCloud2Iterator<uint8_t> iter_ring(*points_msg, "ring");

    for (int i = 0; i < 10; i++)
    {
        *iter_x = i;
        *iter_y = i;
        *iter_z = i;
        *iter_intensity = i;
        *iter_ring = i;

        ++iter_x;
        ++iter_y;
        ++iter_z;
        ++iter_intensity;
        ++iter_ring;
    }

    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        point_pub.publish(points_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}