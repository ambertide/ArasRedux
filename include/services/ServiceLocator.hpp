#pragma once

#include "graphics/GraphicsService.hpp"
#include <memory>

namespace services
{
    class ServiceLocator
    {
    private:
        std::unique_ptr<GraphicsService> graphics_service;

    public:
        ServiceLocator();
        ~ServiceLocator();

        /**
         * @brief Return a reference to a graphics service.
         *
         * @return GraphicsService& reference to graphics service.
         */
        GraphicsService &graphics() const;

        /**
         * @brief Register a graphics service.
         *
         * @param graphics
         */
        void provide(std::unique_ptr<GraphicsService> graphics);
    };
}