/*
 * GameMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>

#include <EntityMgr.h>
#include <GameMgr.h>
#include <GfxMgr.h>

#include <iostream>
#include <Types381.h>

#include <OgreOverlay.h>
#include <OgreSceneNode.h>
#include <OgreMeshManager.h>


GameMgr::GameMgr(Engine *engine): Mgr(engine) {
	cameraNode = 0;
}

GameMgr::~GameMgr() {
	// TODO Auto-generated destructor stub
}

void GameMgr::Init(){
	  engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	  engine->gfxMgr->mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	  Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
	  light->setPosition(20.0, 80.0, 50.0);


	  // A node to attach the camera to so we can move the camera node instead of the camera.
	  cameraNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	  cameraNode->setPosition(0, 200, 500);
	  cameraNode->attachObject(engine->gfxMgr->mCamera);

	  gun = engine->gfxMgr->mSceneMgr->createEntity("glock.mesh");
	  gunNode = cameraNode->createChildSceneNode();
	  gunNode->attachObject(gun);
	  gunNode->setPosition(20, -15, 10);
	  gunNode->pitch(Ogre::Degree(-90));
	  gunNode->yaw(Ogre::Degree(90));
	  gunNode->setScale(4,4,4);


	  MakeGround();
	  MakeSky();
	  MakeEntities();

}

void GameMgr::LoadLevel(){

//	  engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
//
//	  engine->gfxMgr->mCamera->lookAt(Ogre::Vector3(0, 0, 0));
//	  Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
//	  light->setPosition(20.0, 80.0, 50.0);
//
//
//	  // A node to attach the camera to so we can move the camera node instead of the camera.
//	  cameraNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
//	  cameraNode->setPosition(0, 200, 500);
//	  cameraNode->attachObject(engine->gfxMgr->mCamera);
//
//	  MakeGround();
//	  MakeSky();
//	  MakeEntities();
}

void GameMgr::MakeEntities(){

	srand(time(NULL));
	Ogre::Vector3 pos = Ogre::Vector3(0,20,0);
	int index = 0;

	for(int i = 0 ; i < 20 ; i++)
	{
		float hatTemp = rand()%2;
		bool hat = false;
		if(hatTemp)
			hat = true;
		else
			hat = false;

		float negTemp = rand()%2;
		int neg = 1;
		if(negTemp)
			neg = 1;
		else
			neg = -1;

		pos = Ogre::Vector3(rand()%500 * neg, 25, rand()%500 * neg);

		if(hat)
		{
			engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, pos, false, NULL, true);
			index++;
			engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, pos, true, engine->entityMgr->GetEntityAt(index - 1), false);
//			engine->entityMgr->GetEntityAt(i)->hasHat = true;
		}
		else
		{
			engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, pos, false, NULL, false);
//			engine->entityMgr->GetEntityAt(i)->hasHat = false;

		}
		pos.x += 20;
		index++;
	}
	engine->entityMgr->SelectNextEntity(); //sets selection
	engine->entityMgr->GetEntityAt(0)->isTarget = true;
	for(int i=1 ; i<engine->entityMgr->entities.size() ; i++)
		engine->entityMgr->GetEntityAt(i)->isTarget = false;
}

void GameMgr::MakeGround(){

	 plane = new Ogre::Plane(Ogre::Vector3::UNIT_Y, 0);
	 Ogre::Plane* wall1 = new Ogre::Plane(Ogre::Vector3(0,0,1), -750);
	 Ogre::Plane* wall2 = new Ogre::Plane(Ogre::Vector3(1,0,0), -750);
	 Ogre::Plane* wall3 = new Ogre::Plane(Ogre::Vector3(-1,0,0), -750);
	 Ogre::Plane* wall4 = new Ogre::Plane(Ogre::Vector3(0,0,-1), -750);

	  Ogre::MeshManager::getSingleton().createPlane(
	    "ground",
	    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	    *plane,
	    1500, 1500, 20, 20,
	    true,
	    1, 5, 5,
	    Ogre::Vector3::UNIT_Z);
	  Ogre::MeshManager::getSingleton().createPlane(
	  	    "wall1",
	  	    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  	    *wall1,
	  	    1500, 300, 200, 1,
	  	    true,
	  	    1, 10, 5,
	  	    Ogre::Vector3::UNIT_Y);

	  Ogre::MeshManager::getSingleton().createPlane(
	  	  	    "wall2",
	  	  	    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  	  	    *wall2,
	  	  	    1500, 300, 200, 1,
	  	  	    true,
	  	  	    1, 10, 5,
	  	  	    Ogre::Vector3::UNIT_Y);
	  Ogre::MeshManager::getSingleton().createPlane(
	  	  	  	    "wall3",
	  	  	  	    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  	  	  	    *wall3,
	  	  	  	    1500, 300, 200, 1,
	  	  	  	    true,
	  	  	  	    1, 10, 5,
	  	  	  	    Ogre::Vector3::UNIT_Y);
	  Ogre::MeshManager::getSingleton().createPlane(
	  	  	  	    "wall4",
	  	  	  	    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  	  	  	    *wall4,
	  	  	  	    1500, 300, 200, 1,
	  	  	  	    true,
	  	  	  	    1, 10, 5,
	  	  	  	    Ogre::Vector3::UNIT_Y);



	  Ogre::Entity* groundEntity = engine->gfxMgr->mSceneMgr->createEntity("ground");
	  engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	  groundEntity->setCastShadows(false);
	  //groundEntity->setMaterialName("Ocean2_HLSL_GLSL");
	  //groundEntity->setMaterialName("OceanHLSL_GLSL");
	  groundEntity->setMaterialName("Texture/Flooring");
	  //groundEntity->setMaterialName("NavyCg");


	  Ogre::Entity* wallEntity1 = engine->gfxMgr->mSceneMgr->createEntity("wall1");
	  engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(wallEntity1);
	  wallEntity1->setMaterialName("Texture/Walls");

	  Ogre::Entity* wallEntity2 = engine->gfxMgr->mSceneMgr->createEntity("wall2");
	  engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(wallEntity2);
	  wallEntity2->setMaterialName("Texture/Walls");

	  Ogre::Entity* wallEntity3 = engine->gfxMgr->mSceneMgr->createEntity("wall3");
	  engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(wallEntity3);
	  wallEntity3->setMaterialName("Texture/Walls");

	  Ogre::Entity* wallEntity4 = engine->gfxMgr->mSceneMgr->createEntity("wall4");
	  engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(wallEntity4);
	  wallEntity4->setMaterialName("Texture/Walls");
}

void GameMgr::MakeSky(){
	engine->gfxMgr->mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");
}
