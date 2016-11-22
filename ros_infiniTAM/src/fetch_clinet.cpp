#include "fetch_clent.h"
#include <ros/package.h>

fetch_client::fetch_client( ros::NodeHandle & nh )
        : ps( CHOOSE ), ms( GOAL_REACHED ),
          image_updated(false), goal_completion_time( ros::Time::now() ),
          listener( ros::Duration(60.0) ),		// tf cache length in sec
          step_cntr(0), nh_(nh), private_nh_("~"), ac_("go_to_pose_act", true)
{
        srand((unsigned)time(NULL));
}
void fetch_client::fetch_client_init()
{
        cloud_sub = nh_.subscribe( "/arm_kinect/arm_kinect/depth/points", 1, &fetch_client::GoalCallback, this);

        // wait for the action server to start
        ROS_INFO("Waiting for action server to start.");
        ac_.waitForServer(); //will wait for infinite time
        ROS_INFO("Action server started!");
}
