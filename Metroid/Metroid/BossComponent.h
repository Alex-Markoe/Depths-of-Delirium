//GUARD
#ifndef __BOSSCOMPONENT_H_INCLUDED__
#define __BOSSCOMPONENT_H_INCLUDED__

//FORWARD DEPENDENCIES
class BossBehavior;

//INCLUDE DEPENDENCIES
#include "Component.h"

//LOGIC FOR BOSS AI
class BossComponent : public Component {
public:
	BossComponent();
	~BossComponent();
	void Update() override;
	void SetBehavior(BossBehavior* _behavior);

private:
	BossBehavior* behavior;
};

#endif //__BOSSCOMPONENT_H_INCLUDED__