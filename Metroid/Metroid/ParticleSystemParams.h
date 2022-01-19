//GUARD
#ifndef __PARTICLESYSTEMPARAMS_H_INCLUDED__
#define __PARTICLESYSTEMPARAMS_H_INCLUDED__

//FORWARD DEPENDENCIES

//INCLUDE DEPENDENCIES
#include <SDL.h>

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

class ParticleSystemParams {
public:
	ParticleSystemParams(int _system_lifetime, int _max_particles, int _particle_lifetime, int _spawn_interval, int _particle_spawn_rate, int _init_angle, int _angle_range, bool _random, bool _reverse,
		float _decell, int _speed, float _rotation_rate, SDL_Point _grav, SDL_Point _origin_offset, PARTICLE_TYPE _type, BEHAVIOR_TYPE _behavior);

	int system_lifetime;
	int max_particles; 
	int particle_lifetime;
	int spawn_interval;
	int particle_spawn_rate; 
	int init_angle; 
	int angle_range; 
	bool random; 
	bool reverse;
	float decell;
	int speed; 
	float rotation_rate; 
	SDL_Point grav; 
	SDL_Point origin_offset; 
	PARTICLE_TYPE type; 
	BEHAVIOR_TYPE behavior;
};

#endif //__PARTICLESYSTEMPARAMS_H_INCLUDED__