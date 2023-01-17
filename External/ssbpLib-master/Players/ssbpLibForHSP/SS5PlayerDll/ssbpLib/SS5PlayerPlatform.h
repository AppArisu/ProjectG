/**
*  SS5PlayerPlatform.h
*/

#ifndef SS5PlayerPlatform_h
#define SS5PlayerPlatform_h
#include "SS5Player.h"
#include <stdio.h>
#include <string>
#include <windows.h>

#define CELL_MAX (100)
struct CELLDATA {
	int index;
	char name[MAX_PATH];
};

struct PARTDATA {
	int texid;	//�e�N�X�`��ID
	int visble;	//��\���t���O
	int x;		//�\���ʒuX
	int y;		//�\���ʒuY
	int sx;		//�e�N�X�`�����̊J�n�ʒuX
	int sy;		//�e�N�X�`�����̊J�n�ʒuY
	int h;		//�e�N�X�`���̕�
	int w;		//�e�N�X�`���̍���
	int zoomx;	//�g�嗦X
	int zoomy;	//�g�嗦Y
	int rot;	//��]�p�x
	int alpha;	//�����x
	int brend;	//�u�����h���[�h
	int flipx;	//�����]
	int flipy;	//�c���]
	int sizex;	//X�T�C�Y
	int sizey;	//Y�T�C�Y
	int boundingRadius;	//�����蔼�a
};

namespace ss
{
	struct State;
	struct UserData;
	class Player;

	extern unsigned char* SSFileOpen(const char* pszFileName, const char* pszMode, unsigned long * pSize);
	extern long SSTextureLoad(const char* pszFileName);
	extern bool SSTextureRelese(long handle);
	extern bool isAbsolutePath(const std::string& strPath);
	extern void SSDrawSprite(State state);
	extern bool SSGetTextureSize(long handle, int &w, int &h);
	extern void SSonUserData(Player *player, UserData *userData);
	extern void SSPlayEnd(Player *player);

};	// namespace ss

#endif
