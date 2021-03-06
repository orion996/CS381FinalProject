/*
 * Physics2D.h
 *
 *  Created on: Mar 1, 2018
 *      Author: sushil
 */

#ifndef PHYSICS2D_H_
#define PHYSICS2D_H_

#include <Aspect.h>

class Physics2D : Aspect
{
public:
	Physics2D(Entity381 *ent);
	~Physics2D();

	void Tick(float dt);

	void checkForCollisions(float dt);
	void avoidWalls();

	float collisionTimer = 0.0;
};



#endif /* PHYSICS2D_H_ */
