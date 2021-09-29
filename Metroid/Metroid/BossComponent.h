//GUARD
#ifndef __BOSSCOMPONENT_H_INCLUDED__
#define __BOSSCOMPONENT_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "Component.h"

//LOGIC FOR BOSS AI
class BossComponent : public Component {
public:
	BossComponent();
	~BossComponent();
	void Update() override;
};

#endif //__BOSSCOMPONENT_H_INCLUDED__