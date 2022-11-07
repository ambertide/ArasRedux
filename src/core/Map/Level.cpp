#include <core/Map/Level.hpp>
#include <core/Object/Vector3.hpp>
#include <core/Character/Action.hpp>

using namespace core;

void Level::proccess_characters()
{
    for (auto object : this->objects)
    {
        if (object->object_type() != ObjectType::CHARACTER)
        {
            continue;
        }
        auto character = std::static_pointer_cast<Character>(object);
        if (Vector3<float>::point_distance(
                character->position(),
                this->player().position()) < character->notice_range() &&
            !character->is_attacking(this->player()))

        {
            // If the player is close enough and character is not already targeting them
            // Target the player.
            // Create new attack action to attack the player
            auto action = std::make_shared<AttackAction>(this->player());
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

Player &Level::player()
{
    return this->player_;
}

const std::list<std::shared_ptr<Object>> Level::objects_within_range(const Locatable &centre, float range) const
{
    std::list<std::shared_ptr<Object>> objects_in_range;
    for (auto object : this->objects)
    {
        if (core::Vector3<float>::point_distance(centre.position(), object->position()) <= range)
        {
            objects_in_range.push_back(object);
        }
    }
    return objects_in_range;
}