#include "ros/ros.h"
#include "std_msgs/UInt32.h"

#include <sstream>
#include <cstdint>

typedef struct mfields{
	uint32_t m1 : 2;
	uint32_t m2 : 2;
	uint32_t m3 : 2;
	uint32_t m4 : 2;
	uint32_t t1 : 2;
	uint32_t t2 : 2;
	uint32_t t3 : 2;
	uint32_t t4 : 2;
	uint32_t i1 : 4;
	uint32_t i2 : 4;
	uint32_t i3 : 4;
	uint32_t i4 : 4;
}mfields;

typedef union motor_msg{
	mfields field;
	uint32_t raw;
}motor_msg;

//m1 m2 m3 m4 t1 t2 t3 t4 i1 i2 i3 i4
// 2  2  2  2  2  2  2  2  4  4  4  4
// stop   forward   backward    keep
// 00     01        10          11

ros::Publisher gPub;

void timerCallback(const ros::TimerEvent&){
	std_msgs::UInt32 msg;
	
	static int i = 0;
	uint32_t test[] = {
		0x4040a000,
		0,
		0x8040a000,
		0,
		0x10100a00,
		0,
		0x20100a00,
		0,
		0x40400a0,
		0,
		0x80400a0,
		0,
		0x101000a,
		0,
		0x201000a,
		0
	};
	
	if(i >= 16) i = 0;
	
	msg.data = test[i];
	gPub.publish(msg);
	
	ROS_INFO("Publishing to motor, instruction: %x", test[i]);

	i++;
}

int main(int argc, char **argv){

	ros::init(argc, argv, "motor_test_pub");
	ros::NodeHandle n;
	ros::Publisher motorPub = n.advertise<std_msgs::UInt32>("motorPub", 1000);	
	gPub = motorPub;
	ros::Timer timer = n.createTimer(ros::Duration(5), timerCallback);
	ros::spin();
	
	return 0;
}
