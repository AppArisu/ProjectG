#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "ssbpLib/SS5Player.h"
#include "ssbpLib/SS5PlayerPlatform.h"


/**
* SS5Player for HSP
*/
//#define OUTPUT_DEBUG_LOG	//�L���ɂ���ƃf�o�b�O�o��
void logout(const char *str);

//-------------------------------------------------------------------------------
//	DLL�G���g���[
//-------------------------------------------------------------------------------
BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}



/// SS5�v���C���[
#define SSPLAYER_MAX (32)
ss::Player *ssplayer[SSPLAYER_MAX];

int buffcount = 0;
int texindex = 0;


CELLDATA celldata[CELL_MAX];
PARTDATA partdata[128];
float fps_dt = 0.0166f;

//SS5P for HSP�C���^�[�t�F�[�X
//������
INT WINAPI SSPlayer_initlize(void)
{
	logout("SSPlayer_initlize---------------------------------\n");

	memset(celldata, 0, sizeof(CELLDATA));
	int idx;
	for (idx = 0; idx < CELL_MAX; idx++)
	{
		celldata[idx].index = -1;
	}


	buffcount = 0;
	texindex = 0;

	for (idx = 0; idx < SSPLAYER_MAX; idx++)
	{
		ssplayer[idx] = NULL;
	}
	logout("SSPlayer_initlize_end\n");
	return 0;
}

//FPS�ݒ�
INT WINAPI SSPlayer_setFps(int fps)
{
	logout("SSPlayer_setFps\n");

	fps_dt = 1.0f / (float)fps;
	logout("SSPlayer_setFps\n");
	return 0;
}

//DLL�ŊǗ����Ă���v���C���[�����擾
INT WINAPI SSPlayer_getPlayerNum(void)
{
	return SSPLAYER_MAX;
}


//sspb�ǂݍ���
INT WINAPI SSPlayer_addData(char *name)
{
	logout("SSPlayer_addData\n");

	ss::ResourceManager *resman;
	resman = ss::ResourceManager::getInstance();
	//���ꂼ��̃v���b�g�t�H�[���ɍ��킹���p�X�֕ύX���Ă��������B
	std::string ret = resman->addData(name);
	logout("SSPlayer_addData_end\n");
	return 0;
}

//�e�N�X�`���ԍ����擾
INT WINAPI SSPlayer_get_texureIndex(int idx )
{
	return celldata[idx].index;
}
//�e�N�X�`�������擾
INT WINAPI SSPlayer_get_texureName(int idx, char *name)
{
	sprintf_s(name, MAX_PATH, "%s", celldata[idx].name);
	return 0;
}

//�v���C���[�쐬
INT WINAPI SSPlayer_play(int idx, char *data_name, char *motion_name)
{
	logout("SSPlayer_create\n");
	
	if ( ssplayer[idx] == NULL )
	{
		ssplayer[idx] = ss::Player::create();	//�v���C���[�쐬
	}
	ssplayer[idx]->setData(data_name);		        // ssbp�t�@�C�����i�g���q�s�v�j

	logout("SSPlayer_create_1\n");
	char str[128];
	sprintf_s(str, 128, "%s\n", motion_name );
	logout(str);


	//�Đ����郂�[�V������ݒ�
	ssplayer[idx]->play(motion_name);				 // �A�j���[�V���������w��(ssae��/

	logout("SSPlayer_create_end\n");
	return 0;

}

//�v���C���[�X�V
INT WINAPI SSPlayer_update(void)
{
//	logout("SSPlayer_update\n");

	int idx;
	for (idx = 0; idx < SSPLAYER_MAX; idx++)
	{
		if ( ssplayer[idx] != NULL )
		{
			ssplayer[idx]->update(fps_dt);		//�A�j���̍X�V
		}
	}
	return 0;
}

//�p�[�c���̎擾
INT WINAPI SSPlayer_get_partNum(int idx)
{
	int rc = 0;
	if (ssplayer[idx] != NULL)
	{
		rc = ssplayer[idx]->getPartNum();

	}
	return rc;
}

