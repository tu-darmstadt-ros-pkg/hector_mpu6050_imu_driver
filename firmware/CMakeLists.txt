cmake_minimum_required(VERSION 2.8.3)

include_directories(${ROS_LIB_DIR} ../lib)

# Remove this if using an Arduino without native USB (eg, other than Leonardo)
#add_definitions(-DUSB_CON)
add_definitions(-DMPU6050)

generate_arduino_firmware(MPU6050_imu
  SRCS MPU6050_IMU.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD nano328
  PORT /dev/ttyUSB0
)
