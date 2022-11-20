#pragma once
#include "Character.hpp"

namespace core
{
    class Player : public Character
    {
    private:
        /* data */
    public:
        Player() : Locatable({0, 0, 0}), Character(0, 0, "Player", {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 50, 0.5f, 0.5f, 500.0f, ObjectType::PLAYER){};
        ~Player() = default;
    };
};