#pragma once
namespace core
{
    /**
     * @brief Objects that are hurtable.
     *
     */
    class Hurtable
    {
    public:
        /** Maximum health of the object. */
        int max_health;
        /** Current health */
        int health;

        explicit Hurtable(int max_health, int health);
        virtual ~Hurtable() = default;

        virtual void hurt(int amount);
        virtual void heal(int amount);
    };
}