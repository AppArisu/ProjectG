#include"Graphics/Graphic.h"
#include"Scene_Manager.h"

// �X�V����
void SceneManager::Update(float elapsedTime)
{
	if (nextScene != nullptr)
	{
		// �Â��V�[�����I������
		Clear();

		// �V�����V�[����ݒ�
		currentScene = nextScene;
		nextScene = nullptr;

		// �V�[������������
		if (!currentScene->IsReady())
		{
			currentScene->Initialize();
		}
	}

	if (currentScene != nullptr)
	{
		currentScene->Update(elapsedTime);
	}
}

// �`�揈��
void SceneManager::Render()
{
	imGuiSceneChanger();

	if (currentScene != nullptr)
	{
		currentScene->Render();
	}
}

// �V�[���N���A
void SceneManager::Clear()
{
	if (currentScene != nullptr)
	{
		currentScene->Finalize();
		delete currentScene;
		currentScene = nullptr;
	}
}

// �V�[���؂�ւ�
void SceneManager::ChangeScene(Scene* scene)
{
	nextScene = scene;
}

// ImGUI�ɂ��V�[���؂�ւ�
void SceneManager::imGuiSceneChanger()
{
#if _DEBUG
#endif
}