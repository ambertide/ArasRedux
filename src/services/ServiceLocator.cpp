#include <services/ServiceLocator.hpp>
#include <services/graphics/NullGraphicsService.hpp>

services::ServiceLocator::ServiceLocator()
{
    // Initialise null services to use if none is defined.
    this->graphics_service = std::make_unique<NullGraphicsService>();
}

void services::ServiceLocator::provide(std::unique_ptr<GraphicsService> graphics)
{
    this->graphics_service = std::move(graphics);
}

services::GraphicsService &services::ServiceLocator::graphics() const
{
    return *this->graphics_service;
}