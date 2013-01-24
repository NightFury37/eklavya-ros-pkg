#ifndef _IMU_H
#define _IMU_H

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "tf/transform_broadcaster.h"
#include "sensor_msgs/Imu.h"

#ifndef TF_MATRIX3x3_H
  typedef btScalar tfScalar;
  namespace tf { typedef btMatrix3x3 Matrix3x3; }
#endif

namespace IMUspace
{
	class IMU
	{
	public:
		static void initIMU();
		static void getYaw(double *);
		static void closeIMU();
    static void update_pose(const sensor_msgs::Imu&);
	};
}

#endif
