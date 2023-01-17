#include <stdio.h>
#include <tchar.h>
#include <string>
#include <locale.h>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "SSPlayer\SS5Player.h"

void init(void);
void outputdata(void);
void relese(void);
void outputVal(FILE *fp, int val);
void outputVal(FILE *fp, float val);
std::string toShortString(float value);

std::string open_filename;
std::string output_filename;
std::string ssbp_name;
std::string ssae_name;


/// SS5�v���C���[
ss::Player *ssplayer;
ss::ResourceManager *resman;

bool err;

extern TexureData texdata[TEXDATA_MAX];
extern int partdata_index;
extern PARTDATA partdata[PARTDATA_MAX];


/**
* ���C���֐�
*/
int main(int argc, char *argv[])
{
	//�����`�F�b�N
	int i;
	bool ishelp = false;
	int inputcount = 0;
	err = false;

	if (argc == 1)
	{
		ishelp = true;
	}
	for (i = 1; i < argc; i++)
	{
		if (
			(strcmp(argv[i], "-h") == 0)
		 || (strcmp(argv[i], "-H") == 0)
			)
		{
			//�w���v�\��
			ishelp = true;
		}
		else
		{
			switch (inputcount)
			{
			case 0:
				open_filename = argv[i];
				inputcount++;
				break;
//			case 1:
//				ssae_name = argv[i];
//				inputcount++;
//				break;
			}
		}
	}
	//�g���q�`�F�b�N
	if (open_filename.find(".ssbp") == std::string::npos)
	{
		err = true;	//�G���[���o���珈�����f
	}

	if (inputcount == 1)
	{
		//�o�̓t�@�C�������쐬
		output_filename = open_filename.substr(0, open_filename.length() - 5);
		output_filename = output_filename + ".xml";
	}
	else
	{
		err = true;	//�G���[���o���珈�����f
	}



	if (ishelp == true)
	{
		printf("�������Fssbp�̃p�X\r\n");
		printf("�I�v�V����\r\n");
		printf("-h�F�w���v�\��\r\n");
	}
	else
	{
		if (err == false)
		{
			/// �v���C���[������
			init();
			//�t�@�C���o��
			outputdata();
			/// �v���C���[�I������
			relese();
		}
	}

	return 0;				// �\�t�g�̏I�� 
}

void init( void )
{
	/**********************************************************************************

	SS�A�j���\���̃T���v���R�[�h
	Visual Studio Express 2013 for Windows Desktop�ADX���C�u�����œ�����m�F���Ă��܂��B
	ssbp��png������΍Đ����鎖���ł��܂����AResources�t�H���_��sspj���܂܂�Ă��܂��B

	**********************************************************************************/
	//���\�[�X�}�l�[�W���̍쐬
	resman = ss::ResourceManager::getInstance();
	//�v���C���[�̍쐬
	ssplayer = ss::Player::create();

	//�A�j���f�[�^�����\�[�X�ɒǉ�
	resman->addData(open_filename);

	int fpos = open_filename.rfind("\\");
	if ( fpos == std::string::npos)
	{
		//�����Ȃ��ꍇ�͂��̂܂�
		ssbp_name = open_filename;
	}
	else
	{
		ssbp_name = open_filename.substr(fpos + 1);
		ssbp_name = ssbp_name.substr(0, ssbp_name.length() - 5);	//�g���q�Ƃ�
	}

	//�v���C���[�Ƀ��\�[�X�����蓖��
	ssplayer->setData(ssbp_name);        // ssbp�t�@�C�����i�g���q�s�v�j
	//�\���ʒu��ݒ�
	ssplayer->setPosition(0, 0);
	//�X�P�[���ݒ�
	ssplayer->setScale(1.0f, 1.0f);
	//��]��ݒ�
	ssplayer->setRotation(0.0f, 0.0f, 0.0f);
	//�����x��ݒ�
	ssplayer->setAlpha(255);
	//���]��ݒ�
	ssplayer->setFlip(false, false);

}


/**
* �v���C���[�I������
*/
void relese( void )
{
	//SS5Player�̍폜
	delete (ssplayer);	
	delete (resman);
}



