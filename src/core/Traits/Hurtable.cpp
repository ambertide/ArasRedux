#include <core/Traits/Hurtable.hpp>

using namespace core;

Hurtable::Hurtable(int max_health, int health) : max_health(max_health), health(health)
{
}

Hurtable::~Hurtable()
{
}

void Hurtable::heal(int amount)
{
    if (this->health + amount <= this->max_health)
    {
        this->health += amount;
    }
    else
    {
        this->health = max_health;
    }
}

void Hurtable::hurt(int amount)
{
    if (this->health -= amount >= 0)
    {
        this->health -= amount;
    }
    else
    {
        this->health = 0;
    }
}
