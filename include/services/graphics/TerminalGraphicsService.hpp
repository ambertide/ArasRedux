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

        /**
         * @brief Draw a single character at the given location of the screen.
         *
         * @param x x location in the coord space.
         * @param y y location in the coord space
         * @param screen_centre centre of the screen in the coordinate space.
         * @param character character to draw.
         */
        void draw_at(const float x, const float y, const float screen_centre, std::string character);
        virtual void draw(const core::Object &object) override;
        virtual void init_screen() override;
        virtual void release_screen() override;
        virtual void print_player_stats() override;

    public:
        TerminalGraphicsService(/* args */) {}
        ~TerminalGraphicsService() = default;
        virtual void mainloop() override;
        virtual bool available() const override;
    };

} // namespace service
