#pragma once
#include "GraphicsService.hpp"

namespace services
{
    /**
     * @brief Simple graphics using the terminal.
     *
     */
    class TerminalGraphicsService final : public GraphicsService
    {
    private:
        /* data */
    public:
        TerminalGraphicsService(/* args */);
        ~TerminalGraphicsService();
    };

    TerminalGraphicsService::TerminalGraphicsService(/* args */)
    {
    }

    TerminalGraphicsService::~TerminalGraphicsService()
    {
    }

} // namespace service
