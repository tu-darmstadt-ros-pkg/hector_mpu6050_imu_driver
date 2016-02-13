#ifndef MPU_H
#define MPU_H


struct s_quat { float w, x, y, z; };

struct s_mympu {
    s_quat quat;
	float ypr[3];
	float gyro[3];
};

extern struct s_mympu mympu;

int mympu_open(unsigned int rate);
int mympu_update();

#endif

