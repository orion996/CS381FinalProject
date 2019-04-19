/*
 * InputMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <GameMgr.h>

#include <Utils.h>

InputMgr::InputMgr(Engine *engine) : Mgr(engine) {

	this->mInputMgr = 0;
	this->mKeyboard = 0;
	this->mMouse = 0;
	this->keyboardTimer = keyTime;
	deltaDesiredSpeed = 3.0f;
	deltaDesiredHeading = 3.0f;
	deltaDesiredAltitude = 3.0f;
	mMoveableFound = false;
	mRayScnQuery = 0;
	mCameraMan = 0;
	mTrayMgr = 0;
	lmbDown = rmbDown = false;
	followMode = false;
}

InputMgr::~InputMgr() {

}

void InputMgr::Init(){

	  OIS::ParamList pl;
	  size_t windowHandle = 0;
	  std::ostringstream windowHandleStr;

	  engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHandle);
	  windowHandleStr << windowHandle;
	  pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));

	  #if defined OIS_WIN32_PLATFORM
	  	  pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	  	  pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	  	  pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	  	  pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
	  #elif defined OIS_LINUX_PLATFORM
	  	  pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	  	  pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	  	  pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	  	  pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
	  #endif
	  mInputMgr = OIS::InputManager::createInputSystem(pl);

	  mKeyboard = static_cast<OIS::Keyboard*>(
	    mInputMgr->createInputObject(OIS::OISKeyboard, false));
	  mMouse = static_cast<OIS::Mouse*>(
	    mInputMgr->createInputObject(OIS::OISMouse, true));

	  int left, top;
	  unsigned int width, height, depth;

	  engine->gfxMgr->mWindow->getMetrics(width, height, depth, left, top);
	  const OIS::MouseState &ms = mMouse->getMouseState();
	  ms.width = width;
	  ms.height = height;

	  mMouse->setEventCallback(this);
	  mKeyboard->setEventCallback(this);

	  mCameraMan = new OgreBites::SdkCameraMan(
			  engine->gfxMgr->mCamera);

	   mInputContext.mKeyboard = mKeyboard;
	   mInputContext.mMouse = mMouse;

	   mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName",
			   engine->gfxMgr->mWindow,
			   mInputContext,
			   engine->gfxMgr);
//	   mTrayMgr->hideCursor(); //DO NOT HIDE CURSOR!!!

	   mRayScnQuery = engine->gfxMgr->mSceneMgr->createRayQuery(Ogre::Ray());




}



void InputMgr::Stop(){
	if(mInputMgr){
		mInputMgr->destroyInputObject(mMouse);
		mInputMgr->destroyInputObject(mKeyboard);

		OIS::InputManager::destroyInputSystem(mInputMgr);
		mInputMgr = 0;
   	}
}

void InputMgr::Tick(float dt){
	//Must capture both every tick for buffered input to work
	mMouse->capture();
	mKeyboard->capture();

	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE)){
		engine->keepRunning = false;
	}

//	mTrayMgr->frameRenderingQueued(fe);

	UpdateCamera(dt);
	UpdateVelocityAndSelection(dt);
}

void InputMgr::UpdateCamera(float dt){
	float move = 400.0f;
	float rotate = 0.1f;

	 Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

	  if (mKeyboard->isKeyDown(OIS::KC_W))
		  dirVec.z -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_S))
		  dirVec.z += move;

	  if (mKeyboard->isKeyDown(OIS::KC_T))
		  dirVec.y += move;

	  if (mKeyboard->isKeyDown(OIS::KC_G))
		  dirVec.y -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_A))
		  dirVec.x -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_D))
		  dirVec.x += move;

	  if (mKeyboard->isKeyDown(OIS::KC_Q))
		  engine->gameMgr->cameraNode->yaw(Ogre::Degree(5 * rotate));

	  if (mKeyboard->isKeyDown(OIS::KC_E))
	  		  engine->gameMgr->cameraNode->yaw(Ogre::Degree(-5 * rotate));

	  if (mKeyboard->isKeyDown(OIS::KC_R))
	  		  engine->gameMgr->cameraNode->pitch(Ogre::Degree(5 * rotate));

	  if (mKeyboard->isKeyDown(OIS::KC_F))
	  		  engine->gameMgr->cameraNode->pitch(Ogre::Degree(-5 * rotate));

	  if (mKeyboard->isKeyDown(OIS::KC_Z))
	  		  engine->gameMgr->cameraNode->roll(Ogre::Degree(5 * rotate));

	  if (mKeyboard->isKeyDown(OIS::KC_X))
	  		  engine->gameMgr->cameraNode->roll(Ogre::Degree(-5 * rotate));

	  //follow Mode
	  keyboardTimer -= dt;
	  if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_C))
	  {
		  keyboardTimer = .5;

		  if(!followMode)
			  followMode = true;
		  else if(followMode)
		  {
			  engine->gfxMgr->mCamera->setPosition(0, 0, 80);
			  engine->gfxMgr->mCamera->lookAt(0, 0, -300);
			  followMode = false;
		  }

	  }

	  if(followMode)
	  {
//		  std::cout << "*** Following ***" << std::endl;
		  const Ogre::Vector3 pos = engine->entityMgr->selectedEntity->position;
		  engine->gfxMgr->mCamera->setPosition(pos.x, pos.y, pos.z + 80);
		  engine->gfxMgr->mCamera->lookAt(pos.x, pos.y, pos.z);
	  }

	  else if(!followMode)
		  engine->gameMgr->cameraNode->translate(dirVec * dt, Ogre::Node::TS_LOCAL);
}

void InputMgr::UpdateVelocityAndSelection(float dt){
	keyboardTimer -= dt;
	UnitAI* uai = (UnitAI*) engine->entityMgr->selectedEntity->aspects.at(1);

	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_I)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredSpeed += deltaDesiredSpeed;
		uai->clearCommands();
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_K)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredSpeed -= deltaDesiredSpeed;
		uai->clearCommands();
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_J)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredHeading -= deltaDesiredHeading;
		uai->clearCommands();
	//turn left is decreasing degrees, turn right is increasing degrees because increasing degrees gives us the +ive Z axis
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_L)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredHeading += deltaDesiredHeading;
		uai->clearCommands();
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_U))
	{
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredAltitude += deltaDesiredAltitude;
		uai->clearCommands();
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_O))
	{
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredAltitude -= deltaDesiredAltitude;
		uai->clearCommands();
	}
	engine->entityMgr->selectedEntity->desiredHeading = FixAngle(engine->entityMgr->selectedEntity->desiredHeading);
	engine->entityMgr->selectedEntity->desiredAltitude = FixAngle(engine->entityMgr->selectedEntity->desiredAltitude);

	//Set velocity to zero....
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_SPACE)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->velocity = Ogre::Vector3::ZERO;
		engine->entityMgr->selectedEntity->desiredSpeed = engine->entityMgr->selectedEntity->speed = 0;
		engine->entityMgr->selectedEntity->desiredHeading = engine->entityMgr->selectedEntity->heading;
		uai->clearCommands();
	}

	//tab handling
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_TAB)){
		keyboardTimer = keyTime;
		engine->entityMgr->SelectNextEntity();
	}
}

void InputMgr::LoadLevel(){

}

bool InputMgr::keyPressed(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& me){

	mTrayMgr->injectMouseMove(me);
//	if(rmbDown) mCameraMan->injectMouseMove(me);

	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID mid){

	const OIS::MouseState &ms = mMouse->getMouseState();

	if(mid == OIS::MB_Left && lmbDown == false)
	{
		Ogre::Ray mouseRay = mTrayMgr->getCursorRay(engine->gfxMgr->mCamera);

		std::vector<Entity381*> ent = engine->entityMgr->entities;

		for(unsigned int iter = 0 ; iter < engine->entityMgr->entities.size() ; iter++)
		{
			std::pair<bool, float> result = mouseRay.intersects(
					engine->entityMgr->entities[iter]->sceneNode->_getWorldAABB());

			if(result.first)
			{
				engine->entityMgr->SelectEntity(iter);
			}
		}


		lmbDown = true;
	}

	else if (mid == OIS::MB_Right)
	{
		Ogre::Ray mouseRay = mTrayMgr->getCursorRay(engine->gfxMgr->mCamera);

		std::vector<Entity381*> ent = engine->entityMgr->entities;
		Ogre::Plane* plane = engine->gameMgr->plane;

		bool intercept = false;

		for(unsigned int iter = 0 ; iter < engine->entityMgr->entities.size() ; iter++)
		{
			//mouseray intersects the entity
			std::pair<bool, float> entRes = mouseRay.intersects(
					engine->entityMgr->entities[iter]->sceneNode->_getWorldAABB());

			if(entRes.first)
			{
				//get target entity
				Entity381* target = engine->entityMgr->entities[iter];

				//get target coordinates
				Ogre::Vector3 targetPoint = target->position;

				//add intercept command with those coordinates
				UnitAI* uai = (UnitAI*) engine->entityMgr->selectedEntity->aspects.at(1);
				if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
				{
					uai->AddCommand("INTERCEPT", targetPoint, target);
				}
				else
				{
					uai->SetCommand("INTERCEPT", targetPoint, target);
				}

//				std::cout << "INTERCEPT COMMAND" << std::endl;

				intercept = true;
				break;
			}
		}
		//mouseray intersects the plane
		std::pair<bool, float> terrRes = mouseRay.intersects(*plane);
		if(terrRes.first && !intercept)
		{
			//get point coordinates
			Ogre::Vector3 worldPoint = mouseRay.getPoint(terrRes.second);
//				std::cout << "WORLD POINT: " << worldPoint << std::endl;

			//add moveTo command with those coordinates
			UnitAI* uai = (UnitAI*) engine->entityMgr->selectedEntity->aspects.at(1);

			if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			{
				uai->AddCommand("MOVETO", worldPoint, NULL);
			}
			else
			{
				uai->SetCommand("MOVETO", worldPoint, NULL);
			}
//			std::cout << "MOVETO COMMAND" << std::endl;

			intercept = false;
		}



		rmbDown = true;
	}

	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mid){

	if (mid == OIS::MB_Right)
	{
		rmbDown = false;
	}
	else if (mid == OIS::MB_Left)
	{
		lmbDown = false;
	}

	return true;
}
