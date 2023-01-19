#pragma once

class Character
{
public:
    Character() {};
    virtual ~Character() {};

    virtual void Update(float elapsedTime) = 0;
    virtual void Render(float elapsedTime) = 0;

    auto GetHP() const { return HP; }
    void SetHP(auto hp) { this->HP = hp; }

    auto GetMaxHP() const { return MaxHP; }
    void SetMaxHP(auto maxhp) { this->MaxHP = maxhp; }

    auto GetAttack() const { return Attack; }
    void SetAttack(auto attack) { this->Attack = attack; }

    auto GetDefense() const { return Defense; }
    void SetDefense(auto defense) { this->Defense = defense; }

    auto GetSpeed() const { return Speed; }
    void SetSpeed(auto speed) { this->Speed = speed; }

    bool ApplyDamage(int damage);

protected:
    virtual void OnDamaged() {}
    virtual void OnDead() {}

protected:
    int HP = 0;
    int MaxHP = 0;
    int Attack = 0;
    int Defense = 0;
    int Speed = 0;
};