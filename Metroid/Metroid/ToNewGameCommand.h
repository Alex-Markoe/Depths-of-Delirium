//GUARD
#ifndef __TONEWGAMECOMMAND_H_INCLUDED__
#define __TONEWGAMECOMMAND_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "ButtonCommand.h"
#include "SceneManager.h"

class ToNewGameCommand : public ButtonCommand {
public:
	ToNewGameCommand() {};
	~ToNewGameCommand() {};
	void Execute() override;
};

#endif //__TONEWGAMECOMMAND_H_INCLUDED__