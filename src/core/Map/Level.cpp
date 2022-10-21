#include <core/Map/Level.hpp>

using namespace core;

void Level::tick(int delta)
{
    for (auto &character : this->characters)
    {
        character.tick(delta);
    }
}