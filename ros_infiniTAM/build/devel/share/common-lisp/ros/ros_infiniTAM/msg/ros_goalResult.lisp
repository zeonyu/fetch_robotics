; Auto-generated. Do not edit!


(cl:in-package ros_infiniTAM-msg)


;//! \htmlinclude ros_goalResult.msg.html

(cl:defclass <ros_goalResult> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass ros_goalResult (<ros_goalResult>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ros_goalResult>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ros_goalResult)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_infiniTAM-msg:<ros_goalResult> is deprecated: use ros_infiniTAM-msg:ros_goalResult instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <ros_goalResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_infiniTAM-msg:success-val is deprecated.  Use ros_infiniTAM-msg:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ros_goalResult>) ostream)
  "Serializes a message object of type '<ros_goalResult>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ros_goalResult>) istream)
  "Deserializes a message object of type '<ros_goalResult>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ros_goalResult>)))
  "Returns string type for a message object of type '<ros_goalResult>"
  "ros_infiniTAM/ros_goalResult")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ros_goalResult)))
  "Returns string type for a message object of type 'ros_goalResult"
  "ros_infiniTAM/ros_goalResult")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ros_goalResult>)))
  "Returns md5sum for a message object of type '<ros_goalResult>"
  "358e233cde0c8a8bcfea4ce193f8fc15")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ros_goalResult)))
  "Returns md5sum for a message object of type 'ros_goalResult"
  "358e233cde0c8a8bcfea4ce193f8fc15")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ros_goalResult>)))
  "Returns full string definition for message of type '<ros_goalResult>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%~%#result definition~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ros_goalResult)))
  "Returns full string definition for message of type 'ros_goalResult"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%~%#result definition~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ros_goalResult>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ros_goalResult>))
  "Converts a ROS message object to a list"
  (cl:list 'ros_goalResult
    (cl:cons ':success (success msg))
))
