#include <services/graphics/TerminalGraphicsService.hpp>

#ifdef NCURSES_ENABLED
// On *nix systems, the NCURSES comes enabled.
void services::TerminalGraphicsService::mainloop() {}

#else

void services::TerminalGraphicsService::mainloop() {}
#endif