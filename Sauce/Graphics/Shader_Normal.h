#pragma once
#include <memory>
#include <wrl.h>
#include "Shader.h"

class ShaderNormal :public SpriteShader
{
public:
    ShaderNormal(ID3D11Device* device);
    ~ShaderNormal() override {}

    void Begin(const RenderContext& rc) override;
    void Draw(const RenderContext& rc, const Sprite* sprite) override;
    void End(const RenderContext& rc) override;

private:
    Microsoft::WRL::ComPtr<ID3D11VertexShader>			vertexShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader>			pixelShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout>			inputLayout;

    Microsoft::WRL::ComPtr<ID3D11BlendState>			blendState;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState>		rasterizerState;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState>		depthStencilState;

    Microsoft::WRL::ComPtr<ID3D11SamplerState>			samplerState;
};