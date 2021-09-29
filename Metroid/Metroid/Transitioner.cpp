#include "Transitioner.h"

//Constructor
Transitioner::Transitioner(){
	to_open = "Levels/room1.txt";
	ReadSave();
	ReadFile();
}
//Destructor
Transitioner::~Transitioner(){
	for (unsigned i = 0; i < 4; i++) {
		if (boss_data[i] != nullptr) delete boss_data[i];
	}
}

//CREATE SAVED DATA
void Transitioner::CreateSave() {
	std::ofstream save_file_create;
	save_file_create.open("Levels/save_data.txt", std::ios::out | std::ios::beg);
	if (save_file_create.is_open()) {
		save_file_create << "Levels/room1.txt\n";
		save_file_create << "TTTT";
		save_file_create.close();
	}
}
//READ IN SAVED DATA
void Transitioner::ReadSave(){
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

			}
			else {
				boss_data[i] = nullptr;
			}
		}

		save_file_read.close();
	}
}
//WRITE SAVED DATA
void Transitioner::WriteSave() {

}

//READ ROOM DATA IN 
bool Transitioner::ReadFile() {
	std::ifstream room_file_read;
	bool boss_room = false;
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
		enter_position = SDL_Point{ x, y };
		//READ EXIT POSITION
		std::getline(room_file_read, data);
		x = std::stoi(data);
		std::getline(room_file_read, data);
		y = std::stoi(data);
		exit_position = SDL_Point{ x, y };
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

BossComponent* Transitioner::GetBossData() { return boss_data[setting]; }
void Transitioner::ToNext() { to_open = next_room; }
void Transitioner::ToPrevious() { to_open = previous_room; }