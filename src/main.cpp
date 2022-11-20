#include <memory>
#include <thread>
#include <chrono>
#include <iostream>
#include <core/Map/Level.hpp>
#include <core/Character/Player.hpp>
#include <core/Character/Character.hpp>
#include <core/Traits/Temporal.hpp>
#include <services/ServiceLocator.hpp>
#include <services/graphics/TerminalGraphicsService.hpp>
#include <game/Game.hpp>

void game_mainloop(game::Game &game)
{
    while (!game.should_terminate())
    {
        using namespace std::chrono_literals;
        game.current_level()->tick(1);
        std::this_thread::sleep_for(1000ms);
    }
}

void graphics_mainloop(services::GraphicsService &graphics)
{
    graphics.mainloop();
}

int main()
{
    // Construct services.
    auto service_locator = std::make_unique<services::ServiceLocator>();
    auto graphics_service = std::make_unique<services::TerminalGraphicsService>(1);
    service_locator->provide(std::move(graphics_service));

    std::list<std::shared_ptr<core::Temporal>> temporals;
    std::list<std::shared_ptr<core::Object>> objects;
    auto object = std::make_shared<core::Object>(1, 2, "Grail", core::Vector3{7.0f, 10.0f, 0.0f});
    auto character = std::make_shared<core::Character>(2, 43, "Basic Enemy", core::Vector3{-15.0f, 15.0f, 0.0f}, core::Vector3{1.0f, 1.0f, 0.0f}, 25.0f, 0.5f, 5.0f, 1.0f);
    objects.push_back(object);
    objects.push_back(character);
    temporals.push_back(character);
    core::Player player;
    // Generate the main level and load it to the services.
    auto main_level = std::make_shared<core::Level>(player, temporals, objects);
    game::Game game(std::move(service_locator), main_level);
    game.service_locator().graphics().set_level(main_level);

    // Execute the game logic in a new thread since some
    // Graphics services need to own the main thread to
    // work properly.
    std::thread game_thread(game_mainloop, std::ref(game));
    graphics_mainloop(game.service_locator().graphics());
    game.set_should_terminate(true);
    game_thread.join();
}