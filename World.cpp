#include "DXUT.h"
#include "World.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Asset.h"

World::World()
	:currentScene(nullptr)
{
}


World::~World()
{
}

void World::update(float dt)
{
	if(currentScene) currentScene->update(dt);

	for(int i=0; i<256; i++)
	{
		lastKeys[i] = currentKeys[i];
		currentKeys[i] = GetAsyncKeyState(i) & 0x8000;
	}

	GetCursorPos(&mousePoint);
	ScreenToClient(DXUTGetHWND(), &mousePoint);

	for(auto timer : timerList)
	{
		timer->update(dt);
	}

	timerList.erase(remove_if(timerList.begin(), timerList.end(),
		[&](auto iter) {
			bool removing = iter->removing;
			if (removing) {
				SAFE_DELETE(iter);
			}
			return removing;
		}), timerList.end());
}

void World::render()
{
	if(currentScene) currentScene->render();
}

void World::init()
{
	asset.init();
	cout.precision(3);
	D3DXCreateSprite(DXUTGetD3D9Device(), &rootSprite);
	changeScene(new TitleScene());
	ZeroMemory(lastKeys, sizeof(lastKeys));
	ZeroMemory(currentKeys, sizeof(currentKeys));
}

void World::dispose()
{
	timerList.erase(remove_if(timerList.begin(), timerList.end(),
		[&](auto iter) {
			SAFE_DELETE(iter);
			return true;
		}), timerList.end());
	asset.dispose();
	SAFE_RELEASE(rootSprite);
	SAFE_DELETE(currentScene);
}

void World::changeScene(Scene* scene)
{
	if(currentScene != nullptr) SAFE_DELETE(currentScene);
	currentScene = scene;
}

int World::getKeyState(int vk)
{
	if(currentKeys[vk] && lastKeys[vk]) return 2;
	if(currentKeys[vk] && !lastKeys[vk]) return 1;
	if(!currentKeys[vk] && lastKeys[vk]) return -1;
	return -2;
}

Vec2 World::getMousePos()
{
	return Vec2(mousePoint.x, mousePoint.y);
}

World world;