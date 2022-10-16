#include <list>
#include "../Temporal.hpp"
#include "../Character/Character.hpp"
#include "../Character/Player.hpp"
namespace core
{
    /**
     * @brief  a level object.
     *
     * Also controls the movement and behaviour of the enemies
     * around the player since the level *knows* its own layout.
     */
    class Level : public Temporal
    {
    private:
        Player &player;
        /**
         * @brief Characters in the level.
         *
         */
        std::list<Character> characters;

    public:
        virtual void tick(int delta) override;
    };
};