//�Z���f�[�^�̏o��
void outputdata(void)
{
	FILE *fp;
	wchar_t buf[1024];
	// �t�@�C���̃I�[�v��
	fopen_s(&fp, output_filename.c_str(), "w,ccs=UTF-8");
	if (fp == NULL)
	{
		//�G���[
		printf("file open error!!\n");
		err = true;
	}
	if (err == false)
	{
		//���P�[���w��
		setlocale(LC_ALL, "japanese");

		//�w�b�_�o��
		fputws(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"), fp);
		fputws(_T("<ssbx version=\"1.0\">\n"), fp);


		{
			//�A�j���[�V�������
			wchar_t	name[256];
			size_t wLen = 0;
			mbstowcs_s(&wLen, name, 256, ssbp_name.c_str(), _TRUNCATE);
			swprintf_s(buf, 1024, _T("  <name>%s</name>\n"), name);
			fputws(buf, fp);

			{
				//�Z�����
				fputws(_T("  <textures>\n"), fp);
				int i = 0;
				for (i = 0; i < TEXDATA_MAX; i++)
				{
					if (texdata[i].id == -1)
					{
						break;	//�f�[�^�I���
					}
					wchar_t	name[256];
					size_t wLen = 0;
					mbstowcs_s(&wLen, name, 256, texdata[i].name.c_str(), _TRUNCATE);

					swprintf_s(buf, 1024, _T("      <texture id=\"%d\" name=\"%s\" />\n"), texdata[i].id, name);
					fputws(buf, fp);
				}
				fputws(_T("  </textures>\n"), fp);
			}
		}

		ss::ResourceSet* rs = resman->getData(ssbp_name);

		for (std::map<std::string, ss::AnimeRef*>::iterator itpairstri = rs->animeCache->_dic.begin(); itpairstri != rs->animeCache->_dic.end(); itpairstri++)
		{
			// �C�e���[�^�� pair<const string, int> �^�Ȃ̂ŁA
			std::string strKey = itpairstri->first;     // �C�e���[�^����L�[��������B


			if (strKey.find("/") == std::string::npos)	//ssae�����܂܂�Ă��Ȃ��ꍇ�̓X�L�b�v
			{
				continue;
			}


			//�Đ����郂�[�V������ݒ�
			ssplayer->play(strKey);				 // �A�j���[�V���������w��(ssae��/�A�j���[�V���������\�A�ڂ����͌�q)
			ssplayer->pause();

			fputws(_T("  <motion>\n"), fp);
			{
				//���[�V�������
				wchar_t	name[256];
				size_t wLen = 0;
				mbstowcs_s(&wLen, name, 256, strKey.c_str(), _TRUNCATE);
				swprintf_s(buf, 1024, _T("    <name>%s</name>\n"), name);
				fputws(buf, fp);

				swprintf_s(buf, 1024, _T("    <fps>%d</fps>\n"), ssplayer->getFPS());
				fputws(buf, fp);
				swprintf_s(buf, 1024, _T("    <maxframe>%d</maxframe>\n"), ssplayer->getMaxFrame());
				fputws(buf, fp);

			}

			{
				//�t���[���f�[�^
				fputws(_T("    <framedata>\n"), fp);
				int maxframe = ssplayer->getMaxFrame();
				int i; 
				for (i = 0; i < maxframe; i++)
				{
					swprintf_s(buf, 1024, _T("      <frame time=\"%d\">\n"), i);
					fputws(buf, fp);

					ssplayer->setFrameNo(i);
					ssplayer->update(0);


					partdata_index = 0;	//�p�[�c�C���f�b�N�X�̏�����
					int idx = 0;
					for (idx = 0; idx < PARTDATA_MAX; idx++ )
					{
						partdata[idx].texture = -2;	//�f�[�^�Ȃ�
					}


					ssplayer->draw();	//�p�[�c�X�e�[�^�X�̎擾

					//�f�[�^�����o��
					idx = 0;
					while (1)
					{
						if ( partdata[idx].texture == -2 )
						{
							//�f�[�^�I��
							break;
						}
						//�p�[�c�X�e�[�g�������o��
						fputws(_T("        <partdata"), fp);
						
						{
							wchar_t	name[256];
							size_t wLen = 0;
							mbstowcs_s(&wLen, name, 256, partdata[idx].name.c_str(), _TRUNCATE);
							swprintf_s(buf, 1024, _T(" NAME=\"%s\""), name);
							fputws(buf, fp);
						}

	//					if (partdata[idx].x != 0.0f )
						{
							fputws(_T(" X="), fp);
							outputVal(fp, partdata[idx].x);
						}

	//					if (partdata[idx].y != 0.0f)
						{
							fputws(_T(" Y="), fp);
							outputVal(fp, partdata[idx].y);
						}

	//					if (partdata[idx].rotationZ != 0.0f)
						{
							fputws(_T(" ROTZ="), fp);
							outputVal(fp, partdata[idx].rotationZ);
						}

	//					if (partdata[idx].scaleX != 0.0f)
						{
							fputws(_T(" SCLX="), fp);
							outputVal(fp, partdata[idx].scaleX);
						}

	//					if (partdata[idx].scaleY != 0.0f)
						{
							fputws(_T(" SCLY="), fp);
							outputVal(fp, partdata[idx].scaleY);
						}

	//					if (partdata[idx].opacity != 0)
						{
							fputws(_T(" ALPH="), fp);
							outputVal(fp, partdata[idx].opacity);
						}

	//					if (partdata[idx].size_X != 0.0f)
						{
							fputws(_T(" SIZX="), fp);
							outputVal(fp, partdata[idx].size_X);
						}

	//					if (partdata[idx].size_Y != 0.0f)
						{
							fputws(_T(" SIZY="), fp);
							outputVal(fp, partdata[idx].size_Y);
						}

	//					if (partdata[idx].boundingRadius != 0.0f)
						{
							fputws(_T(" BORA="), fp);
							outputVal(fp, partdata[idx].boundingRadius);
						}
	/*
						swprintf_s(buf, 1024, _T(" colorBlendFunc=\"%d\""), partdata[idx].colorBlendFunc);
						fputws(buf, fp);

						swprintf_s(buf, 1024, _T(" colorBlendType=\"%d\""), partdata[idx].colorBlendType);
						fputws(buf, fp);
	*/
	//					if (partdata[idx].flipX != 0)
						{
							fputws(_T(" FLPX="), fp);
							outputVal(fp, partdata[idx].flipX);
						}

	//					if (partdata[idx].flipY != 0)
						{
							fputws(_T(" FLPY="), fp);
							outputVal(fp, partdata[idx].flipY);
						}

						fputws(_T(" TXID="), fp);
						outputVal(fp, partdata[idx].texture);

						fputws(_T(" RECX="), fp);
						outputVal(fp, partdata[idx].rect.x);
						fputws(_T(" RECY="), fp);
						outputVal(fp, partdata[idx].rect.y);
						fputws(_T(" RECW="), fp);
						outputVal(fp, partdata[idx].rect.w);
						fputws(_T(" RECH="), fp);
						outputVal(fp, partdata[idx].rect.h);

	//					if (partdata[idx].blendfunc != 0)
						{
							fputws(_T(" BLED="), fp);
							outputVal(fp, partdata[idx].blendfunc);
						}


						fputws(_T(" />\n"), fp);

						idx++;
					}
					fputws(_T("      </frame>\n"), fp);
				}
				fputws(_T("    </framedata>\n"), fp);
			}
			fputws(_T("  </motion>\n"), fp);
		}
		//�t�b�_�o��
		fputws(_T("</ssbx>\n"), fp);
		fputws(_T("\n"), fp);

	}
	fclose(fp);	//�t�@�C���̃N���[�Y
}

void outputVal(FILE *fp, int val)
{
	wchar_t buf[1024];

	swprintf_s(buf, 1024, _T("\"%d\""), val);
	fputws(buf, fp);
}

void outputVal(FILE *fp, float val)
{
	wchar_t buf[1024];

	if ( val == 0.0f )
	{
		swprintf_s(buf, 1024, _T("\"0\""));
	}
	else
	{
		std::string str = toShortString(val);

		wchar_t	wstr[256];
		size_t wLen = 0;
		mbstowcs_s(&wLen, wstr, 256, str.c_str(), _TRUNCATE);

		swprintf_s(buf, 1024, _T("\"%s\""), wstr);
		//�����_�ȍ~��0�̏ꍇ�������ɂ���
	}
	fputws(buf, fp);
}


/** ���������_��Z��������ŕԂ� */
std::string toShortString(float value)
{
	if (value == -0.0f) value = 0.0f;

	std::stringstream ss;
	double i;
	double d = std::modf(value, &i);

	// ��������0�̂Ƃ��͏����P���A����ȊO�͏����U���ɂ���B
	// �؂�̂Ă��鏬�����͎l�̌ܓ������
	int nd = (d == 0.0) ? 0 : 1;
	ss << std::setprecision(nd) << std::setiosflags(std::ios::fixed);

	ss << value;
	return ss.str();
}
