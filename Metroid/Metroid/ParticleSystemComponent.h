//GUARD
#ifndef __PARTICLESYSTEMCOMPONENT_H_INCLUDED__
#define __PARTICLESYSTEMCOMPONENT_H_INCLUDED__

//FORWARD DEPENDENCIES
class GameObject;
class ParticleBehavior;
class ParticleSystemParams;

//INCLUDE DEPENDENCIES
#include "Component.h"

//ATTACHABLE PARTICLE SYSTEM
class ParticleSystemComponent : public Component {
public:
	ParticleSystemComponent(ParticleSystemParams params, GameObject* _obj);
	~ParticleSystemComponent();
	void Update() override;
	void Reset();
	void SetAngle(int angle, int _angle_range);
	void Modify(ParticleSystemParams params);

private:
	void SpawnParticle();
	void GetNextSpawn();
	ParticleBehavior* GetBehavior();

	GameObject* particles; //particle array
	GameObject* obj; //Parent object
	SDL_Point origin_offset; //Range of position from origin
	SDL_Point grav; //gravity to be applied
	Uint32 spawn_timer; //timer between spawns
	Uint32 system_timer;
	Uint32* timers;
	int behavior; //enum for behavior

	//ANGLE BASED VARIABLES
	int init_angle;
	int angle_range;
	int angle_range_sign;
	int current_angle;

	//system variable
	int max_particles;
	int particle_spawn_rate; //particles spawned per spawn interval
	int particle_lifetime; 
	int spawn_interval; //time between particle spawn
	int system_lifetime;
	int speed;
	float rotation_rate;
	float dir_x;
	float dir_y;
	bool random_spawn;
	bool reverse;

	//For iterating through particle/timer array
	int start_index;
	int particle_count;
};

#endif //__PARTICLESYSTEMCOMPONENT_H_INCLUDED__