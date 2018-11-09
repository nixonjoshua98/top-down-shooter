#ifndef JN_PLAYER_H
#define JN_PLAYER_H

#include "SDL.h"

#include "JN_Sprite.h"
#include "JN_ProjectileController.h"
#include "JN_PlayerControls.h"

#include <set>
#include <map>

class JN_Player : public JN_Sprite
{
public:
	///<summary>Deconstructor</summary>
	~JN_Player();


	///<summary>Initialises the player objects</summary>
	///<param name = "renderer">Used to load the images</param>
	void Init(SDL_Renderer *renderer);


	///<summary>Method which handles the user input</summary>
	///<param name = "e">The event object</param>
	void Input(SDL_Event e);


	///<summary>Method which is called every frame</summary>
	void Update();


	///<summary>Called after Update and handles collisions</summary>
	///<param name = "tiles">The tiles which the player could potentially collide with</param>
	void LateUpdate(std::vector<JN_Sprite*> tiles);


	///<summary>Renders the player to the screen</summary>
	///<param name = "renderer">The renderer which the player will be on</param>
	void Render(SDL_Renderer *renderer) override;

private:
	static const int MOVEMENT_SPEED = 5;	// The amount the player moves each movement cycle
	static const int MOVEMENT_DELAY = 10;	// The delay between movements
	static const int SHOOT_DELAY    = 250;	// The delay between being able to fire a projectile
	static const int PLAYER_WIDTH   = 20;	// ...
	static const int PLAYER_HEIGHT  = 20;	// ...


	JN_ProjectileController projectileController = JN_ProjectileController(10);	// Creates the controller with a maximum of 10 projectiles on screen at once
	JN_PlayerControls controls		             = JN_PlayerControls();			// The controls object for the player, deals with all input

	// Player buffs and debuffs
	std::map<SpriteType, bool> statusEffects = {
		{ SpriteType::MOVEMENT_DEBUFF, false }
	};

	SDL_Rect newRect = SDL_Rect();	// Temp rect used during collision detection

	float lastMovementTime = 0;	// Movement delay timer
	float lastShootTime    = 0;	// Shoot timer


	///<summary>Moves the player based on the input</summary>
	void Move();


	///<summary>Attempts to shoot a projectile</summary>
	void Shoot();


	///<summary>Handles the keyboard input</summary>
	///<param name = "e">The event object</param>
	void KeyboardInputHandler(SDL_Event e);


	///<summary>Handles the mouse input</summary>
	///<param name = "e">The event object</param>
	void MouseInputHandler(SDL_Event e);


	///<summary>Sets the player position after collision checking</summary>
	void ConfirmPlayerMovement();


	///<summary>Returns a set containign the collision types</summary>
	///<param name = "tiles">vector of potential collisions</param>
	std::set<SpriteType> GetColliders(std::vector<JN_Sprite*> tiles);


	///<summary>Actions based on collisions</summary>
	///<param name = "tiles">vector of potential collisions</param>
	void ColliderManager(std::vector<JN_Sprite*> tiles);


	///<summary>Resets all player status effects</summary>
	void ResetBuffs();
};

#endif // !PLAYER_H
