//GUARD
#ifndef __CONTINUEGAMECOMMAND_H_INCLUDED__
#define __CONTINUEGAMECOMMAND_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "ButtonCommand.h"

//Continue game button command
class ContinueGameCommand : public ButtonCommand {
public:
	ContinueGameCommand() {};
	~ContinueGameCommand() {};
	void Execute() override;
};

#endif //__CONTINUEGAMECOMMAND_H_INCLUDED__