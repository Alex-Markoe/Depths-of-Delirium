#include "FileManager.h"
#include <fstream>
#include <iostream>

//Constructor
FileManager::FileManager(){
	next = true;
	boss_data = new bool[4];
}
//Destructor
FileManager::~FileManager(){
	delete[] boss_data;
}

//CREATE SAVED DATA
void FileManager::CreateSave() {
	std::ofstream save_file_create;
	save_file_create.open("Levels/save_data.txt", std::ios::out | std::ios::beg);
	if (save_file_create.is_open()) {
		save_file_create << "Levels/room1.txt\n"; //FIRST ROOM
		save_file_create << "TTTT"; //IF BOSS HAS BEEN DEFEATED OR NOT T FOR YES
		save_file_create.close();
	}
}
//READ IN SAVED DATA
void FileManager::ReadSave(){
	std::ifstream save_file_read;
	save_file_read.open("Levels/save_data.txt", std::ios::in | std::ios::beg);
	if (save_file_read.is_open()) {
		std::string data;
		//Read in last room
		std::getline(save_file_read, data);
		to_open = data;
		//Read in boss data
		std::getline(save_file_read, data);
		for (unsigned i = 0; i < 4; i++) {
			if (data[i] == 'T') {
				//CREATE BOSS DATA
			}
			else {
				boss_data[i] = false;
			}
		}

		save_file_read.close();
	}
}
//WRITE SAVED DATA
void FileManager::WriteSave() {
	std::ofstream save_file_create;
	save_file_create.open("Levels/save_data.txt", std::ios::out | std::ios::beg);
	if (save_file_create.is_open()) {
		//CHECK IF IN UNFINISHED BOSS
		if (boss_room && boss_data[setting]) {
			save_file_create << previous_room;
		}
		else {
			save_file_create << to_open;
		}

		//CHECK HOW MANY BOSSES HAVE BEEN DEFEATED/UNDEFEATED
		save_file_create << "\n";
		for (unsigned i = 0; i < 4; i++) {
			if (!boss_data[i]) {
				save_file_create << "F";
			}
			else {
				save_file_create << "T";
			}
		}
		save_file_create.close();
	}
}
//READ ROOM DATA IN 
bool FileManager::ReadFile() {
	std::ifstream room_file_read;
	boss_room = false;
	room_file_read.open(to_open, std::ios::in | std::ios::beg);
	if (room_file_read.is_open()) {
		std::string data;
		int x = 0, y = 0;
		//PREVIOUS ROOM FILE NAME
		std::getline(room_file_read, data);
		previous_room = data;
		//NEXT ROOM FILE NAME
		std::getline(room_file_read, data);
		next_room = data;
		//READ ENTER POSITION
		std::getline(room_file_read, data);
		x = std::stoi(data);
		std::getline(room_file_read, data);
		y = std::stoi(data);
		if (next) enter_position = SDL_Point{ x, y };
		//READ EXIT POSITION
		std::getline(room_file_read, data);
		x = std::stoi(data);
		std::getline(room_file_read, data);
		y = std::stoi(data);
		if (!next) enter_position = SDL_Point{ x, y };
		//READ ROOM FILE NAME
		std::getline(room_file_read, data);
		room_file_name = data;
		//READ SETTING
		std::getline(room_file_read, data);
		if (data[0] == 'I') {
			setting = ICE;
		}
		else if (data[0] == 'G') {
			setting = GRAVEYARD;
		}
		else if (data[0] == 'S') {
			setting = SHADOW;
		}
		else if (data[0] == 'E') {
			setting = ELDRITCH;
		}
		//READ BOSS DATA
		std::getline(room_file_read, data);
		if (data[0] != 'F') {
			boss_room = true;
		}

		room_file_read.close();
	}

	return boss_room;
}

//CHANGE ROOMS/GET BOSS DATA
int FileManager::GetBossData() { return setting; }
void FileManager::ToNext() { 
	to_open = next_room; 
	next = true;
}
void FileManager::ToPrevious() { 
	to_open = previous_room; 
	next = false;
}