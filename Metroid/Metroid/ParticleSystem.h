#pragma once
#include "ProjectileManager.h"

class ParticleSystem :
	public ProjectileManager
{
public:
	ParticleSystem(SDL_Renderer* gRenderer, SDL_Point init_Speed, SDL_Point initPosition,
				   SDL_Point gravity, PROJECTILE_TYPE systemType, int range, int angle,
				   int lifetime, int spawnFrequency, int systemLifetime);
	~ParticleSystem();
	void Update() override;
	void UpdatePosition(SDL_Rect new_Position);
	void Add(SDL_Rect pos, SDL_Point force, PROJECTILE_TYPE type, bool playerOwned, float angle) override;

private:
	PROJECTILE_TYPE type;
	SDL_Rect position;
	SDL_Point init_Speed;
	SDL_Point grav;
	Uint32 spawn_Timer;
	Uint32 system_Timer = 0;
	int init_Angle;
	int angle_Range; 
	int spawn_Frequency;
	int particle_Lifetime;
	int system_Lifetime;
};