#include "../Object/Object.hpp"
#include "../Object/Vector3.hpp"
#include "../Temporal.hpp"
#include "State.hpp"

namespace core
{
    class Character : public Object, public Temporal
    {
    private:
        State state;
        Vector3<float> speed;
        /**
         * @brief Position the character is walking to.
         *
         */
        Vector3<float> target_position;
        float health;
        float attack_;

        /**
         * @brief Walk towards the target_position.
         *
         * @param delta: Passed ticks.
         */
        void walk_to(int delta);

        /**
         * @brief Get the unit step that must be taken towards target.
         *
         * Get the unit step that the character must take towards a target
         * position.
         *
         * @return const Vector3<float>& reference to the step.
         */
        const Vector3<float> &calculate_step() const;

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
         * @brief Attack to another character.
         *
         * @param character
         */
        void start_attacking_to(Character &other);

        /**
         * @brief Check if a character can walk/run
         *
         * @return true if the character can walk, ie: in IDLE or WALK.
         * @return false otherwise.
         */
        bool can_walk();

        /**
         * @brief Walk to another position.
         *
         * @param position Position to walk to.
         */
        void start_walking_to(const Vector3<float> &position);

        void tick(int delta) override;

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