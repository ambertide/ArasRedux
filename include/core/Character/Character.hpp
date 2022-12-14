#pragma once
#include <stack>
#include <optional>
#include <memory>
#include "../Object/Object.hpp"
#include "../Object/Vector3.hpp"
#include "../Traits/Temporal.hpp"
#include "State.hpp"
#include "Action.hpp"
#include "../Traits/Hurtable.hpp"
#include "../Traits/Targetable.hpp"
#include "../Traits/Hostile.hpp"
namespace core
{
    class Character : public Object, public Temporal, public Targetable, public Hostile
    {
    private:
        State state;
        Vector3<float> speed;
        /** Pending actions of the player. */
        std::stack<std::shared_ptr<Action>> actions;

        /**
         * @brief Get the unit step that must be taken towards target.
         *
         * Get the unit step that the character must take towards a target
         * position.
         *
         * @param target: Target to walk to.
         * @return const Vector3<float>& reference to the step.
         */
        const Vector3<float> calculate_step(const Vector3<float> &target) const;

        /**
         * @brief Walk to another position.
         *
         * @param delta
         * @param position
         */
        void walk(int delta, const Vector3<float> &position);

        /**
         * @brief Process walk action.
         *
         * @param delta Passed ticks
         */
        void walk(int delta);

        /**
         * @brief Attack to another character.
         *
         * @param character
         */
        void attack_();

        /**
         * @brief Target another character.
         *
         * Walk towards the character until it is in range,
         * then attack it.
         *
         * @param delta Time passed until we reach the target.
         */
        void target(int delta);

        /**
         * @brief Stop executing the current action and switch to next.
         *
         */
        void next_action();

    public:
        void die();

        /**
         * @brief Check if the character is attacking this target.
         *
         * @param target Target to check against.
         * @return true
         * @return false
         */
        bool is_attacking(const Targetable &target) const;

        /**
         * @brief Check if a character is in a busy state.
         *
         *
         * @return true if the character is not attacking, dying or dead.
         * @return false otherwise.
         */
        bool can_attack();

        /**
         * @brief Check if a character can walk/run
         *
         * @return true if the character can walk, ie: in IDLE or WALK.
         * @return false otherwise.
         */
        bool can_walk();

        void tick(int delta) override;

        /**
         * @brief Get the current action being executed by the player.
         *
         */
        const std::shared_ptr<Action> current_action() const;

        /**
         * @brief Add an action for the character to take.
         *
         * @param action
         */
        void push_action(std::shared_ptr<Action> action);

        /**
         * @brief Reset the action queue of the player.
         */
        void reset_actions();

        /**
         * @brief Construct a new Character object
         *
         * @param id
         * @param position
         * @param health
         */
        Character(
            uint32_t class_id,
            uint64_t id,
            const std::string name,
            Vector3<float> position,
            Vector3<float> speed,
            float health,
            float attack,
            float range,
            float notice_range,
            const ObjectType object_type = ObjectType::CHARACTER)
            : Locatable(position),
              Object::Object(class_id, id, name, position, object_type),
              Targetable::Targetable(position, health, health),
              Hostile::Hostile(attack, range, notice_range),
              state(State::IDLE),
              speed(speed)
        {
        }
    };
};