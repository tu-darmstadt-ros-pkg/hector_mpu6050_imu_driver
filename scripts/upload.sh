#!/bin/bash

# This only works when in the workspace root, has to be made more robust

# Obsolete, using plain catkin
#catkin_make hector_mpu6050_imu_driver_firmware_mpu6050_imu-upload

# For use with catkin tools, see https://github.com/ros-drivers/rosserial/issues/244
catkin build --no-deps hector_mpu6050_imu_driver --make-args hector_mpu6050_imu_driver_firmware_mpu6050_imu-upload
