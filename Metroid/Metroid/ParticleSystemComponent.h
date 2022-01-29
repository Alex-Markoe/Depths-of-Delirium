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
	GameObject* obj;
	SDL_Point origin_offset;
	SDL_Point grav;
	Uint32 spawn_timer;
	Uint32 system_timer;
	Uint32* timers;
	int behavior;

	int init_angle;
	int angle_range;
	int angle_range_sign;
	int current_angle;

	int max_particles;
	int particle_spawn_rate;
	int particle_lifetime;
	int spawn_interval;
	int system_lifetime;
	int speed;
	float rotation_rate;
	float dir_x;
	float dir_y;
	bool random_spawn;
	bool reverse;

	int start_index;
	int particle_count;
};

#endif //__PARTICLESYSTEMCOMPONENT_H_INCLUDED__