//�p�[�c�X�e�[�^�X�̎擾
INT WINAPI SSPlayer_get_partStatus(int idx, int partidx, PARTDATA *pt)
{

	pt->texid = -1;	//�e�N�X�`��ID
	if (ssplayer[idx] != NULL)
	{

		ss::State state;
		state = ssplayer[idx]->getPartState(partidx);
		pt->texid = state.texture;					//00:�e�N�X�`��ID
		pt->visble = 0;
		if ( state.isVisibled == true )				//01:��\���t���O
		{
			pt->visble = 1;
		}
		pt->x = (int)state.mat[12];					//02:�\���ʒuX
		pt->y = (int)state.mat[13];					//03:�\���ʒuY
		pt->sx = (int)state.rect.origin.x;			//04:�e�N�X�`�����̊J�n�ʒuX
		pt->sy = (int)state.rect.origin.y;			//05:�e�N�X�`�����̊J�n�ʒuY
		pt->h = (int)state.rect.size.width;			//06:�摜�̕�
		pt->w = (int)state.rect.size.height;		//07:�摜�̍���
		pt->zoomx = (int)( state.scaleX * 100.0f );	//08:�g�嗦X
		pt->zoomy = (int)( state.scaleY * 100.0f );	//09:�g�嗦Y
		pt->rot =   (int)( state.rotationZ );		//10:��]�p�x
		pt->alpha = state.opacity;					//11:�����x
		pt->brend = state.blendfunc;				//12:�u�����h���[�h
		pt->flipx = 0;								//13:�����]
		if (state.flipX == true )
		{
			pt->flipx = 1;							//13:�����]
		}
		pt->flipy = 0;								//14:�c���]
		if (state.flipY == true)
		{
			pt->flipy = 1;							//14:�c���]
		}
		pt->sizex = (int)(state.size_X);			//15:X�T�C�Y
		pt->sizey = (int)(state.size_Y);			//16:Y�T�C�Y
		pt->boundingRadius = (int)(state.boundingRadius);	//17:�����蔼�a

	}
	//	logout("SSPlayer_update\n");

	return 0;
}

//�v���C���[�\���ʒu�ݒ�
INT WINAPI SSPlayer_setPosition(int idx, int x, int y)
{
	if (ssplayer[idx] != NULL)
	{
		ssplayer[idx]->setPosition((float)x, (float)y);
	}
	return 0;
}

//�v���C���[�\���p�x�ݒ�
INT WINAPI SSPlayer_setRotation(int idx, double rotx, double roty, double rotz)
{
	if (ssplayer[idx] != NULL)
	{
		ssplayer[idx]->setRotation((float)rotx, (float)roty, (float)rotz );
	}
	return 0;
}

//�v���C���[�\���X�P�[���ݒ�
INT WINAPI SSPlayer_setScale(int idx, double zoomx, double zoomy)
{
	if (ssplayer[idx] != NULL)
	{
		ssplayer[idx]->setScale((float)zoomx, (float)zoomy);
	}
	return 0;
}

//�v���C���[�����x�ݒ�
INT WINAPI SSPlayer_setAlpha(int idx, int a)
{
	if (ssplayer[idx] != NULL)
	{
		ssplayer[idx]->setAlpha(a);
	}
	return 0;
}

//�v���C���[���]�ݒ�
INT WINAPI SSPlayer_setFlip(int idx, int flipX, int flipY)
{
	bool fx =  false;
	if (flipX != 0 )
	{
		fx = true;
	}
	bool fy = false;
	if (flipY != 0)
	{
		fy = true;
	}
	if (ssplayer[idx] != NULL)
	{
		ssplayer[idx]->setFlip(fx, fy);
	}
	return 0;
}

