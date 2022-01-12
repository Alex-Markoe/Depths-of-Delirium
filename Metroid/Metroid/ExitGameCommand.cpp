#include "ExitGameCommand.h"
#include "SceneManager.h"

//quit the game :)
void ExitGameCommand::Execute() {
	SceneManager::instance().Quit();
}