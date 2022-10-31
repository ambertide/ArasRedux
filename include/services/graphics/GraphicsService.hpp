#pragma once
#include <atomic>
#include <memory>
#include "../../core/Object/Object.hpp"
#include "../../core/Map/Level.hpp"

namespace services
{
    class GraphicsService
    {
    protected:
        std::shared_ptr<core::Level> current_level;

        /**
         * @brief Draw a locatable object to the screen.
         *
         * @param locatable
         */
        virtual void draw(const core::Object &locatable);

    public:
        GraphicsService(/* args */){};
        virtual ~GraphicsService() = 0;

        /**
         * @brief Set the level object
         *
         * @param level
         */
        void set_level(const std::shared_ptr<core::Level> level)
        {
            this->current_level = level;
        }

        /**
         * @brief Start the mainloop of the graphics service.
         *
         */
        virtual void mainloop() = 0;

        /**
         * @brief Check if the given service is available for this device.
         *
         * @return true if the service is available
         * @return false if the service is not available
         */
        virtual bool available() const = 0;
    };
};