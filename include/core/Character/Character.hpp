#include <Object.hpp>
#include <State.hpp>
#include <Vector3.hpp>

namespace core
{
    class Character : public Object
    {
    private:
        State state;
        Vector3<float> speed;
        float health;


    public : void die();
        /**
         * @brief Attack to another character.
         *
         * @param character
         */
        void attack(const Character &character);

        /**
         * @brief Walk to another position.
         *
         * @param position Position to walk to.
         * @return true if the character has arrived to
         * the position in this tick.
         */
        bool walk_to(const Vector3<float> position);

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