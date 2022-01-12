//GUARD
#ifndef __TOTITLECOMMAND_H_INCLUDED__
#define __TOTITLECOMMAND_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "ButtonCommand.h"

//Return to title screen
class ToTitleCommand : public ButtonCommand {
public:
	ToTitleCommand() {};
	~ToTitleCommand() {};
	void Execute() override;
};

#endif //__TOTITLECOMMAND_H_INCLUDED__