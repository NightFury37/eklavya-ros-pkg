#ifndef _EKLAVYA2_H_
#define _EKLAVYA2_H_

#include <unistd.h>   /* Needed for sleep() and usleep() */
#include <pthread.h>  /* Needed for all pthread library calls */

#include "Modules/Lidar/LidarData.h"

#define MAP_MAX 1000
enum Strategies {
  FollowNose = 0,
  TrackWayPoint,
  HectorSLAM
};

typedef struct Triplet {
  double x, y, z;
} Triplet;
typedef struct Pose {
  Triplet position;
  Triplet orientation; // Roll - Pitch - Yaw
} Pose;
typedef struct LatLong {
  double latitude;
  double longitude;
} LatLong;
typedef struct Odom {
  double left_velocity;
  double right_velocity;
} Odom;

/* Global data structures to be shared by all threads */
extern Pose pose; // Shared by IMU, EKF
extern LatLong lat_long; // Shared by GPS, EKF
extern Odom odom; // Shared by Encoder, EKF
extern char global_map[MAP_MAX][MAP_MAX]; // Shared by Lidar, Planner
extern Triplet bot_location; // Shared by EKF, Planner
extern Triplet target_location; // Shared by EKF, Planner

extern LidarData *laser;
extern int strategy;

/* mutex for mutually exclusive updating of the shared data structures */
extern pthread_mutex_t pose_mutex;
extern pthread_mutex_t lat_long_mutex;
extern pthread_mutex_t odom_mutex;
extern pthread_mutex_t map_mutex;
extern pthread_mutex_t bot_location_mutex;
extern pthread_mutex_t target_location_mutex;

void *imu_thread(void *arg);
void *lidar_thread(void *arg);
void *gps_thread(void *arg);
void *encoder_thread(void *arg);
void *ekf_thread(void *arg);
void *slam_thread(void *arg);
void *navigation_thread(void *arg);
void *planner_thread(void *arg);
void *diagnostics_thread(void *arg);

#endif
