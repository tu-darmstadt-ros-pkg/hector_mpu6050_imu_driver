/*
 * NOTE: Type of imu has to be defined in inv_mpu.h
 */

#include "freeram.h"

#include "mpu.h"
#include "I2Cdev.h"

#include <ros.h>
#include <ros/time.h>
#include <geometry_msgs/Quaternion.h>

ros::NodeHandle nh;

geometry_msgs::Quaternion quat_msg;
ros::Publisher quat_pub("quaternion", &quat_msg);

int ret;
void setup() {
    Fastwire::setup(400,0);
    ret = mympu_open(200);

    nh.initNode();

    nh.advertise(quat_pub);

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

    quat_msg.w = mympu.quat.w;
    quat_msg.x = mympu.quat.x;
    quat_msg.y = mympu.quat.y;
    quat_msg.z = mympu.quat.z;

    quat_pub.publish(&quat_msg);
}

