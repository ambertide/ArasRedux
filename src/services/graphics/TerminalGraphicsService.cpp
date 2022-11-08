#include <services/graphics/TerminalGraphicsService.hpp>
#include <core/Character/Action.hpp>
#include <thread>
#include <chrono>

#ifdef NCURSES_ENABLED

void services::TerminalGraphicsService::init_screen()
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    nonl();
    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_BLUE, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);
        init_pair(4, COLOR_BLACK, COLOR_WHITE);
    }
    // Initiate the stats window
    refresh();
    this->stats_window = newwin(15, COLS, LINES - 15, 0);
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
    wbkgd(this->stats_window, COLOR_PAIR(4));
    box(this->stats_window, 0, 0);
    std::string current_action_string = current_action == nullptr ? "NOTHING" : core::convert_action_type(current_action->type_);
    mvwprintw(this->stats_window, 4, 2, "Health: %d / %d", player.health, player.max_health);
    mvwprintw(this->stats_window, 5, 2, "Attack: %f", player.attack_point());
    mvwprintw(this->stats_window, 6, 2, "Range: %f", player.attack_range());
    mvwprintw(this->stats_window, 7, 2, "Currently Undertaking: %s", current_action_string.c_str());
    mvwprintw(this->stats_window, 8, 2, "Player is at: (%f, %f)", player.position().x, player.position().y);
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
    int offset_x = (locatable->position().x - centre.x) / this->grid_size;
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

void services::TerminalGraphicsService::handle_user_input()
{
    const int user_input = getch();
    core::Vector3<float> move_vector{0.0f, 0.0f, 0.0f};
    core::Vector3<float> zero_vector(move_vector);
    if (user_input == KEY_UP)
    {
        move_vector.y = 1.0f;
    }
    else if (user_input == KEY_DOWN)
    {
        move_vector.y = -1.0f;
    }

    if (user_input == KEY_RIGHT)
    {
        move_vector.x = 1.0f;
    }

    else if (user_input == KEY_LEFT)
    {
        move_vector.x = -1.0f;
    }

    if (move_vector != zero_vector)
    {
        this->current_level->player().position() += move_vector;
    }

    switch (user_input)
    {
    case 0x27:
        this->should_terminate = true;
        break;
    default:
        break;
    }
}

void services::TerminalGraphicsService::mainloop()
{
    this->init_screen();
    do
    {
        this->handle_user_input();
        clear();
        this->render_player();
        this->render_objects();
        refresh();
        this->print_player_stats();
        wrefresh(this->stats_window);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(50ms);
    } while (!this->should_terminate);
    this->release_screen();
}

#else

void services::TerminalGraphicsService::mainloop() {}
bool services::TerminalGraphicsService::available() const
{
    return false;
}
#endif