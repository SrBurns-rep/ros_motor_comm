#include "ros/ros.h"
#include "std_msgs/UInt32.h"
#include <ncurses.h>

//m1 m2 m3 m4 t1 t2 t3 t4 i1 i2 i3 i4
// 2  2  2  2  2  2  2  2  4  4  4  4
// stop   forward   backward    keep
// 00     01        10          11

int main(int argc, char **argv){

	initscr();
	noecho();
	keypad(stdscr, TRUE);
	halfdelay(1);

	ros::init(argc, argv, "teleop");
	ros::NodeHandle n;
	ros::Publisher teleop_pub = n.advertise<std_msgs::UInt32>("teleop",  1000);
	ros::Rate loop_rate(100);
	
	printw("Teleop robot.\n");
	refresh();

	std_msgs::UInt32 umsg;
	
	int ch = 0, prevch = 0, count = 0, ctrl = 0;
	
	while(ros::ok()){
	
		ch = getch();
		
		attron(A_BOLD);
		if(prevch > 0){
			count++;
		}else{
			count = 0;
		}
		if(count > 1 && ch > 0){
			mvprintw(1, 0, "%i\n", ch);
			ctrl = ch;
		}
		else{
			mvprintw(1, 0, "%i\n", -1);
			ctrl = -1;
		}
		mvprintw(2, 0, "%i\n", count);
		attroff(A_BOLD);
		refresh();
		prevch = ch;
		if(ch == 'q')break;
		
		switch(ctrl){
			case 'w':
				umsg.data = 0x5555aaaa;
				break;
			case 's':
				umsg.data = 0xaa55aaaa;
				break;
			case 'a':
				umsg.data = 0x9955aaaa;
				break;
			case 'd':
				umsg.data = 0x6655aaaa;
				break;
			default:
				umsg.data = 0;
		}
	
		ROS_INFO("instruction: %x", umsg.data);
		teleop_pub.publish(umsg);
		ros::spinOnce();
		loop_rate.sleep();
	
	}
	endwin();
	return 0;
}
