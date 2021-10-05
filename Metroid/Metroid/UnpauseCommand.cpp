#include "UnpauseCommand.h"

void UnpauseCommand::Execute() {
	SceneManager::instance().ChangeScene(GAME);
}