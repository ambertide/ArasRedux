#include <memory>
#include <thread>
#include <core/Map/Level.hpp>
#include <services/ServiceLocator.hpp>
#include <services/graphics/TerminalGraphicsService.hpp>

void graphics_mainloop(services::GraphicsService &graphics_service)
{
    graphics_service.mainloop();
}

int main()
{
    // Construct services.
    auto service_locator = std::make_shared<services::ServiceLocator>();
    auto graphics_service = std::make_unique<services::TerminalGraphicsService>();
    service_locator->provide(std::move(graphics_service));

    // Generate the main level and load it to the services.
    auto main_level = std::make_shared<core::Level>();
    service_locator->graphics().set_level(main_level);

    // Execute the graphics routines in a new thread.
    std::thread graphics_thread(graphics_mainloop, std::ref(service_locator->graphics()));
}