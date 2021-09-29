#include "ParticleSystemComponent.h"

//Constructor, use half of range, 0 for looping system
ParticleSystemComponent::ParticleSystemComponent() {
	/*position = SDL_Rect{ initPosition.x, initPosition.y, 0, 0 };
	init_Speed = speed;
	init_Angle = angle;
	grav = gravity;
	angle_Range = range;
	type = systemType;
	particle_Lifetime = lifetime;
	spawn_Frequency = spawnFrequency;
	spawn_Timer = SDL_GetTicks() + spawnFrequency;
	if (systemLifetime > 0) system_Lifetime = SDL_GetTicks() + systemLifetime;*/
}

//Override of update specific for particle systems
void ParticleSystemComponent::Update(){
	//for (unsigned i = 0; i < projectiles.size(); i++) {
	//	if (grav.y != 0) projectiles[i]->ApplyForce(grav);
	//	projectiles[i]->Update();
	//	if (!projectiles[i]->active) Remove(projectiles[i]);
	//}
	////Spawn new particle
	//if (spawn_Timer < SDL_GetTicks()) {
	//	int sign = rand() % 2;
	//	if (sign > 0) sign = 1;
	//	else sign = -1;

	//	int range = rand() % (angle_Range / 2) * sign;
	//	float angle = init_Angle + range;
	//	SDL_Point t_F{init_Speed.x * cos(angle), init_Speed.y * sin(angle)};
	//	Add(position, t_F, type, false, angle);
	//	spawn_Timer = SDL_GetTicks() + spawn_Frequency;
	//}
}