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

	Ogre::SceneNode *cameraNode;
	Ogre::Plane* plane;//(Ogre::Vector3::UNIT_Y, 0);
	Ogre::Entity* gun;
	Ogre::SceneNode* gunNode;

};

#endif /* GAMEMGR_H_ */
