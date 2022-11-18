#include <assert.h>
#include <core/Character/Character.hpp>

using namespace core;

bool Character::can_attack()
{
    auto state = this->state;
    return state == State::IDLE || state == State::WALKING || state == State::ALERT;
}

void Character::next_action()
{
    this->actions.pop();
    auto next_action = this->current_action();
    if (next_action != nullptr)
    {
        this->state = next_action->state;
    }
    else
    {
        this->state = State::IDLE;
    }
}

const std::shared_ptr<Action> Character::current_action() const
{
    if (this->actions.empty())
    {
        return nullptr;
    }
    return this->actions.top();
}

void Character::attack_()
{
    auto action = this->current_action();
    auto &target = std::static_pointer_cast<AttackAction>(action)->target;
    if (this->can_attack())
    {
        target.hurt(this->attack_point());
        // Now that we attacked, we can reset our action.
        this->next_action();
    }
}

void Character::target(int delta)
{
    auto action = this->current_action();
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

const Vector3<float> Character::calculate_step(const Vector3<float> &target) const
{
    const auto &diff = target - this->position();
    const Vector3<float> step = diff / diff.norm();
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
    auto action = this->current_action();
    if (this->can_walk())
    {
        auto &target = std::static_pointer_cast<WalkAction>(action)->target;
        this->walk(delta, target);
        if (this->position() == target)
        {
            // Arrived at our destination.
            this->next_action();
        }
    }
    else
    {
        this->reset_actions();
    }
}

void Character::tick(int delta)
{
    if (!this->actions.empty()) {
        switch (this->current_action()->type_)
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
}

bool Character::is_attacking(const Targetable &target) const
{
    if (this->current_action()->type_ != ActionType::ATTACK)
    {
        return false;
    }
    auto action = std::static_pointer_cast<AttackAction>(this->current_action());
    return (&action->target == &target);
}

void Character::push_action(std::shared_ptr<Action> action)
{
    this->actions.push(action);
}

void Character::reset_actions()
{
    while (!this->actions.empty())
    {
        this->actions.pop();
    }
}
