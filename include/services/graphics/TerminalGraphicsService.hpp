#pragma once
#include "GraphicsService.hpp"
#include <string>

#ifdef NCURSES_ENABLED
#include <ncurses.h>
#endif

namespace services
{
#ifndef NCURSES_ENABLED
    /** Empty window struct to avoid compile errors in non-ncurses systems.*/
    struct WINDOW
    {
    };
#endif
    /**
     * @brief Simple graphics using the terminal.
     *
     */
    class TerminalGraphicsService final : public GraphicsService
    {
    private:
        WINDOW *stats_window;
        const int grid_size;
        bool should_terminate = false;

        /**
         * @brief Render a locatable with a given character.
         *
         * @param locatable
         * @param character
         */
        void render(core::Locatable *locatable, const char *character);
        virtual void init_screen() override;
        virtual void release_screen() override;
        virtual void print_player_stats() override;
        virtual void render_player() override;
        virtual void render(core::Object *object) override;
        virtual void render(core::Character *character) override;
        virtual void render_objects() override;
        virtual void handle_user_input() override;

    public:
        TerminalGraphicsService(const int grid_size) : grid_size(grid_size) {}
        ~TerminalGraphicsService() = default;
        virtual void mainloop() override;
        virtual bool available() const override;
    };

} // namespace service
