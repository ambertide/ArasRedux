#include <assert.h>
#include <Character/Character.hpp>

using namespace core;

Character::Character(uint64_t id, Vector3<float> position, float health) : Object::Object(id, position), Hurtable(100, health)
{
    this->state = State::IDLE;
}

bool Character::can_attack()
{
    auto state = this->state;
    return state == State::IDLE || state == State::WALKING || state == State::ALERT;
}

void Character::attack_()
{
    auto action = this->current_action.value();
    auto &target = std::static_pointer_cast<AttackAction>(action)->target;
    if (this->can_attack())
    {
        target.hurt(this->attack());
    }
}

bool Character::can_walk()
{
    auto state = this->state;
    return state == State::IDLE || state == State::WALKING || state == State::ALERT;
}

const Vector3<float> &Character::calculate_step(const Vector3<float> &target) const
{
    const auto &diff = target - this->position();
    const Vector3<float> &step = diff / diff.norm();
    return step;
}

void Character::walk(int delta)
{
    auto action = this->current_action.value();
    if (this->can_walk())
    {
        auto &target = std::static_pointer_cast<WalkAction>(action)->target;
        auto &step = this->calculate_step(target);
        Vector3<float> effectiveStep = step * delta;
        this->position() += effectiveStep;
    }
    else
    {
        this->reset_actions();
    }
}

void Character::tick(int delta)
{
    auto action = this->current_action.value_or(nullptr);
    // Now get the next action if queue is not empty.
    if (action == nullptr && !this->action_queue.empty())
    {
        auto next_action = this->action_queue.front();
        this->action_queue.pop();
        // And place it as the current action.
        this->current_action.emplace(next_action);
        // Switch to action's state.
        this->state = this->current_action.value()->state;
    }
    else
    {
        // Switch the state to idle if we do not have any next action to take.
        this->state = State::IDLE;
        return;
    }
    switch (this->state)
    {
    case State::WALKING:
        this->walk(delta);
        break;
    case State::ATTACKING:
        this->attack();
    default:
        break;
    }

    // If the action requires termination, terminate it.
    // for walking this is when we reach destination,
    // meanwhile for attack, it is a one turn thing.
    if (action != nullptr && action->type_ == ActionType::ATTACK || action->type_ == ActionType::WALK && (std::static_pointer_cast<WalkAction>(action))->target == this->position())
    {
        this->current_action.reset();
    }
}
// If the state is walking, continue walking towards the target_position.
