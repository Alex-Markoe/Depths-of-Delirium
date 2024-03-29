//GUARD
#ifndef __FILEMANAGER_H_INCLUDED__
#define __FILEMANAGER_H_INCLUDED__

//FORWARD DEPENDENCIES
class BossComponent;

//INCLUDE DEPENDENCIES
#include <SDL.h>
#include <string>

//REPRESENTATION OF THE SETTING FOR
//USE WHEN LOADING TEXTURES AND BOSS DATA
enum SETTING {
	ICE,
	GRAVEYARD,
	SHADOW,
	ELDRITCH
};

//TRANSITIONER CLASS
//READS IN ROOM DATA TO
//BE READ BY THE WORLD FOR
//LEVEL LOADING
class FileManager{
public:
	static FileManager& instance() {
		static FileManager* instance = new FileManager();
		return *instance;
	};
	~FileManager();
	void CreateSave();
	void ReadSave();
	void WriteSave();
	void ToPrevious();
	void ToNext();
	bool ReadFile();
	int GetBossData();

	SDL_Point enter_position;
	std::string room_file_name; //file to be loaded by the world
	std::string previous_room; //room file name of previous
	std::string next_room; //room file name of next
	SETTING setting;

private:
	FileManager();

	bool boss_room;
	bool next;
	std::string to_open; //next room file to open
	bool* boss_data;
};

#endif //__FILEMANAGER_H_INCLUDED__