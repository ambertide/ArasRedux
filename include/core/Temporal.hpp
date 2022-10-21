#pragma once
namespace core
{

    /**
     * @brief a game object that feels the passage of time.
     *
     */
    class Temporal
    {
    public:
        /**
         * @brief Pass the time, take the actions.
         *
         * Take actions that depend on the passing time.
         * @param delta amount of ticks that passed.
         */
        virtual void tick(int delta) = 0;
    };
};