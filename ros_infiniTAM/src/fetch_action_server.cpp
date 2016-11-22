#include "ros_infiniTAM/fetch_action_server.h"

FetchAction::FetchAction(std::string name):
        as_(nh_,name,boost::bind(&FetchAction::executeCB,this,_1),false),
        action_name_(name),base_ac("move_base", true)
{
    as_.start();
    spinner=new ros::AsyncSpinner(1);
  //  moveit::planning_interface::MoveGroup::Options option("arm_with_torso","base_link",nh_);
    group=new moveit::planning_interface::MoveGroup("arm_with_torso");
   // planning_scene_interface=new moveit::planning_interface::PlanningSceneInterface ("base_link");
    success=true;
    needMoveBase=false;
}
FetchAction::~FetchAction(){

}
void FetchAction::init()
{
    this->spinner->start();
    this->display_publisher = nh_.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);
    while(!base_ac.waitForServer(ros::Duration(5.0))){
      ROS_INFO("Waiting for the move_base action server to come up");
    }
}
void FetchAction::executeCB(const ros_infiniTAM::ros_goalGoalConstPtr &goal){
    //ROS_INFO("%s: Executing, get reach point %f", action_name_.c_str(), goal.position[1]);
    bool isok=true;
    if(as_.isPreemptRequested() || !ros::ok())
    {
        ROS_INFO("%s: Preempted",action_name_.c_str());
        as_.setPreempted();
        isok=false;
    }
    if (isok)
    {
        SetTagetPose(goal->position);
        this->success=go_to_pose();
    }
    if (this->success)
    {
        //need to do compare the completeness
        feedback_.completeness=computeCompleteness();
        result_.success=true;
        as_.publishFeedback(feedback_);
        ROS_INFO("%s: Succeeded",action_name_.c_str());
        as_.setSucceeded(result_);
    } else
    {
         result_.success=false;
         ROS_INFO("%s: failed: ",action_name_.c_str());
    }

}
float FetchAction::computeCompleteness(){
    return 0.6;
}
void FetchAction::SetTagetPose(std::vector<float> position){
    this->target_pose.orientation.w = 1.0;
    this->target_pose.position.x=position[1];
    this->target_pose.position.y=position[2];
    this->target_pose.position.z=0.8;
}
bool FetchAction::move_arm_to_goal(){
    group->setPoseTarget(this->target_pose);
    bool success=group->move();
    return success;
}
bool FetchAction::move_base_to_goal(){
    base_ac.sendGoal(this->base_goal);
    base_ac.waitForResult();
    bool success;
    if(base_ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      success=true;
    else
      success=false;
}
void FetchAction::setBaseGoalFromTargetPose(){
    this->base_goal.target_pose.header.frame_id = "base_link";
    this->base_goal.target_pose.header.stamp = ros::Time::now();
    this->base_goal.target_pose.pose.position.x = this->target_pose.position.x;
    this->base_goal.target_pose.pose.position.y = this->target_pose.position.y;
    this->base_goal.target_pose.pose.orientation.w = 1.0;
}

bool FetchAction::go_to_pose(){
    bool success=move_arm_to_goal();
    if (success)
        needMoveBase=false;
    else
        needMoveBase=true;
    if (needMoveBase){
        setBaseGoalFromTargetPose();
        bool move_base_success=move_base_to_goal();
        if (move_base_success)
           success=move_arm_to_goal();
        else
            ROS_INFO("The base failed to move for some reason");
    }
//    if (~success)
//        ROS_INFO("Failed to move to target pose");

    return success;
}

