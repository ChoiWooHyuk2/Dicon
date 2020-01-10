#include "DXUT.h"
#include "GameScene.h"
#include "World.h"
#include "Local_GameManager.h"
#include "TitleScene.h"
#include "WinnerScene.h"
#include "Asset.h"

GameScene::GameScene(string url1, string url2) : ur1(url1), ur2(url2), camSpeed(3.0f),
currnetPos(0.0f, 0.0f), zoomRatio(1.0f), posRatio(0.0f), zoomOffsetLerp(0.0f, 0.0f)
{
	asset.sounds[L"Sources/Sound/Main.wav"]->Stop();
	asset.sounds[L"Sources/Sound/Game.wav"]->Play();
	asset.sounds[L"Sources/Sound/Game.wav"]->Reset();

	background = new Sprite("image/background/map.png");
	background->pos = Vec2(-200.0f, -100.0f);
	addChild(background);

	hpController = new HPController(this, url1, url2);

	if (url1 == "song")
		p1 = new Player_03(false);

	else if (url1 == "jae")
		p1 = new Player_04(false);

	else if (url1 == "woo")
		p1 = new Player_01(false);

	else if (url1 == "black")
		p1 = new Player_02(false);



	if (url2 == "song")
		p2 = new Player_03(true);

	else if (url2 == "jae")
		p2 = new Player_04(true);

	else if (url2 == "woo")
		p2 = new Player_01(true);

	else if (url2 == "black")
		p2 = new Player_02(true);

	p1->pos.x = 50.0f;
	p2->pos.x = 1100.0f;

	addChild(p1); LOCAL_GM->addPlayer(p1);
	addChild(p2); LOCAL_GM->addPlayer(p2);

	p1->moveSpeed *= 2.0f;
	p2->moveSpeed *= 2.0f;

	printf("p1/p2 HP : %f %f\n",
		p1->current_Hp_Gauge, p2->current_Hp_Gauge);

	offset = Vec2(1280 / 2, 720 / 2);

}

GameScene::~GameScene()
{
	delete hpController;
}

void GameScene::update(float dt)
{
	Scene::update(dt);
	LOCAL_GM->Update_GameManager(dt);
	hpController->updateHPGUI(p1, p2);
	hpController->updateShieldGUI(p1, p2);
	hpController->updateSkillCoolFill(p1, p2);
	if (LOCAL_GM->isEnd) {
		LOCAL_GM->isEnd = false;
		world.changeScene(new WinnerScene(hpController->winner, hpController->duce, ur1, ur2, p1));
		LOCAL_GM->gameReset();
		return;
	}

	cameraMovement(dt);
}

void GameScene::cameraMovement(float dt) {
	Vec2 target;
	float width = 0.0f;


	//get Width - for Scale
	width = abs(p1->center().x - p2->center().x) + 300.0f;
	
	//Get Target Pos
	target = (p1->center() + p2->center()) / 2.0f;

	if (zoomRatio == 1.0f)
		target = Vec2(0.0f, 0.0f);		//ZoomRatio == 1 -> 최소 줌 -> 여백 많이 보임


	zoomRatio = lerp(zoomRatio, (offset.x * 2) / width, camSpeed * dt);		//For Zoom
	posRatio = lerp(posRatio, width / (offset.x * 2), camSpeed * dt);		//줌한 비율을 구해서 offset추가
	currnetPos = lerp(currnetPos, target, camSpeed * dt);							//target 따라가기

	zoomRatio = clamp(zoomRatio, 1.0f, 1.4f);	//최소, 최대 설정
	posRatio = clamp(posRatio, 0.6f, 1.0f);		//최소, 최대 설정

	

	if (zoomRatio != 1.0f)
		zoomOffsetLerp = lerp(zoomOffsetLerp, offset + (-offset * (1.0f - posRatio))
			+ Vec2(0.0f, 70.0f) + (-Vec2(0.0f, 70.0f) * (1.0f - posRatio)), camSpeed * dt);
	else
		zoomOffsetLerp = lerp(zoomOffsetLerp, Vec2(0.0f, 0.0f), camSpeed * dt);

	this->scale = Vec2(zoomRatio, zoomRatio);		//스케일 적용
	this->pos = -currnetPos + zoomOffsetLerp;		//구한 위치 + Zoom한 만큼의 비율 값
}