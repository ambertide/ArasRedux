#include "../Object/Object.hpp"
#include "../Object/Vector3.hpp"
#include "State.hpp"

namespace core
{
    class Character : public Object
    {
    private:
        State state;
        Vector3<float> speed;
        float health;
        float attack_;

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
        void attack_to(Character &other);

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
         * @return true if the character has arrived to
         * the position in this tick.
         */
        bool walk_to(const Vector3<float> &position);

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