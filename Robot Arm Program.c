#include "dynamixel.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void move_to_location(int connection, unsigned char id,
			unsigned char loc_h, unsigned char loc_l) {

	unsigned char cs = ~ ( id + 0x07 + 0x03 + 0x1e + loc_l + loc_h +
				0x30 + 0x00);

	unsigned char arr[] = { 0xff, 0xff, id, 0x07, 0x03, 0x1e, loc_l,
                                       loc_h, 0x30, 0x00, cs };

	int buff_len = 100;
	unsigned char buff[buff_len];

	int bytes_read = write_to_connection(connection,arr,11,buff,buff_len);

}

void wait_until_done() {
	usleep(2000000);
}

//function to convert tower and block position into each joint's movement
void movePosition(unsigned char x, unsigned char y) {
	int connection = open_connection("/dev/ttyUSB0",B1000000);
	//initialize variables
	unsigned char id = 0;
	unsigned char rot1 = 0x01;
	unsigned char rot2 = 0x01;
	unsigned char j2 = 0x01;
	unsigned char j3 = 0x01;
	unsigned char j4 = 0x01;

	if (x==0) {
		//tower position 0
		rot2=0xaf;
	} else if (x==1) {
		//tower position 1
		rot2=0xff;
	} else if (x==2) {
		//tower position 2, uses a different quadrant, as we want the towers to be far apart.
		rot1=0x02;
		rot2=0x50;
	} else {
		printf("Error: not a rotation");
	}
	if (y==0) {
		//block position 0
		j2=0x2a;
		j3=0x42;
		j4=0x42;
	} else if (y==1) {
		//block position 1
		j2=0x4a;
		j3=0x32;
		j4=0x32;
	} else if (y==2) {
		//block position 2
		j2=0x6a;
		j3=0x22;
		j4=0x22;
	} else {
		printf("Error: not a position");
	}

	//rotates each joint to the position needed
	move_to_location(connection,1,rot1,rot2);
	move_to_location(connection,2,0x01,j2);
	move_to_location(connection,3,0x01,j3);
	move_to_location(connection,4,0x01,j4);
	wait_until_done();
}
//function to reset the position of the arm
void resetPosition() {
	int connection = open_connection("/dev/ttyUSB0",B1000000);

	//the 3 joints of the arm
	move_to_location(connection,2,0x01,0xff);
	move_to_location(connection,3,0x01,0xff);
	move_to_location(connection,4,0x01,0xff);
	wait_until_done();
	//then the rotation of the arm
	move_to_location(connection,1,0x01,0xff);
	wait_until_done();
}
//function to make the robot close the "hand", then reset its position
void grab() {
	int connection = open_connection("/dev/ttyUSB0",B1000000);
	move_to_location(connection,5,0x01,0x27);
	wait_until_done();
	resetPosition();
}
//function to make the robot open the "hand", then reset its position
void ungrab() {
	int connection = open_connection("/dev/ttyUSB0",B1000000);
	move_to_location(connection,5,0x01,0xff);
	wait_until_done();
	resetPosition();
}

int main(int argc, char* argv[]) {
	/*
	Start positions:
	Tower 0: none
	Tower 1: none
	Tower 2: Block 1 
			 Block 2
			 Block 3
	*/

	//move to and grab block 1
	movePosition(2,2);
	grab();

	//place in tower 1
	movePosition(1,0);
	ungrab();

	//move to and grab block 2
	movePosition(2,1);
	grab();

	//place in tower 0
	movePosition(0,0);
	ungrab();

	//move to and grab block 1
	movePosition(1,0);
	grab();

	//place on block 2
	movePosition(0,1);
	ungrab();

	//move to and grab block 3
	movePosition(2,0);
	grab();

	//place in tower 1
	movePosition(1,0);
	ungrab();

	//move to and grab block 1
	movePosition(0,1);
	grab();

	//place in tower 2
	movePosition(2,0);
	ungrab();

	//move to and grab block 2
	movePosition(0,0);
	grab();

	//place on block 3
	movePosition(1,1);
	ungrab();

	//move to and grab block 1
	movePosition(2,0);
	grab();

	//place on block 2
	movePosition(1,2);
	ungrab();

	//tower of hanoi solved
	return 0;

}
