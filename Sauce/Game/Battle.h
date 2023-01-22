#pragma once

class Battle
{
public:
    Battle() {}
    ~Battle() {}

    void Update(float elapsedTime);
    void Render(float elapsedTime);

    void PlayrBattle();
    void EnemyBattle();
};