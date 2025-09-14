#include <ncurses.h>
#include <chrono>
#include <thread>
#include <time.h>
#include <random>
#include <vector>

typedef unsigned short ushort;

const char *SKULL_ASCII =
    "                 uuuuuuu                      \n"
    "             uu$$$$$$$$$$$uu                  \n"
    "          uu$$$$$$$$$$$$$$$$$uu               \n"
    "         u$$$$$$$$$$$$$$$$$$$$$u              \n"
    "        u$$$$$$$$$$$$$$$$$$$$$$$u             \n"
    "       u$$$$$$$$$$$$$$$$$$$$$$$$$u            \n"
    "       u$$$$$$$$$$$$$$$$$$$$$$$$$u            \n"
    "       u$$$$$$\"   \"$$$\"   \"$$$$$$u        \n"
    "       \"$$$$\"      u$u       $$$$\"         \n"
    "        $$$u       u$u       u$$$             \n"
    "        $$$u      u$$$u      u$$$             \n"
    "         \"$$$$uu$$$   $$$uu$$$$\"            \n"
    "          \"$$$$$$$\"   \"$$$$$$$\"           \n"
    "            u$$$$$$$u$$$$$$$u                 \n"
    "             u$\"$\"$\"$\"$\"$\"$u            \n"
    "  uuu        $$u$ $ $ $ $u$$       uuu        \n"
    " u$$$$        $$$$$u$u$u$$$       u$$$$       \n"
    "  $$$$$uu      \"$$$$$$$$$\"     uu$$$$$$     \n"
    "u$$$$$$$$$$$uu    \"\"\"\"\"    uuuu$$$$$$$$$$\n"
    "$$$$\"\"\"$$$$$$$$$$uuu   uu$$$$$$$$$\"\"\"$$$\n"
    " \"\"\"      \"\"$$$$$$$$$$$uu \"\"$\"\"\"    \n"
    "           uuuu \"\"$$$$$$$$$$uuu             \n"
    "  u$$$uuu$$$$$$$$$uu \"\"$$$$$$$$$$$uuu$$$    \n"
    "  $$$$$$$$$$\"\"\"\"           \"\"$$$$$$$$$$$\n"
    "   \"$$$$$\"                      \"\"$$$$\"\"\n"
    "     $$$\"                         $$$$\"       ";

constexpr ushort STD_COLORS = 1,
                 SKULL_COLORS = 2,
                 TEXT_BAR_COLORS = 3,
                 BAR_COLORS = 4,
                 PANEL_COLORS = 5;

const std::vector<std::string> PALABRAS_CLAVE{"Tecmilenio", "Servidores VPN", "ARPs", "firewalls", "compilador", "CND", "BBVA", "ALIENS", "FBI", "SI"};

int main()
{
    srand((unsigned)time(nullptr));

    initscr();
    start_color();
    init_pair(STD_COLORS, COLOR_WHITE, COLOR_BLACK);
    init_pair(SKULL_COLORS, COLOR_RED, COLOR_BLACK);
    init_pair(TEXT_BAR_COLORS, COLOR_WHITE, COLOR_YELLOW);
    init_pair(PANEL_COLORS, COLOR_GREEN, COLOR_BLACK);
    init_pair(BAR_COLORS, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(STD_COLORS));

    // bar configs
    WINDOW *bar = newwin(3, COLS, LINES - 3, 0);
    wbkgd(bar, COLOR_PAIR(BAR_COLORS));
    box(bar, 0, 0);

    // skull configs
    WINDOW *skull = newwin(26, 48, 0, 0);
    wbkgd(skull, COLOR_PAIR(SKULL_COLORS));

    // panel configs
    WINDOW *panel = newwin(LINES - 3, COLS - 49, 0, 49);
    wbkgd(panel, COLOR_PAIR(PANEL_COLORS));
    box(panel, 0, 0);

    wprintw(skull, "%s", SKULL_ASCII);
    wprintw(panel, "Registros de propagación del ransomware ");

    std::thread bar_filling([&]() -> void
                            {
        wmove(bar, 1,1);

        for (ushort i = 0; i < COLS - 2; i++) {
            refresh();
            wrefresh(panel);
            wrefresh(skull);
            wrefresh(bar);
            std::this_thread::sleep_for(std::chrono::duration<float>((rand() % 5) / 10.0f));
            wattron(bar,COLOR_PAIR(TEXT_BAR_COLORS));
            wprintw(bar, " ");
            wattroff(bar, COLOR_PAIR(TEXT_BAR_COLORS));
        } });

    wmove(panel, 1, 2);

    for (ushort i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        wprintw(panel, "hackeando %s... ", PALABRAS_CLAVE.at(i).c_str());
        wmove(panel, i + 1, 2);
    }

    bar_filling.join();

    refresh();
    wrefresh(panel);
    wrefresh(skull);
    wrefresh(bar);

    getch();

    endwin();

    return 0;
}