#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <vector>
using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

 // 由欧拉角创建四元数
  void angle2quat(vector<float>& angle, vector<float> &quaternion)
  {
    cout << endl << "start transfering" << endl;
   float cx = cos(angle[0]/2);
   float sx = sin(angle[0]/2);
   float cy = cos(angle[1]/2);
   float sy = sin(angle[1]/2);
   float cz = cos(angle[2]/2);
   float sz = sin(angle[2]/2);

   cout << cx << " " << sx << " " << cy << " " << sy << " " << cz << " " << sz << endl;

   quaternion[0] = sx*cy*cz - cx*sy*sz;// x 
   quaternion[1] = cx*sy*cz + sx*cy*sz;// y 
   quaternion[2] = cx*cy*sz - sx*sy*cz;// z
   quaternion[3] = cx*cy*cz + sx*sy*sz;// w
  //  quaternion.push_back(cx*cy*cz + sx*sy*sz);// w
   cout << quaternion[0] << " " << quaternion[1] << " " << quaternion[2] << " " << quaternion[3] << endl;

   cout << endl << "end of transfering" << endl;
  };
/*
int main() {
  int n[] = {0, 0, 1.57};
  vector<float> angle1(n, n+3);
  cout << angle1[0] << " " << angle1[1] << " " << angle1[2] << endl;
  vector<float> quat1(4);
  angle2quat(angle1, quat1);
  cout << quat1[0] << " " << quat1[1] << " " << quat1[2] << " " << quat1[3] << endl;
  cout << endl << "complete" << endl;
  return 0;
}
*/

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  // zeon: make a list of goals
  vector<move_base_msgs::MoveBaseGoal> goals;
  // point1 
  move_base_msgs::MoveBaseGoal point1;
  double n[] = {0, 0, 1.57079};
  vector<float> angle1(n, n+3);
  vector<float> quat1(4);
  angle2quat(angle1, quat1);
  for(vector<float>::iterator ite=quat1.begin(); ite != quat1.end(); ite++) {
    cout << *ite << " ";
    cout << endl;
  }
  cout << endl << "complete" << endl;
  point1.target_pose.header.frame_id = "map";
  point1.target_pose.header.stamp = ros::Time::now();
  point1.target_pose.pose.position.x = 2.0;
  point1.target_pose.pose.position.y = 0.0;
  point1.target_pose.pose.position.z = 0.0;
  point1.target_pose.pose.orientation.x = quat1[0];
  point1.target_pose.pose.orientation.y = quat1[1];
  point1.target_pose.pose.orientation.z = quat1[2];
  point1.target_pose.pose.orientation.w = quat1[3];
  goals.push_back(point1);
  // point2 
  /*
  move_base_msgs::MoveBaseGoal point2;
  point2.target_pose.header.frame_id = "map";
  point2.target_pose.header.stamp = ros::Time::now();
  point2.target_pose.pose.position.x = 3.0;
  point2.target_pose.pose.position.y = 1.0;
  point2.target_pose.pose.position.z = 0.0;
  point2.target_pose.pose.orientation.w = 1.0;
  goals.push_back(point2);
  // point3 
  move_base_msgs::MoveBaseGoal point3;
  point3.target_pose.header.frame_id = "map";
  point3.target_pose.header.stamp = ros::Time::now();
  point3.target_pose.pose.position.x =4.0;
  point3.target_pose.pose.position.y = 0.0;
  point3.target_pose.pose.position.z = 0.0;
  point3.target_pose.pose.orientation.w = 1.0;
  goals.push_back(point3);
  // point4
  move_base_msgs::MoveBaseGoal point4;
  point4.target_pose.header.frame_id = "map";
  point4.target_pose.header.stamp = ros::Time::now();
  point4.target_pose.pose.position.x =3.0;
  point4.target_pose.pose.position.y = -1.0;
  point4.target_pose.pose.position.z = 0.0;
  point4.target_pose.pose.orientation.w = 1.0;
  goals.push_back(point4);
  // point 1
  goals.push_back(point1);
*/
  ROS_INFO("start moving");
  ROS_INFO("start moving");
  
  for(vector<move_base_msgs::MoveBaseGoal>::iterator ite = goals.begin(); ite != goals.end(); ite++) {
    ROS_INFO("Sending point");
    ac.sendGoal(*ite);
    ac.waitForResult();

    ros::Duration(5.0).sleep();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Hooray");
    else
      ROS_INFO("failed for some reason");
  }

  return 0;
}

