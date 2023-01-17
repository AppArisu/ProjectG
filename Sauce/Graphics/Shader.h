#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include"RenderContext.h"
#include"Sprite.h"

class SpriteShader
{
public:
    SpriteShader() {}
    virtual ~SpriteShader() {}

    // •`‰æŠJn
    virtual void Begin(const RenderContext& rc) = 0;

    // •`‰æ
    virtual void Draw(const RenderContext& rc, const Sprite* sprite) = 0;

    // •`‰æI—¹
    virtual void End(const RenderContext& rc) = 0;
};