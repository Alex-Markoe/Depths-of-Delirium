#include "ToTitleCommand.h"

void ToTitleCommand::Execute() {
	SceneManager::instance().ChangeScene(TITLE);
	FileManager::instance().WriteSave();
}