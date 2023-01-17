// 
//  SS5Platform.cpp
//
#include "SS5PlayerPlatform.h"

/**
* �e�v���b�g�t�H�[���ɍ��킹�ď������쐬���Ă�������
* DX���C�u�����p�ɍ쐬����Ă��܂��B
*/
//#include "DxLib.h"
TexureData texdata[TEXDATA_MAX];
PARTDATA partdata[PARTDATA_MAX];
int partdata_index;

namespace ss
{
	/**
	* �t�@�C���ǂݍ���
	*/
	unsigned char* SSFileOpen(const char* pszFileName, const char* pszMode, unsigned long * pSize)
	{
		//�e�N�X�`���f�[�^�̏������������ł���Ă��܂��B
		int i;
		for (i = 0; i < TEXDATA_MAX; i++)
		{
			texdata[i].id = -1;
		}

		unsigned char * pBuffer = NULL;
		SS_ASSERT2(pszFileName != NULL && pSize != NULL && pszMode != NULL, "Invalid parameters.");
		*pSize = 0;
		do
		{
		    // read the file from hardware
			FILE *fp = fopen(pszFileName, pszMode);
		    SS_BREAK_IF(!fp);
		    
		    fseek(fp,0,SEEK_END);
		    *pSize = ftell(fp);
		    fseek(fp,0,SEEK_SET);
		    pBuffer = new unsigned char[*pSize];
		    *pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
		    fclose(fp);
		} while (0);
		if (! pBuffer)
		{

			std::string msg = "Get data from file(";
		    msg.append(pszFileName).append(") failed!");
		    
		    SSLOG("%s", msg.c_str());

		}
		return pBuffer;
	}

	/**
	* �e�N�X�`���̓ǂݍ���
	*/
	int idx = 0;
	long SSTextureLoad(const char* pszFileName )
	{
		/**
		* �e�N�X�`���Ǘ��p�̃��j�[�N�Ȓl��Ԃ��Ă��������B
		* �e�N�X�`���̊Ǘ��̓Q�[�����ōs���`�ɂȂ�܂��B
		* �e�N�X�`���ɃA�N�Z�X����n���h����A�e�N�X�`�������蓖�Ă��o�b�t�@�ԍ����ɂȂ�܂��B
		*
		* �v���C���[�͂����ŕԂ����l�ƃp�[�c�̃X�e�[�^�X�������ɕ`����s���܂��B
		*/
		long rc = idx;
		
		texdata[idx].id = idx;
		texdata[idx].name = pszFileName;


		idx++;

		return rc;
	}
	
	/**
	* �e�N�X�`���̉��
	*/
	bool SSTextureRelese(long handle)
	{
		/// �����������ԍ��ŉ��x������������Ă΂��̂ŁA��O���o�Ȃ��悤�ɍ쐬���Ă��������B
		bool rc = true;
		return rc ;
	}

	/**
	* �e�N�X�`���̃T�C�Y���擾
	* �e�N�X�`����UV��ݒ肷��̂Ɏg�p���܂��B
	*/
	bool SSGetTextureSize(long handle, int &w, int &h)
	{
/*
		if (GetGraphSize(handle, &w, &h) == -1)
		{
			return false;
		}
*/
		return true;
	}

