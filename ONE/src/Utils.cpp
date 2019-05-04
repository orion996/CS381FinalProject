/*
 * Utils.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: sushil
 */


#include <Utils.h>

float FixAngle(float angle){ // hmmm
	if(angle < 0)
		return angle + 360;
	else if (angle > 360)
		return angle - 360;
	return angle;
}

float Clamp(float min, float max, float val){
	if(val < min){
		return min;
	} else if (val > max){
		return max;
	}
	return val;
}

float Distance(Ogre::Vector3 ptA, Ogre::Vector3 ptB)
{
  return sqrt(((ptB.x - ptA.x) * (ptB.x - ptA.x)) + ((ptB.z - ptA.z) * (ptB.z - ptA.z)));
}


