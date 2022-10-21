#include <assert.h>
#include <core/Character/Character.hpp>

using namespace core;

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
        target.hurt(this->attack_point());
        // Now that we attacked, we can reset our action.
        this->current_action.reset();
    }
}

void Character::target(int delta)
{
    auto action = this->current_action.value();
    auto &target = std::static_pointer_cast<AttackAction>(action)->target;
    if (Vector3<float>::point_distance(target.position(), this->position_) > this->attack_range())
    {
        // Try to get in range.
        this->walk(delta, target.position());
    }
    else
    {
        // If already in range, attack!
        this->attack_();
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

void Character::walk(int delta, const Vector3<float> &target)
{
    auto &step = this->calculate_step(target);
    Vector3<float> effectiveStep = step * delta;
    this->position() += effectiveStep;
}

void Character::walk(int delta)
{
    auto action = this->current_action.value();
    if (this->can_walk())
    {
        auto &target = std::static_pointer_cast<WalkAction>(action)->target;
        this->walk(delta, target);
        if (this->position() == target)
        {
            // Arrived at our destination.
            this->current_action.reset();
        }
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

    switch (action->type_)
    {
    case ActionType::WALK:
        this->walk(delta);
        break;
    case ActionType::ATTACK:
        this->target(delta);
    default:
        break;
    }
}
// If the state is walking, continue walking towards the target_position.
