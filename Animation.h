#pragma once
#include "entity.h"
#include "Sprite.h"

class Animation :
	public Sprite
{
public:
	Animation(const string& path, int frameNum, bool loop = true, float fps = 20, bool png = true);
	~Animation();

	void update(float dt);
	void reset();
	
	vector<Texture*> textures;

	float currentFrame;
	float fps;
	bool loop;
	bool isEnd;
	bool isLoopEnd;
};

