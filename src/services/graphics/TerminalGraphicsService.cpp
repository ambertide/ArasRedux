#include <services/graphics/TerminalGraphicsService.hpp>

#ifdef NCURSES_ENABLED
// On *nix systems, the NCURSES comes enabled.
void services::TerminalGraphicsService::mainloop() {}
bool services::TerminalGraphicsService::available() const
{
    return true;
}

void services::TerminalGraphicsService::draw(const core::Object &object)
{
}

#else

void services::TerminalGraphicsService::mainloop() {}
bool services::TerminalGraphicsService::available() const
{
    return false;
}
#endif