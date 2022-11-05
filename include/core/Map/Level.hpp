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
    class Level final : public Temporal
    {
    private:
        Player player_;

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

        /**
         * @brief Get the player object
         *
         * @return Player&
         */
        Player &player();
        Level(Player player, std::list<std::shared_ptr<Temporal>> temporals, std::list<std::shared_ptr<Character>> characters) : player_(player), temporals(temporals), characters(characters){};
    };
};
