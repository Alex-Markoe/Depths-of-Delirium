//GUARD
#ifndef __UNPAUSECOMMAND_H_INCLUDED__
#define __UNPAUSECOMMAND_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "ButtonCommand.h"

//Unpause the game
class UnpauseCommand : public ButtonCommand {
public:
	UnpauseCommand() {};
	~UnpauseCommand() {};
	void Execute() override;
};

#endif //__UNPAUSECOMMAND_H_INCLUDED__