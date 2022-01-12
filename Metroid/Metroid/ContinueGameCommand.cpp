#include "ContinueGameCommand.h"
#include "SceneManager.h"
#include "FileManager.h"

//Read in save data and change the scene
void ContinueGameCommand::Execute() {
	FileManager::instance().ReadSave();
	SceneManager::instance().ChangeScene(GAME);
	SceneManager::instance().LoadGameData();
}