#include "demo1_one_desk_several_poses/fetch_action_server.h"
// #include "demo1_one_desk_several_poses/misc.hpp"

FetchAction::FetchAction(std::string name):
        as_(nh_,name,boost::bind(&FetchAction::executeCB,this,_1),false),
        action_name_(name),
        base_ac("move_base", true)
{
    as_.start();
    spinner=new ros::AsyncSpinner(1);
  //  moveit::planning_interface::MoveGroup::Options option("arm_with_torso","base_link",nh_);
    group=new moveit::planning_interface::MoveGroup("arm_with_torso");
    //zeon
    group->setPoseReferenceFrame("map");
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
    while(!base_ac.waitForServer(ros::Duration())){
      ROS_INFO("Waiting for the move_base action server to come up");
    }
     ROS_INFO(" Connected");
}

void FetchAction::executeCB(const demo1_one_desk_several_poses::ros_goalGoalConstPtr &goal){
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
    this->target_pose.position.x=position[0];
    this->target_pose.position.y=position[1];
    this->target_pose.position.z=position[2];//0.8
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
    this->base_goal.target_pose.header.frame_id = "map"; // base_link odom
    this->base_goal.target_pose.header.stamp = ros::Time::now();
    this->base_goal.target_pose.pose.position.x = this->target_pose.position.x-0.5;
    this->base_goal.target_pose.pose.position.y = this->target_pose.position.y-0.2;
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

void FetchAction::moveForwardOneMeter(){
    ROS_INFO(" Executing, get reach point ");
    demo1_one_desk_several_poses::ros_goalGoal goal;
    goal.position.push_back(1.0);//x
    goal.position.push_back(0.0);//y
    goal.position.push_back(0.8);//z
    
    bool isok = true;
   if(as_.isPreemptRequested() || !ros::ok())
   {
       ROS_INFO("%s, Preempted",action_name_.c_str());
       as_.setPreempted();
       isok = false;
   }
    if (isok)
    {
        SetTagetPose(goal.position);
        this->success = go_to_pose();
        ROS_INFO("%s\n", this->success ? "go_to_pose success" : "go_to_pose failed");
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

// 由欧拉角创建四元数
void FetchAction::angle2quat(std::vector<float> &angle, std::vector<float> &quaternion)
{
    cout << endl
         << "start transfering" << endl;
    float cx = cos(angle[0] / 2);
    float sx = sin(angle[0] / 2);
    float cy = cos(angle[1] / 2);
    float sy = sin(angle[1] / 2);
    float cz = cos(angle[2] / 2);
    float sz = sin(angle[2] / 2);

    cout << cx << " " << sx << " " << cy << " " << sy << " " << cz << " " << sz << endl;

    quaternion[0] = sx * cy * cz - cx * sy * sz; // x
    quaternion[1] = cx * sy * cz + sx * cy * sz; // y
    quaternion[2] = cx * cy * sz - sx * sy * cz; // z
    quaternion[3] = cx * cy * cz + sx * sy * sz; // w
                                                 //  quaternion.push_back(cx*cy*cz + sx*sy*sz);// w
    cout << quaternion[0] << " " << quaternion[1] << " " << quaternion[2] << " " << quaternion[3] << endl;

    cout << endl
         << "end of transfering" << endl;
};
