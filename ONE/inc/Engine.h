/*
 * Engine.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef ENGINE_H_
#define ENGINE_H_

class EntityMgr;
class GameMgr;
class GfxMgr;
class InputMgr;
#include <SoundMgr.h>


class Engine {
private:
public:
	Engine();
	virtual ~Engine();

	OgreSND::SoundMgr* soundMgr;
	EntityMgr *entityMgr;
	GameMgr   *gameMgr;
	GfxMgr    *gfxMgr;
	InputMgr  *inputMgr;

	void Init();
	void Run();
	void TickAll(float dt);
	void Cleanup();

	bool keepRunning;
	bool gameStart;
};

#endif /* ENGINE_H_ */
