#include <stdio.h>
#include "../../eklavya2.h"
#include "navigation.h"

void *navigation_thread(void *arg) {
  int iterations = 0;
  double heading;
  double latitude, longitude;
  Triplet my_target_location;
  Triplet my_bot_location;
  char walkability[MAP_MAX][MAP_MAX];
  
  while(ros::ok()) {
    iterations++;
    switch(strategy) {
      case FollowNose:
        pthread_mutex_lock(&pose_mutex);        
        heading = -pose.orientation.z; 
        pthread_mutex_unlock(&pose_mutex);
        
        navigation_space::FollowNoseStrategy::calibrateReferenceHeading(heading, iterations);
        
        if(iterations < 50) {
          break;
        }
        
        my_target_location = navigation_space::FollowNoseStrategy::getTargetLocation(heading);
        pthread_mutex_lock(&target_location_mutex);
        target_location = my_target_location; // Target
        pthread_mutex_unlock(&target_location_mutex);
        
        my_bot_location = navigation_space::FollowNoseStrategy::getBotLocation();
        pthread_mutex_lock(&bot_location_mutex);
        bot_location = my_bot_location; // Bot
        pthread_mutex_unlock(&bot_location_mutex);
        
        break;
        
      case TrackWayPoint:
        pthread_mutex_lock(&pose_mutex);        
        heading = pose.orientation.z; // Yaw
        pthread_mutex_unlock(&pose_mutex);
        
        pthread_mutex_lock(&lat_long_mutex);        
        latitude = lat_long.latitude; 
        longitude = lat_long.longitude; 
        pthread_mutex_unlock(&lat_long_mutex);

        my_target_location = navigation_space::TrackWayPointStrategy::getTargetLocation(latitude, longitude, heading);
        pthread_mutex_lock(&target_location_mutex);
        target_location = my_target_location; // Target
        cout << "[NAV] [INFO] Target Location: " << target_location.x << " " << target_location.y << endl;
        pthread_mutex_unlock(&target_location_mutex);
        
        my_bot_location = navigation_space::TrackWayPointStrategy::getBotLocation();
        pthread_mutex_lock(&bot_location_mutex);
        bot_location = my_bot_location; // Bot
        pthread_mutex_unlock(&bot_location_mutex);
        
        break;
    }

    usleep(10);
  }
}

