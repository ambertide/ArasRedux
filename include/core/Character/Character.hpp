#include <queue>
#include <optional>
#include <memory>
#include "../Object/Object.hpp"
#include "../Object/Vector3.hpp"
#include "../Temporal.hpp"
#include "State.hpp"
#include "Action.hpp"
#include "Hurtable.hpp"
namespace core
{
    class Character : public Object, public Temporal, private Hurtable
    {
    private:
        State state;
        Vector3<float> speed;
        /** Current action the character is taking */
        std::optional<std::shared_ptr<Action>> current_action;
        /** Pending actions of the player. */
        std::queue<std::shared_ptr<Action>> action_queue;
        float attack_;

        /**
         * @brief Get the unit step that must be taken towards target.
         *
         * Get the unit step that the character must take towards a target
         * position.
         *
         * @param target: Target to walk to.
         * @return const Vector3<float>& reference to the step.
         */
        const Vector3<float> &calculate_step(const Vector3<float> &target) const;

        /**
         * @brief Walk to another position.
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

    public:
        void die();

        /**
         * @brief Check if a character is in a busy state.
         *
         *
         * @return true if the character is not attacking, dying or dead.
         * @return false otherwise.
         */
        bool can_attack();

        /**
         * @brief Get the attack point of the character.
         *
         * @return float
         */
        const float &attack() const;

        /**
         * @brief Check if a character can walk/run
         *
         * @return true if the character can walk, ie: in IDLE or WALK.
         * @return false otherwise.
         */
        bool can_walk();

        void tick(int delta) override;

        /**
         * @brief Add an action for the character to take.
         *
         * @param action
         */
        void enqueue_action(std::shared_ptr<Action> action);

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
        Character(uint64_t id, Vector3<float> position, float health);
    };
};