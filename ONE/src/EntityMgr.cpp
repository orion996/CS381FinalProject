/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <EntityMgr.h>
#include <Engine.h>

EntityMgr::EntityMgr(Engine *eng): Mgr(eng){
	selectedEntity = 0;
	count = 0;
	selectedEntityIndex = -1;
}

EntityMgr::~EntityMgr(){

}

void EntityMgr::CreateEntity(std::string meshfilename, Ogre::Vector3 pos){
	Entity381 *ent = new Entity381(this->engine, meshfilename, pos, count);
	count++;
	entities.push_back(ent);
}

void EntityMgr::CreateDDG51(Ogre::Vector3 pos){
	DDG51 *ent = new DDG51(this->engine, "ddg51.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::CreateCarrier(Ogre::Vector3 pos){
	Carrier *ent = new Carrier(this->engine, "cvn68.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::CreateSpeedBoat(Ogre::Vector3 pos){
	SpeedBoat *ent = new SpeedBoat(this->engine, "cigarette.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}
void EntityMgr::CreateFrigate(Ogre::Vector3 pos){
	Frigate *ent = new Frigate(this->engine, "sleek.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}
void EntityMgr::CreateAlien(Ogre::Vector3 pos){
	Alien *ent = new Alien(this->engine, "alienship.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}
void EntityMgr::CreateBanshee(Ogre::Vector3 pos){
	Banshee *ent = new Banshee(this->engine, "banshee.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}


void EntityMgr::SelectNextEntity(){
	if(selectedEntityIndex >= count - 1) {
		selectedEntityIndex = 0;
	} else {
		selectedEntityIndex++;
	}
	if(selectedEntity != 0)
		selectedEntity->isSelected = false;
	selectedEntity = entities[selectedEntityIndex];
	selectedEntity->isSelected = true;


}

void EntityMgr::SelectEntity(int id)
{
	selectedEntity->isSelected = false;
	selectedEntityIndex = id;

	entities[selectedEntityIndex]->isSelected = true;
	selectedEntity = entities[selectedEntityIndex];
}


void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes entType, Ogre::Vector3 pos){

	switch(entType){
	case DDG51Type:
		CreateDDG51(pos);
		break;
	case CarrierType:
		CreateCarrier(pos);
		break;
	case SpeedBoatType:
		CreateSpeedBoat(pos);
		break;
	case FrigateType:
		CreateFrigate(pos);
		break;
	case AlienType:
		CreateAlien(pos);
		break;
	case BansheeType:
		CreateBanshee(pos);
		break;
	default:
		CreateEntity("robot.mesh", pos);
		break;
	}
}

void EntityMgr::Tick(float dt){
	for(int i = 0; i < count; i++){
		entities[i]->Tick(dt);
	}
}
