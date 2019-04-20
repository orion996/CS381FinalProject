#ifndef __EntityMgr_h_
#define __EntityMgr_h_

#include <vector>
#include <Mgr.h>
#include <Entity381.h>
#include <Types381.h>

class EntityMgr: public Mgr {
public:
  EntityMgr(Engine *engine);
  virtual ~EntityMgr();

  //Engine *engine;

  std::vector<Entity381*> entities;
  Entity381* selectedEntity;
  int selectedEntityIndex;


  //Ogre::SceneManager *sceneMgr;

  void CreateEntityOfTypeAtPosition(EntityTypes type, Ogre::Vector3 pos, bool isHat, Entity381* body);
  void SelectNextEntity();
  void SelectEntity(int id);
  Entity381* GetEntityAt(int id);

  void Tick(float dt);

protected:

private:
  void CreateEntity(std::string meshfilename, Ogre::Vector3 pos);
  void CreateDDG51(Ogre::Vector3 pos);
  void CreateCarrier(Ogre::Vector3 pos);
  void CreateSpeedBoat(Ogre::Vector3 pos, bool isHat, Entity381* body);
  void CreateFrigate(Ogre::Vector3 pos);
  void CreateAlien(Ogre::Vector3 pos);
  void CreateBanshee(Ogre::Vector3 pos);
  int count;

};

#endif // #ifndef __EntityMgr_h_
