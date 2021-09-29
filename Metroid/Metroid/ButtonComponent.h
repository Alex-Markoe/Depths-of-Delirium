//GUARD
#ifndef __BUTTONCOMPONENT_H_INCLUDED__
#define __BUTTONCOMPONENT_H_INCLUDED__

//FORWARD DEPENDENCIES
#include "Component.h"

class ButtonComponent : public Component {
public:
	ButtonComponent();
	~ButtonComponent();
	void Update() override;
	void OnClick();
};

#endif //__BUTTONCOMPONENT_H_INCLUDED__