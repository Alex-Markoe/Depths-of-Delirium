#include "ToTitleCommand.h"
#include "SceneManager.h"
#include "FileManager.h"

//Return to title
void ToTitleCommand::Execute() {
	SceneManager::instance().ChangeScene(TITLE);
	FileManager::instance().WriteSave();
}