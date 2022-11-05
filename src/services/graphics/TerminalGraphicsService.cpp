#include <services/graphics/TerminalGraphicsService.hpp>

#ifdef NCURSES_ENABLED
#include <ncurses.h>

void services::TerminalGraphicsService::init_screen()
{
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();
}

void services::TerminalGraphicsService::release_screen()
{
    endwin();
}

// On *nix systems, the NCURSES comes enabled.
void services::TerminalGraphicsService::mainloop()
{
    this->init_screen();
    mvprintw(0, 0, "Working...");
    refresh();
    getch();
    this->release_screen();
}
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