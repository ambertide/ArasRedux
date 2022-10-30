#pragma once
#include <atomic>
#include <memory>
#include "../../core/Map/Level.hpp"

namespace services
{
    class GraphicsService
    {
    protected:
        std::atomic<std::shared_ptr<core::Level>> current_level;

    public:
        GraphicsService(/* args */);
        virtual ~GraphicsService() = 0;

        /**
         * @brief Set the level object
         *
         * @param level
         */
        void set_level(const std::atomic<std::shared_ptr<core::Level>> level)
        {
            this->current_level.store(level);
        }

        /**
         * @brief Start the mainloop of the graphics service.
         *
         */
        virtual void mainloop() = 0;
    };
};
