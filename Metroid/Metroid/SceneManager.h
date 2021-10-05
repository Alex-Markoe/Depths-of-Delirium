//GUARD
#ifndef __SCENEMANAGER_H_INCLUDED__
#define __SCENEMANAGER_H_INCLUDED__

//FORWARD DEPENDENCIES
class World;

//INCLUDE DEPENDENCIES
#include "TitleScene.h";
#include "MainScene.h";
#include "PauseScene.h";

enum SCENE {
	TITLE,
	GAME,
	PAUSE
};

class SceneManager {
public:
	static SceneManager& instance() {
		static SceneManager* instance = new SceneManager();
		return *instance;
	};
	~SceneManager();
	void SetWorld(World* _world);
	void ChangeScene(int index);
	void LoadGameData();

private:
	SceneManager();
	
	World* world;
	Scene* scenes[3];
	const int TOTAL_SCENES = 3;
};

#endif //__SCENEMANAGER_H_INCLUDED__