//�v���C���[�|�[�Y
INT WINAPI SSPlayer_pause(int idx)
{
	if (ssplayer[idx] != NULL)
	{
		ssplayer[idx]->pause();
	}
	return 0;
}
//�v���C���[�ĊJ
INT WINAPI SSPlayer_resume(int idx)
{
	if (ssplayer[idx] != NULL)
	{
		ssplayer[idx]->resume();
	}
	return 0;
}
//�v���C���[�t���[���w��
INT WINAPI SSPlayer_setFrameNo(int idx, int FrameNo)
{
	if (ssplayer[idx] != NULL)
	{
		ssplayer[idx]->setFrameNo(FrameNo);
	}
	return 0;
}
//�v���C���[�A�j�����t���[���擾
INT WINAPI SSPlayer_getMaxFrame(int idx)
{
	if (ssplayer[idx] != NULL)
	{
		return ( ssplayer[idx]->getMaxFrame() );
	}
	return 0;
}
//�v���C���[�A�j���Đ��t���[���擾
INT WINAPI SSPlayer_getFrameNo(int idx)
{
	if (ssplayer[idx] != NULL)
	{
		return (ssplayer[idx]->getFrameNo() );
	}
	return 0;
}
//���O����p�[�c�X�e�[�^�X���擾
INT WINAPI SSPlayer_get_namePartStatus(int idx, char* name, int frame, PARTDATA *pt)
{
	pt->texid = -1;	//�e�N�X�`��ID
	if (ssplayer[idx] != NULL)
	{

		ss::State state;
		state = ssplayer[idx]->getPartState(name, frame);
		pt->texid = state.texture;					//00:�e�N�X�`��ID
		pt->visble = 0;
		if (state.isVisibled == true)				//01:��\���t���O
		{
			pt->visble = 1;
		}
		pt->x = (int)state.mat[12];					//02:�\���ʒuX
		pt->y = (int)state.mat[13];					//03:�\���ʒuY
		pt->sx = (int)state.rect.origin.x;			//04:�e�N�X�`���Ȃ��̊J�n�ʒuX
		pt->sy = (int)state.rect.origin.y;			//05:�e�N�X�`���Ȃ��̊J�n�ʒuY
		pt->h = (int)state.rect.size.width;			//06:�e�N�X�`���Ȃ��̊J�n�I��X
		pt->w = (int)state.rect.size.height;		//07:�e�N�X�`���Ȃ��̊J�n�I��Y
		pt->zoomx = (int)(state.scaleX * 100.0f);	//08:�g�嗦X
		pt->zoomy = (int)(state.scaleY * 100.0f);	//09:�g�嗦Y
		pt->rot = (int)(state.rotationZ);		//10:��]�p�x
		pt->alpha = state.opacity;					//11:�����x
		pt->brend = state.blendfunc;				//12:�u�����h���[�h
		pt->flipx = 0;								//13:�����]
		if (state.flipX == true)
		{
			pt->flipx = 1;							//13:�����]
		}
		pt->flipy = 0;								//14:�c���]
		if (state.flipY == true)
		{
			pt->flipy = 1;							//14:�c���]
		}
		pt->sizex = (int)(state.size_X);			//15:X�T�C�Y
		pt->sizey = (int)(state.size_Y);			//16:Y�T�C�Y
		pt->boundingRadius = (int)(state.boundingRadius);	//17:�����蔼�a

	}
	//	logout("SSPlayer_update\n");

	return 0;
}

//�I������
INT WINAPI SSPlayer_Delete(void)
{
	int idx;
	for (idx = 0; idx < SSPLAYER_MAX; idx++)
	{
		if ( ssplayer[idx] )
		{
			delete(ssplayer[idx]);
			ssplayer[idx] = NULL;
		}
	}
	ss::ResourceManager *resman;
	resman = ss::ResourceManager::getInstance();
	delete (resman);
	return 0;
}


//���O�o��
void logout(const char *str)
{
#ifdef OUTPUT_DEBUG_LOG
	FILE *fp;	

	if ((fp = fopen("sshsplog.txt", "a")) == NULL) {
		printf("file open error!!\n");
		exit(EXIT_FAILURE);	
	}

	fputs(str, fp);
	fclose(fp);	
#endif
}