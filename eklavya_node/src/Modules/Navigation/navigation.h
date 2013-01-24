#ifndef _NAVIGATION_H_
#define _NAVIGATION_H_

#include "ros/ros.h"
#include "../../eklavya2.h"

namespace navigation_space {
  class FollowNoseStrategy {
  public:
    static void calibrateReferenceHeading(double, int);
    static Triplet getTargetLocation(double);
    static Triplet getBotLocation();
	};
  
  class TrackWayPointStrategy {
  public:
    static Triplet getTargetLocation(double);
    static Triplet getBotLocation();
  };
}

#endif
