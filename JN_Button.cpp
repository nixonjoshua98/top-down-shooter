#include "stdafx.h"

#include "JN_GameObject.h"
#include "JN_Button.h"

JN_Button::JN_Button()
{

}


JN_Button::~JN_Button()
{
	delete text;

	text = NULL;
}


void JN_Button::Init(std::string txt, int x, int y, int w, int h, SDL_Color btnCol, SDL_Color txtCol, char *fontPath, int size)
{
	labelText = txt;

	text = new JN_Text();

	text->Init(x, y, w, h, txtCol.r, txtCol.g, txtCol.b, fontPath, size);
	square.Init(x - 13, y, w + 26, h, btnCol.r, btnCol.b, btnCol.b);
	borderSquare.Init(x - 13, y, w + 26, h, txtCol.r, txtCol.b, txtCol.b);
}


void JN_Button::Render(SDL_Renderer* renderer)
{
	square.Render(renderer, !isActive);
	borderSquare.Render(renderer, false);
	text->Render(renderer, labelText);
}


void JN_Button::Update()
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	SDL_Rect r = SDL_Rect{x, y, 5, 5};
	
	isActive = JN_GameObject::Collide(square.rect, r);
}

void JN_Button::Input(SDL_Event e)
{
	isClicked = false;

	if (isActive && e.type == SDL_MOUSEBUTTONDOWN && (e.button.button == SDL_BUTTON_LEFT))
	{
		isClicked = true;
	}
}


bool JN_Button::IsClicked()
{
	return isClicked;
}

void JN_Button::Resize(int x, int y)
{
	square.rect.x += x;
	square.rect.y += y;

	borderSquare.rect.x += x;
	borderSquare.rect.y += y;

	text->rect.x += x;
	text->rect.y += y;
}

void JN_Button::SetText(std::string str)
{
	labelText = str;
}


void JN_Button::Reset()
{
	isClicked = false;
}