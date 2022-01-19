#include "ParticleSystemParams.h"

ParticleSystemParams::ParticleSystemParams(int _system_lifetime, int _max_particles, int _particle_lifetime, int _spawn_interval, int _particle_spawn_rate, int _init_angle, int _angle_range, 
							bool _random, bool _reverse, float _decell, int _speed, float _rotation_rate, SDL_Point _grav, SDL_Point _origin_offset, PARTICLE_TYPE _type, BEHAVIOR_TYPE _behavior) {
	system_lifetime = _system_lifetime;
	max_particles = _max_particles;
	particle_lifetime = _particle_lifetime;
	spawn_interval = _spawn_interval;
	particle_spawn_rate = _particle_spawn_rate;
	init_angle = _init_angle;
	angle_range = _angle_range;
	random = _random;
	reverse = _reverse;
	decell = _decell;
	speed = _speed;
	rotation_rate = _rotation_rate;
	grav = _grav;
	origin_offset = _origin_offset;
	type = _type;
	behavior = _behavior;
}