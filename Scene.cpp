#include "DXUT.h"
#include "Scene.h"

Scene::Scene()
	:followTarget(nullptr), offset(0, 0)
{
	shakeTimer = new Timer();
}

Scene::~Scene()
{
	shakeTimer->removing = true;
}

void Scene::follow(Entity* target, Vec2 offset)
{
	this->followTarget = target;
	this->offset = offset;
}

void Scene::unfollow()
{
	this->followTarget = nullptr;
	this->offset = Vec2(0, 0);
}

void Scene::shake(float duration, int count, float range)
{
	shakeTimer->reset(duration, count);
	shakeTimer->onTick = [=]()
	{
		pos = pos + Vec2(random(-range, range), random(-range, range));
	};
}

void Scene::update(float dt)
{
	Entity::update(dt);

	Vec2 targetPos = Vec2(0, 0);

	if (followTarget)
	{
		targetPos = -followTarget->center();
	}

	pos += (targetPos + offset - pos) * 0.15;

	//Update UI
	for (auto uiObject : ui) {
		uiObject->update(dt);
	}
}

void Scene::render()
{
	Entity::render();

	//Render UI
	for (auto uiObject : ui) {
		uiObject->render();
	}
}

void Scene::addUI(Entity * uiObject)
{
	ui.push_back(uiObject);
}