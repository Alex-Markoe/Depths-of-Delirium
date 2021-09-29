//GUARD
#ifndef __TRANSITIONER_H_INCLUDED__
#define __TRANSITIONER_H_INCLUDED__

//FORWARD DEPENDENCIES
class BossComponent;

//INCLUDE DEPENDENCIES
#include <SDL.h>
#include <string>
#include <fstream>
#include <iostream>

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
class Transitioner{
public:
	Transitioner();
	~Transitioner();
	void CreateSave();
	void ReadSave();
	void WriteSave();
	void ToPrevious();
	void ToNext();
	bool ReadFile();
	BossComponent* GetBossData();

	SDL_Point enter_position;
	SDL_Point exit_position;
	std::string room_file_name; //file to be loaded by the world
	std::string previous_room; //room file name of previous
	std::string next_room; //room file name of next
	SETTING setting;

private:
	std::string to_open; //next room file to open
	BossComponent* boss_data[4];
};

#endif //__TRANSITIONER_H_INCLUDED__