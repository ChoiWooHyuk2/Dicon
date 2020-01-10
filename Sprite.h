#pragma once
#include "Define.h"
#include "Entity.h"
#include "Texture.h"

class Sprite :
	public Entity
{
public:
	Sprite();
	Sprite(string path, D3DXCOLOR color = D3DXCOLOR(1,1,1,1));
	virtual ~Sprite();
	void render();
	void setPath(string path);

	void setColor(D3DXCOLOR color);

	Texture* texture;
	D3DXCOLOR color;
	bool blending;
};
	