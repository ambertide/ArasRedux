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

void Character::start_attacking_to(Character &other)
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

void Character::start_walking_to(const Vector3<float> &position)
{
    assert(this->can_walk());
    this->target_position = position;
    // Set it to start walking.
    this->state = State::WALKING;
}

const Vector3<float> &Character::calculate_step() const
{
    const auto &diff = this->target_position - this->position();
    const Vector3<float> &step = diff / diff.norm();
    return step;
}

void Character::tick(int delta)
{
    // If the state is walking, continue walking towards the target_position.
    if (this->state == State::WALKING)
    {
        auto &step = this->calculate_step();
        Vector3<float> effectiveStep = step * delta;
        this->position() += effectiveStep;
        // If the character has arrived, stop walking.
        if (this->position() == this->target_position)
        {
            this->state = State::IDLE;
        }
    }
}
