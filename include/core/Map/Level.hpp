#pragma once
#include <list>
#include <memory>
#include "../Traits/Temporal.hpp"
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
         * @brief All time affected entities in the level.
         *
         */
        std::list<std::shared_ptr<Temporal>> temporals;

        /**
         * @brief NPCs in the level, shares members with above.
         *
         */
        std::list<std::shared_ptr<Character>> characters;

        /**
         * @brief Run character AI and decision routines.
         *
         */
        void proccess_characters();

    public:
        virtual void tick(int delta) override;
    };
};
