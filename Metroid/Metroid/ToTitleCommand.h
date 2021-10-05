//GUARD
#ifndef __TOTITLECOMMAND_H_INCLUDED__
#define __TOTITLECOMMAND_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "ButtonCommand.h"
#include "SceneManager.h"

class ToTitleCommand : public ButtonCommand {
public:
	ToTitleCommand() {};
	~ToTitleCommand() {};
	void Execute() override;
};

#endif //__TOTITLECOMMAND_H_INCLUDED__