#pragma once

#include "SpriteSheet.h"

class Entity {

public:

	/*Entity();
	void Update(float elapsed);
	void Render();
	bool collidesWith(Entity *entity);
	void FixedUpdate(); */

private:

	SpriteSheet sprite;
	float x;
	float y;
	float width;
	float height;
	float velocity_x;
	float velocity_y;
	float acceleration_x;
	float acceleration_y;
	float friction_x;
	float friction_y;
	float mass;
	bool isStatic;
	bool enableCollisions;
	bool collidedTop;
	bool collidedBottom;
	bool collidedLeft;
	bool collidedRight;
};