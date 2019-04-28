/*
 * GfxMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef GFXMGR_H_
#define GFXMGR_H_

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

# include <SdkTrays.h>
#include <OgreVector3.h>
#include <SoundMgr.h>
#include <Mgr.h>


class GfxMgr:
		public Mgr,
		public Ogre::WindowEventListener,
		public Ogre::FrameListener,
		public OgreBites::SdkTrayListener{
public:
	GfxMgr(Engine *engine);
	virtual ~GfxMgr();

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	virtual void windowClosed(Ogre::RenderWindow* rw);
//---------------
	void Init();
	void LoadLevel();
	void Tick(float dt);
	void Stop();


	//Ogre related stuff
	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	Ogre::OverlaySystem* mOverlaySystem;
};

#endif /* GFXMGR_H_ */
