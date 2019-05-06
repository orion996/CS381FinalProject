/*
 * UnitAI.h
 *
 *  Created on: Apr 1, 2019
 *      Author: orion996
 */

#ifndef INC_UNITAI_H_
#define INC_UNITAI_H_

#include <list>
#include <string>
#include <OgreVector3.h>
#include <Aspect.h>
#include <Utils.h>
#include <OgreNode.h>
#include <stdlib.h>
#include <time.h>
#include <OgreCamera.h>


struct Command
{
	std::string type;
	Ogre::Vector3 point;
	bool isDone;
	Entity381* target;
	Ogre::Vector3 upperBound;
	Ogre::Vector3 lowerBound;
};

class UnitAI : Aspect
{
public:
	std::list<Command*> commands;

	UnitAI(Entity381* ent);
	~UnitAI();

	void Tick(float dt);
	void SetCommand(std::string, Ogre::Vector3, Entity381*);
	void AddCommand(std::string, Ogre::Vector3, Entity381*);

	void clearCommands();
	void deleteCurrentCommand();

	float boundConst = 15.0;

	Ogre::Camera* camNode;
};



#endif /* INC_UNITAI_H_ */
