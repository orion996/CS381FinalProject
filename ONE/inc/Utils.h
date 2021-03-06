/*
 * Utils.h
 *
 *  Created on: Mar 1, 2018
 *      Author: sushil
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <OgreVector3.h>
#include <cmath>

float FixAngle(float angle);
float Clamp(float min, float max, float val);
float Distance(Ogre::Vector3, Ogre::Vector3);



#endif /* UTILS_H_ */
