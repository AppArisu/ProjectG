/**
*  SS5PlayerTypes.h
*/

#ifndef SS5PlayerTypes_h
#define SS5PlayerTypes_h

namespace ss
{
/**
* �J���[�\����
*/
typedef struct _SSColor4B
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} SSColor4B;

/**
* ���_���W�\����
*/
typedef struct _SSVertex3F
{
	float x;
	float y;
	float z;
} SSVertex3F;

/**
* �S���_���W�\����
*/
typedef struct _SSQuad3 {
	SSVertex3F        bl;
	SSVertex3F        br;
	SSVertex3F        tl;
	SSVertex3F        tr;
} SSQuad3;

/**
* UV�\����
*/
typedef struct _SSTex2F {
	float u;
	float v;
} SSTex2F;

/**
* ���_�\����
*/
typedef struct _ccV3F_C4B_T2F
{
	SSVertex3F			vertices;	/// ���W
	SSColor4B			colors;		/// �J���[
	SSTex2F				texCoords;	/// UV
} SSV3F_C4B_T2F;

/**
* �S���_�\����
*/
typedef struct _SSV3F_C4B_T2F_Quad
{
	SSV3F_C4B_T2F    tl;
	SSV3F_C4B_T2F    bl;
	SSV3F_C4B_T2F    tr;
	SSV3F_C4B_T2F    br;
} SSV3F_C4B_T2F_Quad;



};	// namespace ss

#endif
