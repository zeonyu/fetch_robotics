#include<ros/ros.h>
#include<actionlib/server/simple_action_server.h>
#include<ros_infiniTAM/ros_goalAction.h>
#include <geometry_msgs/Pose.h>

// MoveIt!
#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

//
#include <move_base/move_base.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
//
class FetchAction
{
protected:
    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<ros_infiniTAM::ros_goalAction> as_;
    MoveBaseClient base_ac;
    move_base_msgs::MoveBaseGoal base_goal;
    std::string action_name_;
    ros_infiniTAM::ros_goalFeedback feedback_;
    ros_infiniTAM::ros_goalResult result_;
    ros::AsyncSpinner *spinner;
    ros::Publisher display_publisher;
    moveit_msgs::DisplayTrajectory display_trajectory;
    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
    geometry_msgs::Pose target_pose;
    moveit::planning_interface::MoveGroup *group;
    bool success;
    bool needMoveBase;
public:
    FetchAction(std::string name);
    ~FetchAction();
    void init();
    void executeCB(const ros_infiniTAM::ros_goalGoalConstPtr &goal);
    void SetTagetPose(std::vector<float> position);
    float computeCompleteness();
    void setBaseGoalFromTargetPose();
    bool go_to_pose();
    bool move_arm_to_goal();
    bool move_base_to_goal();
};
