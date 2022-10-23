#include <core/Map/Level.hpp>
#include <core/Object/Vector3.hpp>
#include <core/Character/Action.hpp>

using namespace core;

void Level::proccess_characters()
{
    for (auto character : this->characters)
    {
        if (Vector3<float>::point_distance(
                character->position(),
                this->player.position()) < character->notice_range() &&
            !character->is_attacking(this->player))

        {
            // If the player is close enough and character is not already targeting them
            // Target the player.
            // Create new attack action to attack the player
            auto action = std::make_shared<AttackAction>(player);
            // And push it to the action stack.
            character->push_action(action);
        }
    }
}

void Level::tick(int delta)
{
    this->proccess_characters();
    for (auto temporal : this->temporals)
    {
        temporal->tick(delta);
    }
}
