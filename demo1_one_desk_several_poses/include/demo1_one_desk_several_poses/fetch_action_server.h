// Standard
#include <iostream>
#include <vector>
#include <Eigen/Core>

// ROS Stuff
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <demo1_one_desk_several_poses/ros_goalAction.h>
#include <geometry_msgs/Pose.h>

// MoveIt!
#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

// Move base
#include <move_base/move_base.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
using namespace std;

class FetchAction
{
  private:
    // Ros stuff
    ros::NodeHandle nh_;
    ros::AsyncSpinner *spinner;
    ros::Publisher display_publisher;
   // Actionlib server
    actionlib::SimpleActionServer<demo1_one_desk_several_poses::ros_goalAction> as_;
    std::string action_name_;
    demo1_one_desk_several_poses::ros_goalFeedback feedback_;
    demo1_one_desk_several_poses::ros_goalResult result_;
    // Move base 
    MoveBaseClient base_ac;
    move_base_msgs::MoveBaseGoal base_goal;
    // Moveit!
    moveit::planning_interface::MoveGroup *group;
    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
    geometry_msgs::Pose target_pose;
    moveit_msgs::DisplayTrajectory display_trajectory;
    // Move communication: base and arm
    bool success;
    bool needMoveBase;
    // Current sensor info
    // Eigen::Vector3d position;

  public:
    FetchAction(std::string name);
    ~FetchAction();
    void init();
    void executeCB(const demo1_one_desk_several_poses::ros_goalGoalConstPtr &goal);
    void SetTagetPose(std::vector<float> position);
    float computeCompleteness();
    void setBaseGoalFromTargetPose();
    bool go_to_pose();
    bool move_arm_to_goal();
    bool move_base_to_goal();
    void moveForwardOneMeter();
    void angle2quat(std::vector<float> &angle, std::vector<float> &quaternion);
};
