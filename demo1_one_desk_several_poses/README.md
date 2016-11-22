# demo1_one_desk_several_poses

##目标：

实现手臂和地盘的控制，通过client发送一个goal，底盘移动到这个位置，然后手臂再移动到附近的位置。

## action定义及msgs的类型

参考MoveBase，没有action，因为server是默认启动的，action估计也是默认的，因此只需要些一个client就可以。client的类型是：move_base_msgs::MoveBaseGoal。深入看这个包：move_base_msgs，在这里定义了action：

```
geometry_msgs/PoseStamped target_pose
---
---
geometry_msgs/PoseStamped base_position
```

参考moveit的pose类型：`geometry_msgs::Pose`

关于actionlib，还有一个疑问？？？
Q1：一般一个单一的功能，需要运行一个server的main函数，一个client的main函数，client发送请求，server执行，没有问题。但是如果想要arm和base的控制在同一个模块中同时使用呢？也是需要些两个server的main函数同时运行？
Q2：callback的机制是什么意思

从[官网](http://docs.ros.org/fuerte/api/move_base_msgs/html/msg/MoveBaseGoal.html)可以看出，goal和result的类型都是`geometry_msgs/PoseStamped`，包含一个`Header header`，一个`Pose pose`；而一个`Pose`包含：`Point position`和一个`Quaternion orientation`；其中position是一个三维结构体，包含xyz，而orientation则包含四维xyzw的四元数。逻辑简单清晰。我们也得到启发，在设定最终的手臂的target的时候，类型还是应该调用PoseStamped。唯一不同的是，我们需要自己些一个action，类似上面的方法。

## server 和 client 的配置

有了action作为通信，下面我们来考虑一下server和client的部分应该怎么架构。

首先看看[base部分](http://wiki.ros.org/navigation/Tutorials/SendingSimpleGoals)。

base的server是默认在启动机器人的时候就启动好的，因此不需要启动。我们需要的就是定义一个client，然后设置goal，发送到server就可以。

然后是[arm部分]()

arm的操作使用moveit中的`moveit::planning_interface::MoveGroup`类来进行动作的规划，使用`moveit::planning_interface::PlanningSceneInterface`与世界直接交互？？？

（moveit教程这里还有一点问题，还不知道具体如何控制）

## server 和 client 应该如何架构

考虑现在需要两对server\client，分别是movebase和moveit。其中movebase的server

morne# 参考 gazebo_simulation

如林涛所说，gazebo_simulation的逻辑就是，打开gotopose_main.py，是一个服务器，里面定义了运动控制的逻辑。而cpp代码的pr2_client.cpp则是一个client，定义了一些发送goal，接受server反馈的一些功能，然后写了一个main函数，使其执行spin等操作。client一般不写spin和callback，但是这里其实是用这个callback去得到点云的实时反馈，因此我们的程序中不用考虑。

