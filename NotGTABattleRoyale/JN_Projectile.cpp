#include "stdafx.h"

#include "JN_Projectile.h"
#include "JN_GameWorld.h"

#include <iostream>

JN_Projectile::~JN_Projectile()
{
	logObj = NULL;
	windowData = NULL;
}

void JN_Projectile::Init(SDL_Renderer *renderer, JN_Logging *logObj, JN_WindowData *windowData)
{
	this->logObj = logObj;
	this->windowData = windowData;

	JN_Sprite::Init(SpriteType::PROJECTILE, renderer, SDL_Rect(), logObj, 1);

	rect.w = PROJECTILE_WIDTH;
	rect.h = PROJECTILE_HEIGHT;
}

void JN_Projectile::SetTarget(SDL_Rect _sourceRect, SDL_Rect _targetRect)
{
	visible = true;
	sourceRect = _sourceRect;
	vector2 = JN_Vector2((float)_targetRect.x, (float)_targetRect.y);
	x = (float)_sourceRect.x, y = (float)_sourceRect.y;

	rect.x = _sourceRect.x;
	rect.y = _sourceRect.y;
}

void JN_Projectile::Update()
{
	if (visible)
	{
		JN_Vector2 v = vector2.Normalise();

		x += v.x * speedMultiplier;
		y += v.y * speedMultiplier;

		rect.x = (int)x;
		rect.y = (int)y;
	}
}

bool JN_Projectile::OutOfBounds()
{
	// Projectile out of screen - Split over two lines as very long
	//bool a = (rect.x < 0 || rect.y < JN_GameWorld::BANNER_HEIGHT);
	//bool b = (rect.x + rect.w > JN_GameWorld::MIN_WINDOW_WIDTH || rect.y + rect.h > JN_GameWorld::MIN_WINDOW_HEIGHT);
	//return a || b;

	bool x = ((rect.x + rect.w) < windowData->xOffset || (rect.x > (windowData->xOffset + JN_GameWorld::MIN_WINDOW_WIDTH)));
	bool y = (rect.y < (windowData->yOffset + JN_GameWorld::BANNER_HEIGHT) || (rect.y > (windowData->yOffset + JN_GameWorld::MIN_WINDOW_HEIGHT)));

	return x || y;
}

void JN_Projectile::LateUpdate()
{
	if (visible && OutOfBounds())
		visible = false;
}

void JN_Projectile::Render(SDL_Renderer *renderer)
{
	if (visible)
		JN_Sprite::Render(renderer);
}