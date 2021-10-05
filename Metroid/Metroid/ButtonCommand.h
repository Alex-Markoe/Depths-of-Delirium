//GUARD
#ifndef __BUTTONCOMMAND_H_INCLUDED__
#define __BUTTONCOMMAND_H_INCLUDED__

class ButtonCommand{
public:
	ButtonCommand() {};
	~ButtonCommand() {};
	virtual void Execute() {};
};

#endif //__BUTTONCOMMAND_H_INCLUDED__