#pragma once
#include "Define.h"
#include "Entity.h"
#include "Scene.h"

class World
{
public:
	World();
	~World();
	void update(float dt);
	void render();
	void init();
	void dispose();
	void changeScene(Scene* scene);
	int getKeyState(int vk);
	Vec2 getMousePos();

	Scene* currentScene;
	LPD3DXSPRITE rootSprite;
	bool lastKeys[530];
	bool currentKeys[530];
	POINT mousePoint;
	list<Timer*> timerList;
};

extern World world;