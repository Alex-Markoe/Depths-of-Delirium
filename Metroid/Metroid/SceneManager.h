//GUARD
#ifndef __SCENEMANAGER_H_INCLUDED__
#define __SCENEMANAGER_H_INCLUDED__

//FORWARD DEPENDENCIES
class World;
class Scene;

//INCLUDE DEPENDENCIES

//ENUM REPRESENTING SCENES
//SELF-EXPLANATORY
enum SCENE {
	TITLE,
	GAME,
	PAUSE
};

//SCENE MANAGER SINGLETON
//HANDLES CHANGING SCENES AND DETERMING IF THE 
//GAME MUST BE EXITED
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
	void Quit();

	bool exit; //WETHER OR NOT THE GAME SHOULD BE EXITED

private:
	SceneManager();
	
	World* world;
	Scene* scenes[3];
	const int TOTAL_SCENES = 3;
};

#endif //__SCENEMANAGER_H_INCLUDED__