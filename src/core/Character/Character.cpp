#include <assert.h>
#include <Character/Character.hpp>

using namespace core;

Character::Character(uint64_t id, Vector3<float> position, float health) : Object::Object(id, position)
{
    this->health = health;
}

bool Character::can_attack()
{
    auto state = this->state;
    return state == State::IDLE || state == State::WALKING || state == State::ALERT;
}

void Character::attack_to(Character &other)
{
    assert(this->can_attack());
    this->state = State::ATTACKING;
    other.health -= this->attack();
}

bool Character::can_walk()
{
    auto state = this->state;
    return state == State::IDLE || state == State::WALKING || state == State::ALERT;
}

bool Character::walk_to(const Vector3<float> &position)
{
    assert(this->can_walk());
    this->position() += this->speed;
    if (this->position() == position)
    {
        return true;
    }
    return false;
}
