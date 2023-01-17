#include"../Graphics/Graphic.h"
#include"SceneManager.h"
#include"SceneLoading.h"
#include"Scene_Title.h"
#include"Scene_Game.h"
#include"Scene_Shop.h"
#include"Scene_Battle.h"

// 更新処理
void SceneManager::Update(float elapsedTime)
{
	if (nextScene != nullptr)
	{
		// 古いシーンを終了処理
		Clear();

		// 新しいシーンを設定
		currentScene = nextScene;
		nextScene = nullptr;

		// シーン初期化処理
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

// 描画処理
void SceneManager::Render()
{
	imGuiSceneChanger();

	if (currentScene != nullptr)
	{
		currentScene->Render();
	}
}

// シーンクリア
void SceneManager::Clear()
{
	if (currentScene != nullptr)
	{
		currentScene->Finalize();
		delete currentScene;
		currentScene = nullptr;
	}
}

// シーン切り替え
void SceneManager::ChangeScene(Scene* scene)
{
	nextScene = scene;
}

// ImGUIによるシーン切り替え
void SceneManager::imGuiSceneChanger()
{
#if _DEBUG
	ImGui::Begin("Scene");
	if (ImGui::Button("Title"))
	{
		ChangeScene(new SceneLoading(new SceneTitle));
	}
	if (ImGui::Button("Game"))
	{
		ChangeScene(new SceneLoading(new SceneGame));
	}
	if (ImGui::Button("Shop"))
	{
		ChangeScene(new SceneLoading(new SceneShop));
	}
	if (ImGui::Button("Battle"))
	{
		ChangeScene(new SceneLoading(new SceneBattle));
	}
	ImGui::End();
#endif
}