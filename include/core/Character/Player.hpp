#pragma once
#include "Character.hpp"

namespace core
{
    class Player : public Character
    {
    private:
        /* data */
    public:
        Player() : Character(0, 0, "Player", {0, 0, 0}, {1, 1, 1}, 50, 0.5f, 0.5f, 0.5f), Locatable({0, 0, 0}){};
        ~Player() = default;
    };
};