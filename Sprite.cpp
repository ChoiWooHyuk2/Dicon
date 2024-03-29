#include "DXUT.h"
#include "Sprite.h"
#include "Asset.h"
#include "World.h"

Sprite::Sprite()
	:color(1, 1, 1, 1), blending(false), texture(nullptr)
{
}

Sprite::Sprite(string path, D3DXCOLOR color)
	: color(color), blending(false)
{
	setPath(path);
}

Sprite::~Sprite()
{
}

void Sprite::setPath(string path)
{
	texture = asset.getTexture(path);
	visibleRect = rect = Rect(0, 0, texture->info.Width, texture->info.Height);
}

void Sprite::setColor(D3DXCOLOR color)
{
	this->color = color;
}

void Sprite::render()
{
	if (!visible || !texture) return;
	Entity::render();

	world.rootSprite->Begin(D3DXSPRITE_ALPHABLEND);
	world.rootSprite->SetTransform(&matrix);

	if (blending)
	{
		DXUTGetD3D9Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		DXUTGetD3D9Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		DXUTGetD3D9Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	}

	world.rootSprite->Draw(texture->d3dTexture, &visibleRect, NULL, NULL, color);
	world.rootSprite->End();
}