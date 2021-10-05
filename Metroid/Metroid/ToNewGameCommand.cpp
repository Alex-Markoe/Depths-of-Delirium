#include "ToNewGameCommand.h"

void ToNewGameCommand::Execute() {
	FileManager::instance().CreateSave();
	FileManager::instance().ReadSave();
	SceneManager::instance().ChangeScene(GAME);
	SceneManager::instance().LoadGameData();
}