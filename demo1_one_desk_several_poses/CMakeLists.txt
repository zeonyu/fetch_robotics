cmake_minimum_required(VERSION 2.8.3)
project(demo1_one_desk_several_poses)

##############################################
## -------- End of Zeon ------------------- ##
##############################################

set(CMAKE_CXX_FLAGS "-march=native -mno-avx -ggdb")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/src/cmake")

macro(CANONIFY_BOOL var)
  if (${var})
    set(${var} TRUE)
  else()
    set(${var} FALSE)
  endif()
endmacro()
#find_package(Eigen REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

find_package(CUDA QUIET)
CANONIFY_BOOL(CUDA_FOUND)
message(STATUS "CUDA found: " ${CUDA_FOUND})

find_package(OpenNI QUIET)
CANONIFY_BOOL(OPENNI_FOUND)
message(STATUS "OpenNI found: " ${OPENNI_FOUND})

find_package(libuvc QUIET)
CANONIFY_BOOL(libuvc_FOUND)
message(STATUS "libuvc found: ${libuvc_FOUND}")

find_package(RealSense QUIET)
CANONIFY_BOOL(REALSENSE_FOUND)
message(STATUS "librealsense found: ${REALSENSE_FOUND}")

find_package(PNG QUIET)
CANONIFY_BOOL(PNG_FOUND)
message(STATUS "libpng found: ${PNG_FOUND}")

OPTION(WITH_CUDA "Build with CUDA support?" ${CUDA_FOUND})
INCLUDE(${PROJECT_SOURCE_DIR}/src/cmake/UseOpenMP.cmake)
OPTION(WITH_REALSENSE "Build with Intel RealSense support?" ${REALSENSE_FOUND})

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=corei7-avx -stdlib=libstdc++ -Wno-deprecated-declarations -Wno-unused-function")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -march=corei7-avx -stdlib=libstdc++")
ENDIF()

add_subdirectory(src/ORUtils)
add_subdirectory(src/ITMLib)
add_subdirectory(src/Utils)
add_subdirectory(src/Engine)
IF(WITH_CUDA)
  include_directories(${CUDA_INCLUDE_DIRS})
ELSE()
  add_definitions(-DCOMPILE_WITHOUT_CUDA)
ENDIF()


##############################################
## ------------ End of Zeon --------------- ##
##############################################

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  cv_bridge
  message_filters
  moveit_msgs
  moveit_ros_planning_interface
  roscpp
  roslib
  sensor_msgs
)

# catkin_python_setup()

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate actions in the 'action' folder
add_action_files(
   FILES
   ros_goal.action
)

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   sensor_msgs
   moveit_msgs
   actionlib_msgs
)

## The catkin_package macro generates cmake config files for your package
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES demo1_one_desk_several_poses
  CATKIN_DEPENDS actionlib actionlib_msgs cv_bridge message_filters moveit_ros_planning_interface roscpp roslib sensor_msgs
  DEPENDS system_lib
)

## Specify additional locations of header files
include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(demo1_one_desk_several_poses_node src/demo1_one_desk_several_poses_node.cpp src/fetch_action_server.cpp include/demo1_one_desk_several_poses/fetch_action_server.h)

## Specify libraries to link a library or executable target against
target_link_libraries(demo1_one_desk_several_poses_node
  ${catkin_LIBRARIES}
  Engine
  Utils
)


