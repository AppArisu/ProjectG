struct VS_OUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 texcoord : TEXCOORD;
};

//	�X�v���C�g�`��P�ʂŎw�肷��p�����[�^�[
cbuffer CbMask : register(b0) // 0�Ԃɂ���萔�o�b�t�@������ŗ��p����
{
    float dissolveThreshold; // �f�B�]���u��
    float3 dummy;
};