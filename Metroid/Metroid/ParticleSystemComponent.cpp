#include "ParticleSystemComponent.h"
#include "GameObject.h"
#include "TextureDatabase.h"
#include "ParticleSystemParams.h"

//COMPONENTS
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "AnimationComponent.h"
#include "ParticleComponent.h"

//BEHAVIORS
#include "StraightParticleBehavior.h"

//Constructor, use 0 lifetime for looping system
ParticleSystemComponent::ParticleSystemComponent(ParticleSystemParams params, GameObject* _obj) {
	//Initialize variables
	max_particles = params.max_particles;
	system_lifetime = params.system_lifetime;
	Modify(params);
	behavior = params.behavior;
	obj = _obj;
	start_index = 0;
	particle_count = 0;

	//Initialize particles
	particles = new GameObject[max_particles];
	timers = new Uint32[max_particles];
	int src_y = 0;
	ParticleBehavior* p_behavior;
	for (unsigned i = 0; i < max_particles; i++) {
		//Get a random particle color
		src_y = rand() % 3;
		//Setup components
		particles[i].physics = new PhysicsComponent({ 50, 50 }, params.decell, params.decell);
		particles[i].renderer = new RenderComponent(TextureDatabase::instance().GetTexture(params.type), {0, src_y * 8, 8, 8}, 0); //SRCERECT/TEXTURE
		particles[i].animator = new AnimationComponent(particles[i].renderer);
		//particles[i].animator->SetFrameRate(14);
		particles[i].animator->SetAnimationSource(24, particles[i].renderer->source_rect.y, 0, false);
		//Particle behavior setup
		p_behavior = GetBehavior();
		p_behavior->SetPhysics(particles[i].physics);
		particles[i].AddComponent(new ParticleComponent(particles[i].physics, p_behavior));
		particles[i].Init({obj->position.x, obj->position.y, 8, 8}, true);
		timers[i] = 0;
		//add particle as child
		obj->AddChild(&particles[i]);
	}

	//Spawn some stuff
	system_timer = SDL_GetTicks();
	SpawnParticle();
}
//Destructor
ParticleSystemComponent::~ParticleSystemComponent() {
	delete[] particles;
	delete[] timers;
	obj = nullptr;
}
//Reset the system
void ParticleSystemComponent::Reset() {
	for (unsigned i = 0; i < max_particles; i++) {
		timers[i] = 0;
	}
	start_index = 0;
	particle_count = 0;
	spawn_timer = 0;
}
//Modify select variables, so it can be changed at runtime
void ParticleSystemComponent::Modify(ParticleSystemParams params) {
	particle_lifetime = params.particle_lifetime;
	spawn_interval = params.spawn_interval;
	particle_spawn_rate = params.particle_spawn_rate;
	random_spawn = params.random;
	reverse = params.reverse;
	grav = params.grav;
	origin_offset = params.origin_offset;
	speed = params.speed;
	rotation_rate = params.rotation_rate;
	SetAngle(params.init_angle, params.angle_range);
}

//Override of update specific for particle systems
void ParticleSystemComponent::Update(){
	if (system_lifetime != 0 && SDL_GetTicks() >= system_timer + system_lifetime) return; //system has run out
	if (SDL_GetTicks() >= spawn_timer + spawn_interval && particle_count < max_particles) {
		SpawnParticle();
	}

	//variables for position in array
	int to_destroy = 0;
	int next_start = start_index;
	for (unsigned i = 0; i < particle_count; i++) {
		int index = (i + start_index + particle_count) % max_particles; //ge the index
		//particle is dead
		if (SDL_GetTicks() >= timers[index] + particle_lifetime) {
			//RESET PARTICLE POSITION/PHYSICS/ANIMATION
			particles[index].physics->ResetKinematics(true, true);
			particles[index].animator->SetAnimationSource(24, particles[index].renderer->source_rect.y, 0, false);
			timers[index] = 0;
			to_destroy++;
			next_start++;
			if (next_start >= max_particles) next_start = 0;
		}
		//Others change some stuff
		else {
			particles[index].physics->ApplyForce(grav.x, grav.y);
			particles[index].renderer->SetAngle(particles[index].renderer->GetAngle() + rotation_rate);
		}
	}

	//update position/particle count
	particle_count -= to_destroy;
	start_index = next_start;
}
//"Spawn" a new particle by reseting parameters for an existing particle
void ParticleSystemComponent::SpawnParticle() {
	int to_add = 0;
	ParticleComponent* p = nullptr;
	for (unsigned i = 0; i < particle_spawn_rate; i++) {
		int index = (i + start_index + particle_count) % max_particles; //get the next index
		if (timers[index] != 0) break;
		GetNextSpawn();
		//SETUP PARTICLE PHYSICS/ANIMATION
		particles[index].position = { obj->position.x + (obj->position.w / 2) + (int)(origin_offset.x * dir_x), obj->position.y + (obj->position.h / 2) + (int)(origin_offset.y * dir_y), 8, 8 };
		particles[index].animator->SetAnimationSource(0, particles[index].renderer->source_rect.y, 2, false);
		particles[index].animator->SetFrame(0);
		p = (ParticleComponent*)particles[index].components[0];
		p->SetVelocity({ (int)(dir_x * speed), (int)(dir_y * speed) });
		timers[index] = SDL_GetTicks();
		to_add++;
	}

	//update particle count
	particle_count += to_add;
	spawn_timer = SDL_GetTicks();
}
//Get the next spawn location
void ParticleSystemComponent::GetNextSpawn() {
	//Random based spawning
	if (random_spawn) {
		current_angle = rand() % angle_range + init_angle;
	}
	//Spawn based on time and angle
	else {
		int interval = angle_range / particle_spawn_rate;
		current_angle += interval * angle_range_sign;
		if (current_angle >= init_angle + angle_range || current_angle <= init_angle) {
			if (reverse) angle_range_sign *= -1;
			else current_angle = init_angle;
		}
	}
	//Update directions
	dir_x = cos(current_angle * M_PI / 180.0f);
	dir_y = sin(current_angle * M_PI / 180.0f);
}
//Change the angle at will
void ParticleSystemComponent::SetAngle(int angle, int _angle_range) {
	init_angle = angle;
	angle_range = abs(_angle_range);
	angle_range_sign = _angle_range / abs(_angle_range);
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