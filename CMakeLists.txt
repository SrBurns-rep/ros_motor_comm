cmake_minimum_required(VERSION 3.0.2)
project(motor_comm)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  genmsg
)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(motor_test_pub src/motor_test_pub.cpp)
target_link_libraries(motor_test_pub ${catkin_LIBRARIES})
