#ifndef _FETCH_CLIENT_HPP_
#define _FETCH_CLIENT_HPP_
#include <iostream>
#include <vector>
#include <Eigen/core>

#include <tf/transform_listener.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <ros_infiniTAM/GotoPoseAction.h>

class fetch_client
{
public:
    enum Proc_state{CHOSE,DECIDE};
    enum Move_state{WAIT_FOR_GOAL,GOAL_REACHED};
private:
    Proc_state ps;
    Move_state ms;
    Eigen::vector3d position;
    Eigen::vector4d orientation;
    tf::StampedTransform kinect2map;
    tf::StampedTransform optical2map;
    bool image_updated;
    ros::Time goal_completion_time;
    tf::TransformListener listenner;
    int step_cntr;
    ros::NodeHandle nh_;
    ros::NodeHandle private_nh_;
    actionlib::SimpleActionClient<ros_infiniTAM::GotoPoseAction> ac_;
protected:
    virtual ros::NodeHandle& getNodeHandle() {return nh_;}
    virtual ros::NodeHandle& getPrivateNodeHandle(){return private_nh_;}
public:
    fetch_client(ros::NodeHandle & nh);
    ~fetch_client();
    void fetch_client_init();
    void send_goal(const Eigen::Vector3d & goal_postion, const Eigen::Vector4d & goal_orientation);
    void activeCb(){
        ROS_INFO("Goal just went active");
    }
    void doneCb(const actionlib::SimpleClientGoalState&state, const ros_infiniTAM::GoToPoseResutlConstPtr & result);
private:
    bool process_goal(Eigen::Vector3d & proc_position, Eigen::Vector4d & proc_orientation, Eigen::Vector3d &goal_position, Eigen::Vector4d &goal_orientation);

}
