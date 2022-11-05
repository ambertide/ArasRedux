#pragma once

#include "../services/ServiceLocator.hpp"
#include "../core/Map/Level.hpp"
#include <atomic>
#include <memory>

namespace game
{
    class Game
    {
    private:
        /** Set to true to signal game end. */
        std::atomic<bool> terminate;
        std::unique_ptr<services::ServiceLocator> services;
        std::shared_ptr<core::Level> level;

    public:
        Game(std::unique_ptr<services::ServiceLocator> services,
             std::shared_ptr<core::Level> level)
            : services(std::move(services)),
              level(level)
        {
            this->terminate.store(false);
        };
        ~Game() = default;

        /**
         * @brief Whether or not the game should be terminated.
         *
         * @return true
         * @return false
         */
        bool should_terminate() const { return this->terminate.load(); }

        /**
         * @brief Set the should terminate object
         *
         * @param should_terminate Determines whether the game should terminate.
         */
        void set_should_terminate(bool should_terminate) { this->terminate.store(should_terminate); }

        /**
         * @brief Get the current level being played.
         *
         * @return pointer to the currently played level.
         */
        std::shared_ptr<core::Level> current_level() const
        {
            return this->level;
        }

        /**
         * @brief Return the services locator.
         *
         * @return reference to the locator.
         */
        services::ServiceLocator &service_locator() const { return *this->services; }
    };
}
