// Copyright 2014-2015 Isis Innovation Limited and the authors of InfiniTAM

#include <cstdlib>
// #include <iostream>
// #include <vector>
// using namespace std;

#include "Engine/UIEngine.h"
#include "Engine/ImageSourceEngine.h"
#include "Engine/RosEngine.h"
#include "Engine/OpenNIEngine.h"
#include "Engine/Kinect2Engine.h"
#include "Engine/LibUVCEngine.h"
#include "Engine/RealSenseEngine.h"
#include "demo1_one_desk_several_poses/fetch_action_server.h"
// using namespace InfiniTAM::Engine;


int main(int argc, char **argv) 
try
{
    ros::init(argc, argv, "Demo1_one_desk_several_poses");
    /* -------------------------------------------------------------------
    FetchServer已经包含了MoveBaseClient和Moveit，其中MoveBaseServer已经默认启动了，Moveit使用的是MoveGroup和PlanningSceneInterface来控制，在class FetchServer中也已经启动了。也就是说，我们仅仅需要启动MoveBaseClient和MoveGroup就已经足够。
    ------------------------------------------------------------------- */
    // start FetchAction server and client
    // ros::NodeHandle n;
    FetchAction fetch_server("go_to_pos");
    fetch_server.init();
    printf("initialising fetch server ...\n");
    actionlib::SimpleActionClient<demo1_one_desk_several_poses::ros_goalGoal> fetch_client;
    fetch_client.waitForServer();
    printf("initialising fetch client ...\n");
    // sending goals
    vector<demo1_one_desk_several_poses::ros_goalGoal> goals;
    // point1
    demo1_one_desk_several_poses::ros_goalGoal point1;
    float tmp_oritation[] = {0, 0, 1.57079};
    vector<float> angle1(tmp_oritation, tmp_oritation + 3);
    vector<float> quat1(4);
    fetch_server.angle2quat(angle1, quat1);
    cout << endl << "complete" << endl;
    // configure point1
    point1.target_pose.header.frame_id = "map";
    point1.target_pose.header.stamp = ros::Time::now();
    point1.target_pose.pose.position.x = 2.0;
    point1.target_pose.pose.position.y = 0.0;
    point1.target_pose.pose.position.z = 0.8;
    point1.target_pose.pose.orientation.x = quat1[0];
    point1.target_pose.pose.orientation.y = quat1[1];
    point1.target_pose.pose.orientation.z = quat1[2];
    point1.target_pose.pose.orientation.w = quat1[3];
    goals.push_back(point1);

    for (vector<move_base_msgs::MoveBaseGoal>::iterator ite = goals.begin(); ite != goals.end(); ite++)
    {
        ROS_INFO("Sending point");
        // fetch_server.base_ac.sendGoal(*ite);
        // fetch_server.base_ac.waitForResult();
        fetch_client.sendGoal(*ite);
        bool finished_before_timeout = fetch_client.waitForResult(ros::Duration(30.0));

        if(finished_before_timeout) {
            actionlib::SimpleClientGoalState state = fetch_client.getState();
            ROS_INFO("Action finished: %s", state.toString().c_str());
        }
        else 
            ROS_INFO("Action did not finished the time out.");

        ros::Duration(5.0).sleep();

        // if (fetch_server.base_ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        //     ROS_INFO("Hooray");
        // else
        //     ROS_INFO("failed for some reason");
    }

    return 0;
}
catch (std::exception &e)
{
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
}
