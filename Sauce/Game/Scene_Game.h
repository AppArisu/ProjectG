#pragma once
#include "Scene.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Font.h"

enum State
{
    Town,
    Shop,
    Battle,
    Quit
};

// �^�C�g���V�[��
class SceneGame :public Scene
{
public:
    SceneGame() {}
    ~SceneGame()override {}

    // ������
    void Initialize() override;

    // �I����
    void Finalize() override;

    // �X�V����
    void Update(float elapsedTime) override;

    // �`�揈��
    void Render() override;

    // �摜�`��
    void SpriteRender();

    // �����`��
    void FontRender();

    // �V�[���J��
    void Change(float elapsedTime, Scene* nextScene);

    // 
    void StateSelect(State state01, State state02);

    // �����������Ă��邩
    bool IsSelect() const { return select; }

    // ���������ݒ�
    void SetSelect(bool setSelect) { select = setSelect; }

private:
    int state = State::Town;

    bool select = false;

    // �t�H���g
    DirectWrite* Write = nullptr;

    Sprite* sprite = nullptr;
};