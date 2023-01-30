#pragma once
#include<vector>

enum GameState
{
	Play,
	Paused,
	Quit
};

// シーン
class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	// 初期化
	virtual void Initialize() = 0;

	// 終了化
	virtual void Finalize() = 0;

	// 更新処理
	virtual void Update(float elapsedTime) = 0;
	virtual void ProcessInput() = 0;

	// 描画処理
	virtual void Render() = 0;
	virtual void RenderImGui() {};

	// 準備完了しているか
	bool IsReady() const { return ready; }

	// 準備完了設定
	void SetReady() { ready = true; }

	auto GetGameState() const { return this->gState; }
	void SetGameState(auto state) { gState = state; }

private:
	bool	ready = false;

	GameState gState = GameState::Play;
};
