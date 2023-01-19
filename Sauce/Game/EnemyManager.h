#pragma once
#include<vector>
#include<set>
#include"Enemy.h"

class EnemyManager
{
private:
    EnemyManager() {}
    ~EnemyManager() {}

public:
    // �C���X�^���X�擾
    static EnemyManager& Instance()
    {
        static EnemyManager instance;
        return instance;
    }

    // �X�V����
    void Update(float elapsedTime);
    // �`�揈��
    void Render(float elapsedTime);

    void Register(Enemy* enemy);
    void Clear();
    void Remove(Enemy* enemy);
    int GetEnemyCount() const { return static_cast<int>(enemies.size()); }
    Enemy* GetEnemy(int index) { return enemies.at(index); }

private:
    std::vector<Enemy*> enemies;
    std::set<Enemy*> removes;
};