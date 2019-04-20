/*
 * UnitAI.cpp
 *
 *  Created on: Apr 1, 2019
 *      Author: orion996
 */

#include <UnitAI.h>
#include <Entity381.h>


UnitAI::UnitAI(Entity381* ent) : Aspect(ent)
{
//	srand(time(NULL));
}

UnitAI::~UnitAI()
{

}

void UnitAI::AddCommand(std::string type, Ogre::Vector3 point, Entity381* tgt)
{
	Command* tempCom = new Command();
	tempCom->type = type;
	tempCom->point = point;
	tempCom->isDone = false;
	tempCom->target = tgt;

	tempCom->lowerBound.x = point.x - boundConst;
	tempCom->upperBound.x = point.x + boundConst;
	tempCom->lowerBound.z = point.z - boundConst;
	tempCom->upperBound.z = point.z + boundConst;

	commands.push_back(tempCom);
}

void UnitAI::SetCommand(std::string type, Ogre::Vector3 point, Entity381* tgt)
{
	Command* tempCom = new Command();
	tempCom->type = type;
	tempCom->point = point;
	tempCom->isDone = false;
	tempCom->target = tgt;

	tempCom->lowerBound.x = point.x - boundConst;
	tempCom->upperBound.x = point.x + boundConst;
	tempCom->lowerBound.z = point.z - boundConst;
	tempCom->upperBound.z = point.z + boundConst;


	commands.clear();
	commands.push_back(tempCom);

}

void UnitAI::Tick(float dt)
{
	//			//add moveTo command with those coordinates
	//			UnitAI* uai = (UnitAI*) engine->entityMgr->selectedEntity->aspects.at(1);
	//
	//			if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
	//			{
	//				uai->AddCommand("MOVETO", worldPoint, NULL);
	//			}



	//seg fault if the list is empty, so return instead
	if(commands.empty() && !entity->mIsHat)
	{

		float temp = rand()%2;
		int neg = 1;
		if(temp)
			neg = 1;
		else
			neg = -1;

//		srand(time(NULL));
		Ogre::Vector3 worldPoint;
		worldPoint.y = 0;

//		srand(time(NULL));
		worldPoint.x = rand()%500 * neg;

//		srand(time(NULL));
		worldPoint.z = rand()%500 * neg;

		this->SetCommand("MOVETO", worldPoint, NULL);
//		return;
	}
	if(commands.empty() && entity->mIsHat)
	{
		return;
	}

	if(commands.front()->type == "MOVETO")
	{
		Ogre::Vector3 pos = entity->position;
		Ogre::Vector3 direction = commands.front()->point - pos;

		//check if point equals the current position
		if(pos.x >= commands.front()->lowerBound.x &&
				pos.z >= commands.front()->lowerBound.z &&
				pos.x <= commands.front()->upperBound.x &&
				pos.z <= commands.front()->upperBound.z)//if yes, stop moving and pop the command
		{
			entity->desiredSpeed = 0;
			commands.pop_front();
		}
		else//if no, rotate entity towards the point and max speed
		{
			entity->desiredHeading = FixAngle((Ogre::Math::ATan2(direction.z, direction.x)).valueDegrees());
			entity->desiredSpeed = entity->maxSpeed;
		}
	}
	else if(commands.front()->type == "INTERCEPT")
	{
		//update the point to the target's position
		commands.front()->point = commands.front()->target->position;

		//update point bounds
		commands.front()->lowerBound.x = commands.front()->point.x - boundConst;
		commands.front()->lowerBound.z = commands.front()->point.x - boundConst;
		commands.front()->upperBound.x = commands.front()->point.x + boundConst;
		commands.front()->upperBound.z = commands.front()->point.x + boundConst;

		Ogre::Vector3 pos = entity->position;
		Ogre::Vector3 direction = commands.front()->point - pos;

		//check if point equals the current position
		if(pos.x >= commands.front()->lowerBound.x &&
						pos.z >= commands.front()->lowerBound.z &&
						pos.x <= commands.front()->upperBound.x &&
						pos.z <= commands.front()->upperBound.z)//if yes, stop moving and pop the command
		{
			entity->desiredSpeed = entity->speed = 0;
			commands.pop_front();
		}
		else//if no, rotate entity towards the point and max speed
		{
			entity->desiredHeading = FixAngle((Ogre::Math::ATan2(direction.z, direction.x)).valueDegrees());
			entity->desiredSpeed = entity->maxSpeed;
		}
	}
	else
	{
		commands.pop_front();
	}
}


void UnitAI::clearCommands()
{
	commands.clear();
}