	/**
	* �X�v���C�g�̕\��
	*/
	void SSDrawSprite(State state, char* name)
	{
		//�o�̓o�b�t�@�փR�s�[
		partdata[partdata_index].name = name;						/// ���̃t���[���ōX�V���s����X�e�[�^�X�̃t���O
		partdata[partdata_index].flags = state.flags;						/// ���̃t���[���ōX�V���s����X�e�[�^�X�̃t���O
		partdata[partdata_index].cellIndex = state.cellIndex;					/// �p�[�c�Ɋ��蓖�Ă�ꂽ�Z���̔ԍ�
		partdata[partdata_index].x = state.mat[12];						/// SS5�A�g���r���[�g�FX���W
		partdata[partdata_index].y = state.mat[13];						/// SS5�A�g���r���[�g�FX���W
		partdata[partdata_index].anchorX = state.anchorX;					/// ���_X�I�t�Z�b�g�{�Z���ɐݒ肳�ꂽ���_�I�t�Z�b�gX
		partdata[partdata_index].anchorY = state.anchorY;					/// ���_Y�I�t�Z�b�g�{�Z���ɐݒ肳�ꂽ���_�I�t�Z�b�gY
		partdata[partdata_index].rotationX = state.rotationX;				/// X��]�i�e�q�֌W�v�Z�ρj
		partdata[partdata_index].rotationY = state.rotationY;				/// Y��]�i�e�q�֌W�v�Z�ρj
		partdata[partdata_index].rotationZ = state.rotationZ;				/// Z��]�i�e�q�֌W�v�Z�ρj
		partdata[partdata_index].scaleX = state.scaleX;					/// X�X�P�[���i�e�q�֌W�v�Z�ρj
		partdata[partdata_index].scaleY = state.scaleY;					/// Y�X�P�[���i�e�q�֌W�v�Z�ρj
		partdata[partdata_index].opacity = state.opacity;					/// �s�����x�i0�`255�j�i�e�q�֌W�v�Z�ρj
		partdata[partdata_index].size_X = state.size_X;					/// SS5�A�g���r���[�g�FX�T�C�Y
		partdata[partdata_index].size_Y = state.size_Y;					/// SS5�A�g���r���[�g�FX�T�C�Y
		partdata[partdata_index].uv_move_X = state.uv_move_X;				/// SS5�A�g���r���[�g�FUV X�ړ�
		partdata[partdata_index].uv_move_Y = state.uv_move_Y;				/// SS5�A�g���r���[�g�FUV Y�ړ�
		partdata[partdata_index].uv_rotation = state.uv_rotation;				/// SS5�A�g���r���[�g�FUV ��]
		partdata[partdata_index].uv_scale_X = state.uv_scale_X;				/// SS5�A�g���r���[�g�FUV X�X�P�[��
		partdata[partdata_index].uv_scale_Y = state.uv_scale_Y;				/// SS5�A�g���r���[�g�FUV Y�X�P�[��
		partdata[partdata_index].boundingRadius = state.boundingRadius;			/// SS5�A�g���r���[�g�F�����蔼�a
		partdata[partdata_index].colorBlendFunc = state.colorBlendFunc;				/// SS5�A�g���r���[�g�F�J���[�u�����h�̃u�����h���@
		partdata[partdata_index].colorBlendType = state.colorBlendType;				/// SS5�A�g���r���[�g�F�J���[�u�����h�̒P�F�����_�J���[���B
		partdata[partdata_index].flipX = state.flipX;						/// �����]�i�e�q�֌W�v�Z�ρj
		partdata[partdata_index].flipY = state.flipY;						/// �c���]�i�e�q�֌W�v�Z�ρj
		partdata[partdata_index].isVisibled = state.isVisibled;				/// ��\���i�e�q�֌W�v�Z�ρj
		partdata[partdata_index].instancerotationX = state.instancerotationX;		/// �C���X�^���X�p�[�c�ɐݒ肳�ꂽX��]
		partdata[partdata_index].instancerotationY = state.instancerotationY;		/// �C���X�^���X�p�[�c�ɐݒ肳�ꂽY��]
		partdata[partdata_index].instancerotationZ = state.instancerotationZ;		/// �C���X�^���X�p�[�c�ɐݒ肳�ꂽZ��]
		partdata[partdata_index].texture = state.texture;					/// �Z���ɑΉ������e�N�X�`���ԍ��i�Q�[�����ŊǗ����Ă���ԍ���ݒ肷��j
		partdata[partdata_index].rect.x = (int)state.rect.origin.x;						/// �Z���ɑΉ������e�N�X�`�����̕\���̈�i�J�n���W�A�������j
		partdata[partdata_index].rect.y = (int)state.rect.origin.y;						/// �Z���ɑΉ������e�N�X�`�����̕\���̈�i�J�n���W�A�������j
		partdata[partdata_index].rect.w = (int)state.rect.size.width;						/// �Z���ɑΉ������e�N�X�`�����̕\���̈�i�J�n���W�A�������j
		partdata[partdata_index].rect.h = (int)state.rect.size.height;						/// �Z���ɑΉ������e�N�X�`�����̕\���̈�i�J�n���W�A�������j
		partdata[partdata_index].blendfunc = state.blendfunc;					/// �p�[�c�ɐݒ肳�ꂽ�u�����h���@
		partdata[partdata_index].quad = state.quad;								/// ���_���
		memcpy( partdata[partdata_index].mat, state.mat, sizeof( state.mat ) );					/// �p�[�c�̈ʒu���Z�o���邽�߂̃}�g���N�X�i�e�q�֌W�v�Z�ρj

		partdata_index++;


#if 0
		//���Ή��@�\
		//�X�e�[�^�X��������擾���A�e�v���b�g�t�H�[���ɍ��킹�ċ@�\���������Ă��������B
		//X��]�AY��]�A�㉺���]�A�J���[�u�����h�i�ꕔ�̂݁j
		//���_�ό`�AX�T�C�Y�AY�T�C�Y
		float x = state.mat[12];	/// �\�����W�̓}�g���N�X����擾���܂��B
		float y = state.mat[13];	/// �\�����W�̓}�g���N�X����擾���܂��B
		float rotationZ = RadianToDegree(state.rotationZ);		/// ��]�l
		float scaleX = state.scaleX;							/// �g�嗦
		float scaleY = state.scaleY;							/// �g�嗦

		//�`��t�@���N�V����
		//
		switch (state.blendfunc)
		{
			case BLEND_MIX:		///< 0 �u�����h�i�~�b�N�X�j
				if (state.opacity == 255)
				{
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, state.opacity);
				}
				else
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, state.opacity);
				}
				break;
			case BLEND_MUL:		///< 1 ��Z
				SetDrawBlendMode(DX_BLENDMODE_MULA, state.opacity);
				break;
			case BLEND_ADD:		///< 2 ���Z
				SetDrawBlendMode(DX_BLENDMODE_ADD, state.opacity);
				break;
			case BLEND_SUB:		///< 3 ���Z
				SetDrawBlendMode(DX_BLENDMODE_SUB, state.opacity);
				break;

		}

		if (state.flags & PART_FLAG_COLOR_BLEND)
		{
			//RGB�̃J���[�u�����h��ݒ�
			//�����ɍČ�����ɂ͐�p�̃V�F�[�_�[���g���A�e�N�X�`���ɃJ���[�l����������K�v������
			//�쐬����ꍇ��ssShader_frag.h�ACustomSprite�̃R�����g�ƂȂ��Ă�V�F�[�_�[�������Q�l�ɂ��Ă��������B
			if (state.colorBlendType == VERTEX_FLAG_ONE)
			{
				//�P�F�J���[�u�����h
			}
			else
			{
				//���_�J���[�u�����h
				//���Ή�
			}
			switch (state.colorBlendFunc)
			{
			case BLEND_MIX:
				break;
			case BLEND_MUL:		///< 1 ��Z
				// �u�����h���@�͏�Z�ȊO���Ή�
				// �Ƃ肠��������̐F�𔽉f������
				SetDrawBright(state.quad.tl.colors.r, state.quad.tl.colors.g, state.quad.tl.colors.b);
				break;
			case BLEND_ADD:		///< 2 ���Z
				break;
			case BLEND_SUB:		///< 3 ���Z
				break;
			}

		}

		/**
		* DX���C�u������X��Y�����g��Ȃ̂ŁA�Ƃ肠����X�X�P�[�����g�p����
		* DX���C�u������Y���]�ł��Ȃ��̂Ŗ��Ή�
		* DrawRectRotaGraph��x��y�����S�ɂȂ�悤�ɁA�e�N�X�`���̋�`��\�����܂��B
		*/
		DrawRectRotaGraph(
			(int)x, (int)y,	//���̍��W���摜�̒��S�ɂȂ�܂��B
			(int)state.rect.origin.x, (int)state.rect.origin.y, (int)state.rect.size.width, (int)state.rect.size.height,
			scaleX, rotationZ,
			state.texture, TRUE, state.flipX
			);

		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);	//�u�����h�X�e�[�g��ʏ�֖߂�
#endif
	}

	/**
	* ���[�U�[�f�[�^�̎擾
	*/
	void SSonUserData(Player *player, UserData *userData)
	{
		//�Q�[�����փ��[�U�[�f�[�^��ݒ肷��֐����Ăяo���Ă��������B
	}

	/**
	* ���[�U�[�f�[�^�̎擾
	*/
	void SSPlayEnd(Player *player)
	{
		//�Q�[�����փA�j���Đ��I����ݒ肷��֐����Ăяo���Ă��������B
	}

	/**
	* windows�p�p�X�`�F�b�N
	*/ 
	bool isAbsolutePath(const std::string& strPath)
	{
		return true;
	}

};
