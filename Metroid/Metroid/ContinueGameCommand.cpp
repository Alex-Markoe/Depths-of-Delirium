#include "ContinueGameCommand.h"

void ContinueGameCommand::Execute() {
	FileManager::instance().ReadSave();
	SceneManager::instance().ChangeScene(GAME);
	SceneManager::instance().LoadGameData();
}