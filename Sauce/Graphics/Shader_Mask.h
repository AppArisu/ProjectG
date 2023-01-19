#pragma once
#include <memory>
#include <wrl.h>
#include "Shader.h"

class ShaderMask : public SpriteShader
{
public:
	ShaderMask(ID3D11Device* device);
	~ShaderMask() override {}

	void Begin(const RenderContext& rc) override;
	void Draw(const RenderContext& rc, const Sprite* sprite) override;
	void End(const RenderContext& rc) override;

private:
	// 臒l�𑗂邽�߂̒萔�o�b�t�@�p�\����
	struct CbMask
	{
		float				dissolveThreshold;	// �f�B�]���u��
		DirectX::XMFLOAT3	dummy;
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer>				maskConstantBuffer; 	// �萔�o�b�t�@

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			inputLayout;

	Microsoft::WRL::ComPtr<ID3D11BlendState>			blendState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>		rasterizerState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>		depthStencilState;

	Microsoft::WRL::ComPtr<ID3D11SamplerState>			samplerState;
};