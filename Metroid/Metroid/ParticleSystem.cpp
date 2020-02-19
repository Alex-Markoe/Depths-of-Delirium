#include "ParticleSystem.h"

//Constructor, use half of range, 0 for looping system
ParticleSystem::ParticleSystem(SDL_Renderer* gRenderer, SDL_Point speed, 
	SDL_Point initPosition, SDL_Point gravity, PROJECTILE_TYPE systemType,
	int range, int angle, int lifetime, int spawnFrequency, int systemLifetime) 
	: ProjectileManager(gRenderer){
	init_Speed = speed;
	init_Angle = angle;
	grav = gravity;
	angle_Range = range;
	type = systemType;
	particle_Lifetime = lifetime;
	spawn_Frequency = spawnFrequency;
	spawn_Timer = SDL_GetTicks() + spawnFrequency;
	if (systemLifetime > 0) system_Lifetime = SDL_GetTicks() + systemLifetime;
}

//Destructor
ParticleSystem::~ParticleSystem(){}

//Override of update specific for particle systems
void ParticleSystem::Update(){
	for (unsigned i = 0; i < projectiles.size(); i++) {
		if (grav.y != 0) projectiles[i]->ApplyForce(grav);
		projectiles[i]->Update();
		if (!projectiles[i]->active) Remove(projectiles[i]);
	}
	//Spawn new particle
	if (spawn_Timer < SDL_GetTicks()) {
		int sign = rand() % 2;
		if (sign > 0) sign = 1;
		else sign = -1;

		int range = rand() % (angle_Range / 2) * sign;
		float angle = init_Angle + range;
		SDL_Point t_F{init_Speed.x * cos(angle), init_Speed.y * sin(angle)};
		Add(position, t_F, type, false, angle);
	}
}

//Spawn in particles according to the given guidelines of the system
void ParticleSystem::Add(SDL_Rect pos, SDL_Point force, PROJECTILE_TYPE type, bool playerOwned, float angle) {
	SDL_Rect source;
	switch (type) {
	case FIRE:
		source = SDL_Rect{ 0,0,0,0 };
		break;
	case ICE:
		source = SDL_Rect{ 0,0,0,0 };
		break;
	case PUSH:
		source = SDL_Rect{ 0,0,0,0 };
		break;
	}

	Projectile* proj = new Projectile(SDL_Rect{pos.x, pos.y, source.x, source.y}, 
		source, SDL_Point{}, force, type, playerOwned, angle, particle_Lifetime);
	proj->loadTexture("Assets/", gRenderer);
}

//Update the central position of the particle system
void ParticleSystem::UpdatePosition(SDL_Rect new_Position) {
	position = new_Position;
}