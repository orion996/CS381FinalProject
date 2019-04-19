/*
 * InputMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef INPUTMGR_H_
#define INPUTMGR_H_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <Terrain/OgreTerrainGroup.h>
#include <Terrain/OgreTerrain.h>

# include <SdkTrays.h>
# include <SdkCameraMan.h>
#include <Mgr.h>
#include <Aspect.h>
#include <UnitAI.h>

class Engine;

class InputMgr:
		public Mgr,
		public OIS::KeyListener,
		public OIS::MouseListener,
		public OgreBites::SdkTrayListener
		{

public:
	InputMgr(Engine *engine);
	virtual ~InputMgr();

	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);

	virtual bool mouseMoved(const OIS::MouseEvent& me);
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);

	OIS::InputManager* mInputMgr;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;

	//mouse selection
	bool mMoveableFound;
	Ogre::RaySceneQuery* mRayScnQuery;
	OgreBites::SdkTrayManager* mTrayMgr;
	OgreBites::SdkCameraMan* mCameraMan;
	OgreBites::InputContext mInputContext;

	bool followMode;

	bool lmbDown;
	bool rmbDown;

	void Init();
	void Stop();
	void Tick(float dt);
	void LoadLevel();

	float keyboardTimer;
	const static float keyTime = 0.2f;
	float deltaDesiredSpeed, deltaDesiredHeading, deltaDesiredAltitude;
	void UpdateCamera(float dt);
	void UpdateVelocityAndSelection(float dt);


};

#endif /* INPUTMGR_H_ */
