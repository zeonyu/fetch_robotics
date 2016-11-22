#include "ros/ros.h"
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "ros_infiniTAM/req_im.h"
bool getImage(ros_infiniTAM::req_im::Request  &req,
         ros_infiniTAM::req_im::Response &res)
{
  if (res.isok == 1)
  {

  }
  return true;
}

void callback( const sensor_msgs::ImageConstPtr& msg_rgb , const sensor_msgs::ImageConstPtr& msg_depth )
{
    cv_bridge::CvImagePtr img_ptr_rgb;
    cv_bridge::CvImagePtr img_ptr_depth;
 //       ROS_INFO("orgin depth image_type is = %s", msg_depth->encoding.c_str() );
    try{
        img_ptr_depth = cv_bridge::toCvCopy(*msg_depth, sensor_msgs::image_encodings::TYPE_32FC1);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception:  %s", e.what());
        return;
    }
   //     ROS_INFO("new depth image_type is = %s", img_ptr_depth->encoding.c_str() );
    try{
        img_ptr_rgb = cv_bridge::toCvCopy(*msg_rgb, sensor_msgs::image_encodings::TYPE_8UC3);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception:  %s", e.what());
        return;
    }

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "send_image_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("send_image_server", getImage);

  ros::spin();

  return 0;
}
