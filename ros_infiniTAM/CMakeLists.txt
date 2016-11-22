cmake_minimum_required(VERSION 2.8.3)
project(ros_infiniTAM)

set(CMAKE_CXX_FLAGS "-march=native -mno-avx")
#using cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/src/cmake")
#using catkin_make
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/src/cmake")

macro(CANONIFY_BOOL var)
  if (${var})
    set(${var} TRUE)
  else()
    set(${var} FALSE)
  endif()
endmacro()

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  message_filters
  roscpp
  sensor_msgs
  moveit_msgs
  actionlibe
  actionlib_msgs
  moveit_ros_planning_interface
)
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
## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
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

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ros_infiniTAM
  CATKIN_DEPENDS cv_bridge message_filters actionlib roscpp sensor_msgs
  DEPENDS roslib system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)
message( "catkin_INCLUDE_DIRS: " ${catkin_INCLUDE_DIRS})
## Declare a C++ library
# add_library(fetch_action_server
#     src/fetch_action_server.cpp
#  )
# target_link_libraries(fetch_action_server ${catkin_LIBRARIES})
## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(Ros_infiniTAM ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
# add_executable(Ros_infiniTAM_node src/Ros_infiniTAM_node.cpp)


add_executable(ros_InfiniTAM src/ros_infiniTAM.cpp src/fetch_action_server.cpp include/ros_infiniTAM/fetch_action_server.h) # include/ros_infiniTAM/fibonacci_server.h
#add_executable(fetch_server  src/fetch_action_server.cpp)
#add_executable(fibonacci src/fibonacci_server.cpp)
target_link_libraries(ros_InfiniTAM ${catkin_LIBRARIES})
#target_link_libraries(fibonacci ${catkin_LIBRARIES})
#target_link_libraries(fetch_server ${catkin_LIBRARIES})
target_link_libraries(ros_InfiniTAM Engine)
target_link_libraries(ros_InfiniTAM Utils)
#target_link_libraries(ros_InfiniTAM fetch_action_server)
## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(Ros_infiniTAM_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(Ros_infiniTAM_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS Ros_infiniTAM Ros_infiniTAM_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_Ros_infiniTAM.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
