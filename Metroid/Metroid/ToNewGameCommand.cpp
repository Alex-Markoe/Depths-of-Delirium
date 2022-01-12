#include "ToNewGameCommand.h"
#include "FileManager.h"
#include "SceneManager.h"

//Make new game
void ToNewGameCommand::Execute() {
	FileManager::instance().CreateSave();
	FileManager::instance().ReadSave();
	SceneManager::instance().ChangeScene(GAME);
	SceneManager::instance().LoadGameData();
}