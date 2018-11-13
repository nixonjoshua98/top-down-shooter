#include "stdafx.h"

#include "JN_ProjectileController.h"
#include "JN_RealTimer.h"
#include "JN_WindowData.h"

#include <iostream>


JN_ProjectileController::JN_ProjectileController()
{

}

void JN_ProjectileController::Init(int maxprojectiles, JN_Logging *logObj, JN_WindowData *windowData)
{
	this->windowData = windowData;
	this->maxProjectiles = maxprojectiles;
}

JN_ProjectileController::~JN_ProjectileController()
{
	logObj = NULL;
	windowData = NULL;

	for (auto p : projectiles)
	{
		delete p;
		p = NULL;
	}
}

void JN_ProjectileController::CreateInitialProjectiles(SDL_Renderer *renderer)
{
	JN_Projectile *p;

	for (int i = 0; i < maxProjectiles; i++)
	{
		p = new JN_Projectile();

		p->Init(renderer, logObj, windowData);
		projectiles.push_back(p);
	}
}

bool JN_ProjectileController::Shoot(SDL_Rect sourceRect, SDL_Rect targetRect)
{
	int projectileIndex = GetAvailableProjectileIndex();

	if (projectileIndex >= 0)
		projectiles[projectileIndex]->SetTarget(sourceRect, targetRect);

	return projectileIndex >= 0;
}

bool JN_ProjectileController::ProjectileAvailable()
{
	for (int i = 0; i < maxProjectiles; i++)
	{
		if (!projectiles[i]->visible)
			return true;
	}
	return false;
}

int JN_ProjectileController::GetAvailableProjectileIndex()
{
	if (!ProjectileAvailable())
		return -1;

	for (int i = 0; i < maxProjectiles; i++)
	{
		if (!projectiles[i]->visible)
			return i;
	}

	return -1;
}

void JN_ProjectileController::Update()
{
	for (int i = 0; i < maxProjectiles; i++)
		projectiles[i]->Update();
}

void JN_ProjectileController::LateUpdate()
{
	for (int i = 0; i < maxProjectiles; i++)
		projectiles[i]->LateUpdate();
}

void JN_ProjectileController::Render(SDL_Renderer *renderer)
{
	for (int i = 0; i < maxProjectiles; i++)
		projectiles[i]->Render(renderer);
}