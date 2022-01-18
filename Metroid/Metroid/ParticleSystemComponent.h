//GUARD
#ifndef __PARTICLESYSTEMCOMPONENT_H_INCLUDED__
#define __PARTICLESYSTEMCOMPONENT_H_INCLUDED__

//FORWARD DEPENDENCIES
class GameObject;
class ParticleBehavior;

//INCLUDE DEPENDENCIES
#include "Component.h"

//ENUM TO REPRESENT TYPE
//OF PARTICLE TO SPAWN
enum PARTICLE_TYPE {
	FIRE_PARTICLE = 7,
	ICE_PARTICLE = 8,
	GRAVEYARD_PARTICLE = 9,
	SHADOW_PARTICLE = 10,
	ELDRITCH_PARTICLE = 11
};

enum BEHAVIOR_TYPE {
	STRAIGHT,
	STRAIGHT_ACCELERATING
};

//ATTACHABLE PARTICLE SYSTEM
class ParticleSystemComponent : public Component {
public:
	ParticleSystemComponent(int _system_lifetime, int _max_particles, int _particle_lifetime, int _spawn_interval, int _particle_spawn_rate, int _init_angle, int _angle_range, bool _random, float decell,
							float _speed, SDL_Point _grav, SDL_Point _origin_offset, GameObject* _obj, PARTICLE_TYPE _type, BEHAVIOR_TYPE _behavior);
	~ParticleSystemComponent();
	void Update() override;

private:
	void SpawnParticle();
	void GetNextSpawn();
	ParticleBehavior* GetBehavior();

	GameObject* particles; //particle array
	GameObject* obj;
	SDL_Point origin_offset;
	SDL_Point grav;
	SDL_Point direction;
	Uint32 spawn_timer;
	Uint32 system_timer;
	Uint32* timers;
	BEHAVIOR_TYPE behavior;

	int init_angle;
	int angle_range;
	int angle_range_sign;
	int current_angle;

	int max_particles;
	int particle_spawn_rate;
	int particle_lifetime;
	int spawn_interval;
	int system_lifetime;
	float speed;
	bool random_spawn;

	int start_index;
	int particle_count;
};

#endif //__PARTICLESYSTEMCOMPONENT_H_INCLUDED__