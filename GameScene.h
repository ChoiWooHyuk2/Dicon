#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Player_01.h"
#include "Player_02.h"
#include "Player_03.h"
#include "Player_04.h"
#include "AnimationTest.h"
#include "HPController.h"
class GameScene
	:public Scene
{
public:
	GameScene(string url1, string url2);
	~GameScene();

	HPController * hpController;
	Sprite* background;

	PlayerFrame * p1;
	PlayerFrame * p2;

	AnimationTest * test;
	string ur1;
	string ur2;

	//For Cam
	Vec2 currnetPos;
	Vec2 zoomOffsetLerp;
	float camSpeed;
	float zoomRatio;
	float posRatio;
	float camOffset;

	void update(float dt);
	void cameraMovement(float dt);
};

