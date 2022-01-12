#include "UnpauseCommand.h"
#include "SceneManager.h"

//Unpause
void UnpauseCommand::Execute() {
	SceneManager::instance().ChangeScene(GAME);
}