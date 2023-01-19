#include "Character.h"

bool Character::ApplyDamage(int damage)
{
    if (damage == 0 || HP <= 0) return false;

    // ダメージ処理
    HP -= damage;

    // 死亡orダメージ
    if (HP <= 0)
    {
        OnDead();
    }
    else
    {
        OnDamaged();
    }

    return true;
}
