//GUARD
#ifndef __BOSSBEHAVIOR_H_INCLUDED__
#define __BOSSBEHAVIOR_H_INCLUDED__

//FORWARD DEPENDENCIES
class AnimationComponent;
class PhysicsComponent;
class CollisionComponent;

//INCLUDE DEPENDENCIES

class BossBehavior{
public:
	BossBehavior();
	~BossBehavior();
	void Init(AnimationComponent* _anim, PhysicsComponent* _physics, CollisionComponent* _collider);
	void Update();

protected:
	AnimationComponent* anim;
	PhysicsComponent* physics;
	CollisionComponent* collider;
};

#endif //__BOSSBEHAVIOR_H_INCLUDED__