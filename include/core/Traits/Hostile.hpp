#pragma once
#include <list>
#include <memory>
#include "../Object/Object.hpp"

namespace core
{

    /**
     * @brief Struct to contain attack values.
     *
     */
    struct AttackValuesTuple
    {
        const float point;
        const float range;
    };

    struct AttackModifier
    {
        /**
         * @brief Object doing the modifying.
         *
         */
        const Object &object;
        const float modify_attack_point_by;
        const float modify_attack_range_by;
    };

    /**
     * @brief Those that are able to attack.
     *
     */
    class Hostile
    {
    private:
        /**
         * @brief Calculate the attack values based on modifiers.
         *
         * @return AttackValuesTuple
         */
        AttackValuesTuple calculate_attack_values() const;

    protected:
        const float base_attack_point;
        const float base_attack_range;
        float attack_point_;
        float attack_range_;
        std::list<AttackModifier> attack_modifiers_;

    public:
        /**
         * @brief Number by which to multiply the attack.
         *
         */
        float attack_multiplier = 1.0f;

        explicit Hostile(const float base_attack_point, const float base_attack_range) : base_attack_point(base_attack_point), base_attack_range(base_attack_range) {}

        /** Get the attack value of the hostile. */
        const float &attack_point() const;

        /** Get the attack range of the hostile. */
        const float &attack_range() const;

        /**
         * @brief Add an attack modifier to the Hostile object.
         *
         * @param modifier
         */
        void add_attack_modifier(const AttackModifier &modifier);

        /**
         * @brief Remove the modifier with the given id.
         *
         * @param id
         */
        void remove_attack_modifier(const uint64_t id);

        const std::list<AttackModifier> &attack_modifiers() const;

        virtual ~Hostile();
    };
};