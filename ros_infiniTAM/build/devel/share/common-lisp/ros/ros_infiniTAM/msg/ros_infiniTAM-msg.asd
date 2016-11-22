
(cl:in-package :asdf)

(defsystem "ros_infiniTAM-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :actionlib_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "ros_goalGoal" :depends-on ("_package_ros_goalGoal"))
    (:file "_package_ros_goalGoal" :depends-on ("_package"))
    (:file "ros_goalActionGoal" :depends-on ("_package_ros_goalActionGoal"))
    (:file "_package_ros_goalActionGoal" :depends-on ("_package"))
    (:file "ros_goalFeedback" :depends-on ("_package_ros_goalFeedback"))
    (:file "_package_ros_goalFeedback" :depends-on ("_package"))
    (:file "ros_goalActionFeedback" :depends-on ("_package_ros_goalActionFeedback"))
    (:file "_package_ros_goalActionFeedback" :depends-on ("_package"))
    (:file "ros_goalAction" :depends-on ("_package_ros_goalAction"))
    (:file "_package_ros_goalAction" :depends-on ("_package"))
    (:file "ros_goalActionResult" :depends-on ("_package_ros_goalActionResult"))
    (:file "_package_ros_goalActionResult" :depends-on ("_package"))
    (:file "ros_goalResult" :depends-on ("_package_ros_goalResult"))
    (:file "_package_ros_goalResult" :depends-on ("_package"))
  ))