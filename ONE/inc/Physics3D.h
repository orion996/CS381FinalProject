/*
 * Physics3D.h
 *
 *  Created on: Mar 21, 2019
 *      Author: orion996
 */

#ifndef INC_PHYSICS3D_H_
#define INC_PHYSICS3D_H_

#include <Aspect.h>

class Physics3D : Aspect
{
public:
	Physics3D(Entity381 *ent);
	~Physics3D();

	void Tick(float dt);
};



#endif /* INC_PHYSICS3D_H_ */
