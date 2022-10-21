#include <core/Traits/Hostile.hpp>

using namespace core;

AttackValuesTuple Hostile::calculate_attack_values() const
{
    float point = this->base_attack_point;
    float range = this->base_attack_range;
    for (auto &modifier : this->attack_modifiers())
    {
        point += modifier.modify_attack_point_by;
        range += modifier.modify_attack_range_by;
    }
    return {point * this->attack_multiplier, range};
}

const float &Hostile::attack_point() const
{
    return this->attack_point_;
}

const float &Hostile::attack_range() const
{
    return this->attack_range_;
}

const std::list<AttackModifier> &Hostile::attack_modifiers() const
{
    return this->attack_modifiers_;
}

void Hostile::add_attack_modifier(const AttackModifier &modifier)
{
    this->attack_modifiers_.push_back(modifier);
    // Recalculate values after change
    auto new_values = this->calculate_attack_values();
    this->attack_point_ = new_values.point;
    this->attack_range_ = new_values.range;
}

void Hostile::remove_attack_modifier(const uint64_t id_)
{
    this->attack_modifiers_.remove_if(
        [id_](AttackModifier modifier)
        { return modifier.object.id() == id_; });
    // Recalculate values after change
    auto new_values = this->calculate_attack_values();
    this->attack_point_ = new_values.point;
    this->attack_range_ = new_values.range;
}
