/*
 * NOTE: Type of imu has to be defined in inv_mpu.h
 */

#include "freeram.h"

#include "mpu.h"
#include "I2Cdev.h"

#include <ros.h>
#include <ros/time.h>
#include <geometry_msgs/Quaternion.h>
#include <std_msgs/UInt32.h>

ros::NodeHandle nh;

geometry_msgs::Quaternion quat_msg;
ros::Publisher quat_pub("quaternion", &quat_msg);
/*
std_msgs::UInt32 success_msg;
ros::Publisher success_pub("success_packets", &success_msg);

std_msgs::UInt32 no_msg;
ros::Publisher no_pub("no_packets", &no_msg);

std_msgs::Int8 corrupted_msg;
ros::Publisher corrupted_pub("corrupted_packets", &corrupted_msg);

std_msgs::Int8 overflow_msg;
ros::Publisher overflow_pub("overflow_packets", &overflow_msg);
*/
int ret;
void setup() {
    Fastwire::setup(400,0);
    ret = mympu_open(200);

    nh.initNode();

    nh.advertise(quat_pub);
    //nh.advertise(success_pub);
    //nh.advertise(no_pub);
    //nh.advertise(corrupted_pub);
    //nh.advertise(overflow_pub);

}

unsigned int c = 0; //cumulative number of successful MPU/DMP reads
unsigned int np = 0; //cumulative number of MPU/DMP reads that brought no packet back
unsigned int err_c = 0; //cumulative number of MPU/DMP reads that brought corrupted packet
unsigned int err_o = 0; //cumulative number of MPU/DMP reads that had overflow bit set

void loop() {

    nh.spinOnce();

    ret = mympu_update();

    switch (ret) {
	case 0: c++; break;
	case 1: np++; return;
	case 2: err_o++; return;
	case 3: err_c++; return; 
    default:
		return;
    }
/*
    success_msg.data = c;
    success_pub.publish(&success_msg);
    no_msg.data = np;
    no_pub.publish(&no_msg);

    corrupted_msg.data = err_c;
    corrupted_pub.publish(&corrupted_msg);
    overflow_msg.data = err_o;
    overflow_pub.publish(&overflow_msg);
    */
    if (!(c%25)) {

        quat_msg.w = mympu.quat.w;
        quat_msg.x = mympu.quat.x;
        quat_msg.y = mympu.quat.y;
        quat_msg.z = mympu.quat.z;

        quat_pub.publish(&quat_msg);
    }
}

