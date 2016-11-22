//#include <ros_infiniTAM/fibonacci_server.h>

class FibonacciAction
{
protected:

  ros::NodeHandle nh_;
  // NodeHandle instance must be created before this line. Otherwise strange error may occur.
  actionlib::SimpleActionServer<learning_actionlib::FibonacciAction> as_; 
  std::string action_name_;
  // create messages that are used to published feedback/result
  learning_actionlib::FibonacciFeedback feedback_;
  learning_actionlib::FibonacciResult result_;

public:

  FibonacciAction(std::string name) :
    as_(nh_, name, boost::bind(&FibonacciAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~FibonacciAction(void)
  {
  }

  void executeCB(const learning_actionlib::FibonacciGoalConstPtr &goal);

};


