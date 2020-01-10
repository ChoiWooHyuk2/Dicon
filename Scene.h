#pragma once
#include "Entity.h"
#include "Timer.h"

class Scene :
	public Entity
{
public:
	list<Entity *> ui;
public:
	Scene();
	~Scene();
	void update(float dt);
	void render();
	void addUI(Entity * uiObject);
	void follow(Entity* target, Vec2 offset = Vec2(1280 / 2, 720 / 2));
	void unfollow();
	void shake(float duration, int count, float range);

	Entity* followTarget;
	Vec2 offset;
	Timer* shakeTimer;
};