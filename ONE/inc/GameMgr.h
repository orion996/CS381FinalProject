/*
 * GameMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef GAMEMGR_H_
#define GAMEMGR_H_

#include <Mgr.h>
#include <stdlib.h>
#include <time.h>

//#include <OgreOverlay.h>
//#include <OgreSceneNode.h>
//#include <OgreMeshManager.h>
//#include <OgreVector3.h>

class GameMgr: public Mgr {
public:
	GameMgr(Engine *engine);
	virtual ~GameMgr();

	void Init();
	void LoadLevel();

	void MakeGround();
	void MakeSky();
	void MakeEntities();
	void MakeGun();

	Ogre::SceneNode *cameraNode;
	Ogre::Plane* plane;//(Ogre::Vector3::UNIT_Y, 0);
	Ogre::Entity* gun;
	Ogre::SceneNode* gunNode;

	Ogre::Plane* wall1;
	Ogre::Plane* wall2;
	Ogre::Plane* wall3;
	Ogre::Plane* wall4;
	Ogre::Entity* wallEntity1;
	Ogre::Entity* wallEntity2;
	Ogre::Entity* wallEntity3;
	Ogre::Entity* wallEntity4;


};

#endif /* GAMEMGR_H_ */
