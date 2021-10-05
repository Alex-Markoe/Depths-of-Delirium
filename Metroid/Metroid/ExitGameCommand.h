//GUARD
#ifndef __EXITGAMECOMMAND_H_INCLUDED__
#define __EXITGAMECOMMAND_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "ButtonCommand.h"

class ExitGameCommand : public ButtonCommand {
public:
	ExitGameCommand() {};
	~ExitGameCommand() {};
	void Execute() override;
};

#endif //__EXITGAMECOMMAND_H_INCLUDED__