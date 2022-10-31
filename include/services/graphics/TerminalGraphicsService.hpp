#pragma once
#include "GraphicsService.hpp"
#include <string>

namespace services
{
    /**
     * @brief Simple graphics using the terminal.
     *
     */
    class TerminalGraphicsService final : public GraphicsService
    {
    private:
        /**
         * @brief Draw a single character at the given location of the screen.
         *
         * @param x x location in the coord space.
         * @param y y location in the coord space
         * @param screen_centre centre of the screen in the coordinate space.
         * @param character character to draw.
         */
        void draw_at(const float x, const float y, const float screen_centre, std::string character);

    public:
        TerminalGraphicsService(/* args */);
        ~TerminalGraphicsService();
        virtual void mainloop() override;
        virtual bool available() const override;
    };

} // namespace service
