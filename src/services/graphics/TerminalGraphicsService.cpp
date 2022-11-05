#include <services/graphics/TerminalGraphicsService.hpp>
#include <core/Character/Action.hpp>

#ifdef NCURSES_ENABLED

void services::TerminalGraphicsService::init_screen()
{
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    nonl();
    // Initiate the stats window
    refresh();
    this->stats_window = newwin(15, COLS, LINES - 15, 0);
    box(this->stats_window, 0, 0);
    wrefresh(this->stats_window);
    timeout(1);
}

void services::TerminalGraphicsService::release_screen()
{
    endwin();
    delwin(this->stats_window);
}

void services::TerminalGraphicsService::print_player_stats()
{
    auto &player = this->current_level->player();
    auto current_action = player.current_action();
    std::string current_action_string = current_action == nullptr ? "NOTHING" : core::convert_action_type(current_action->type_);
    mvwprintw(this->stats_window, 4, 2, "Health: %d / %d", player.health, player.max_health);
    mvwprintw(this->stats_window, 5, 2, "Attack: %d", player.attack_point());
    mvwprintw(this->stats_window, 6, 2, "Range: ", player.attack_range());
    mvwprintw(this->stats_window, 7, 2, "Currently Undertaking: %s", current_action_string.c_str());
}

void services::TerminalGraphicsService::mainloop()
{
    this->init_screen();
    int char_input;
    do
    {
        char_input = getch();
        refresh();
        this->print_player_stats();
        mvwprintw(this->stats_window, 8, 2, "Pressing: %d", char_input);
        wrefresh(this->stats_window);
    } while (char_input != 127);
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