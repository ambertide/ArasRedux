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
        /** Current health v*/
        int health;

        Hurtable(int max_health, int health);
        ~Hurtable();

        virtual void hurt(int amount);
        virtual void heal(int amount);
    };
}