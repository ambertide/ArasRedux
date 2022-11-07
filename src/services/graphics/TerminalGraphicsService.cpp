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
    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_BLUE, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);
    }
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
    mvwprintw(this->stats_window, 8, 2, "Player is at: (%d, %d)", player.position().x, player.position().y);
}

void services::TerminalGraphicsService::render_player()
{
    int center_y = LINES / 2;
    int center_x = COLS / 2;
    attron(COLOR_PAIR(1));
    mvprintw(center_y, center_x, "P");
    attroff(COLOR_PAIR(1));
}

bool services::TerminalGraphicsService::available() const
{
    return true;
}

void services::TerminalGraphicsService::render(core::Locatable *locatable, const char *character)
{
    auto &player = this->current_level->player();

    // Center in terms of real space.
    auto centre = player.position();

    int centre_x = COLS / 2;
    int centre_y = LINES / 2;

    // Calculate the offsets in terms of screen.
    int offset_x = (centre.x - locatable->position().x) / this->grid_size;
    int offset_y = (centre.y - locatable->position().y) / this->grid_size;

    mvprintw(centre_y + offset_y, centre_x + offset_x, character);
}

void services::TerminalGraphicsService::render(core::Object *object)
{
    switch (object->object_type())
    {
    case core::ObjectType::CHARACTER:
        this->render(static_cast<core::Character *>(object));
        break;

    default:
        attron(COLOR_PAIR(2));
        this->render(object, "O");
        attroff(COLOR_PAIR(2));
        break;
    }
}

void services::TerminalGraphicsService::render(core::Character *character)
{
    attron(COLOR_PAIR(3));
    this->render(character, "C");
    attroff(COLOR_PAIR(3));
}

void services::TerminalGraphicsService::render_objects()
{
    // Get objects in the player's range.
    auto objects = this->current_level->objects_within_range(
        this->current_level->player(),
        this->current_level->player().notice_range());
    for (auto object : objects)
    {
        this->render(object.get());
    }
}

void services::TerminalGraphicsService::mainloop()
{
    this->init_screen();
    int char_input;
    do
    {
        char_input = getch();
        this->render_player();
        this->render_objects();
        refresh();
        this->print_player_stats();
        mvwprintw(this->stats_window, 4, 60, "Pressing: %d", char_input);
        wrefresh(this->stats_window);
    } while (char_input != 127);
    this->release_screen();
}

#else

void services::TerminalGraphicsService::mainloop() {}
bool services::TerminalGraphicsService::available() const
{
    return false;
}
#endif