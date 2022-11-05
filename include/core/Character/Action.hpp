#pragma once
#include "../Object/Vector3.hpp"
#include "State.hpp"
#include "../Traits/Targetable.hpp"
namespace core
{
    /**
     * @brief Type of the action.
     *
     */
    enum ActionType
    {
        WALK,
        ATTACK
    };

    inline const std::string convert_action_type(ActionType type)
    {
        switch (type)
        {
        case WALK:
            return "WALK";
        case ATTACK:
            return "ATTACK";
        }
    }

    struct Action
    {
        /** Type of the action. */
        const ActionType type_;
        /** The state of the character during action. */
        const State state;
        Action(const ActionType type_, const State state) : type_(type_), state(state) {}
    };

    struct WalkAction : public Action
    {
        /** Target location to walk. */
        const Vector3<float> &target;
        WalkAction(const Vector3<float> &target) : Action(ActionType::WALK, State::WALKING), target(target) {}
    };

    struct AttackAction : public Action
    {
        /** Target entity to attack */
        Targetable &target;
        AttackAction(Targetable &target) : Action(ActionType::ATTACK, State::ATTACKING), target(target) {}
    };
};
