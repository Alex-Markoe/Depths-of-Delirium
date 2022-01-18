#include "ParticleSystemComponent.h"
#include "GameObject.h"
#include "TextureDatabase.h"

//COMPONENTS
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "AnimationComponent.h"
#include "ParticleComponent.h"

//BEHAVIORS
#include "StraightParticleBehavior.h"

//Constructor, use half of range, 0 for looping system
ParticleSystemComponent::ParticleSystemComponent(int _system_lifetime, int _max_particles, int _particle_lifetime, int _spawn_interval, int _particle_spawn_rate, int _init_angle, int _angle_range, bool _random,
	float decell, float _speed, SDL_Point _grav, SDL_Point _origin_offset, GameObject* _obj, PARTICLE_TYPE _type, BEHAVIOR_TYPE _behavior) {
	max_particles = _max_particles;
	system_lifetime = _system_lifetime;
	particle_lifetime = _particle_lifetime;
	spawn_interval = _spawn_interval;
	particle_spawn_rate = _particle_spawn_rate;
	init_angle = _init_angle;
	angle_range = abs(_angle_range);
	angle_range_sign = _angle_range / abs(_angle_range);
	random_spawn = _random;
	grav = _grav;
	origin_offset = _origin_offset;
	obj = _obj;
	speed = _speed;
	behavior = _behavior;
	start_index = 0;
	particle_count = 0;

	particles = new GameObject[max_particles];
	timers = new Uint32[max_particles];
	ParticleBehavior* p_behavior;
	for (int i = 0; i < max_particles; i++) {
		particles[i].physics = new PhysicsComponent({ 50, 50 }, decell, decell);
		particles[i].renderer = new RenderComponent(TextureDatabase::instance().GetTexture(_type), {}, 0); //SRCERECT/TEXTURE
		particles[i].animator = new AnimationComponent(particles[i].renderer);
		p_behavior = GetBehavior();
		p_behavior->SetPhysics(particles[i].physics);
		particles[i].AddComponent(new ParticleComponent(particles[i].physics, p_behavior));
		particles[i].Init({obj->position.x + origin_offset.x, obj->position.y + origin_offset.y, 0, 0}, true);
		timers[i] = 0;
		obj->AddChild(&particles[i]);
	}

	system_timer = SDL_GetTicks();
	SpawnParticle();
}
//Destructor
ParticleSystemComponent::~ParticleSystemComponent() {
	delete[] particles;
	delete[] timers;
	obj = nullptr;
}

//Override of update specific for particle systems
void ParticleSystemComponent::Update(){
	if (system_timer != 0 && SDL_GetTicks() >= system_timer + system_lifetime) return; //system has run out
	if (SDL_GetTicks() >= spawn_timer + spawn_interval && particle_count < max_particles) {
		SpawnParticle();
	}

	int to_destroy = 0;
	int next_start = start_index;
	for (int i = 0; i < particle_count; i++) {
		int index = (i + start_index + particle_count) % max_particles;
		//particle is dead
		if (timers[i] + particle_lifetime >= SDL_GetTicks()) {
			//RESET PARTICLE POSITION/PHYSICS/ANIMATION
			particles[i].position = { obj->position.x + origin_offset.x, obj->position.y + origin_offset.y, 0, 0 };
			particles[i].physics->ResetKinematics();
			particles[i].animator->SetAnimationSource(0, 0, 0);
			timers[i] = 0;
			to_destroy++;
			next_start++;
			if (next_start >= max_particles) next_start = 0;
		}
		else {
			particles[i].physics->ApplyForce(grav.x, grav.y);
		}
	}

	particle_count -= to_destroy;
	start_index = next_start;
}
//"Spawn" a new particle by reseting parameters for an existing particle
void ParticleSystemComponent::SpawnParticle() {
	int to_add = 0;
	for (int i = 0; i < particle_spawn_rate; i++) {
		int index = (i + start_index + particle_count) % max_particles;
		if (timers[index] != 0) break;
		GetNextSpawn();
		//SETUP PARTICLE PHYSICS/ANIMATION
		particles[i].animator->SetAnimationSource(0, 0, 0);
		particles[i].animator->SetFrame(0);
		timers[index] = SDL_GetTicks();
		to_add++;
	}

	particle_count += to_add;
	spawn_timer = SDL_GetTicks();
}
//Get the next spawn location
void ParticleSystemComponent::GetNextSpawn() {
	if (random_spawn) {
		current_angle = rand() % angle_range + init_angle;
	}
	else {
		int interval = angle_range / particle_spawn_rate;
		current_angle += interval * angle_range_sign;
		if (current_angle >= init_angle + angle_range || current_angle <= init_angle) angle_range_sign *= -1;
	}
	direction = { cos(current_angle * M_PI / 180.0f), sin(current_angle * M_PI / 180.0f) };
}
//Get the behavior for this system
ParticleBehavior* ParticleSystemComponent::GetBehavior() {
	switch (behavior) {
	case STRAIGHT:
		return new ParticleBehavior();
	case STRAIGHT_ACCELERATING:
		return new StraightParticleBehavior();
	}
}