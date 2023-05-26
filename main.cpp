#include <ncurses.h>
#include <chrono>
#include <thread>
#include <time.h>
#include <random>

#define std_colors 1
#define skull_colors 2
#define text_bar_colors 3
#define panel_colors 4
#define bar_colors 5
#define alert_colors 6

char * palabras_clave[10] = {"Tecmilenio","Servidores VPN","ARPs","firewalls","compilador","CND","BBVA","ALIENS","FBI","SI"};

int main()
{
    srand((unsigned) time(NULL));

    initscr();
    start_color();
    init_pair(std_colors, COLOR_WHITE, COLOR_BLACK);
    init_pair(skull_colors, COLOR_RED, COLOR_BLACK);
    init_pair(text_bar_colors, COLOR_WHITE, COLOR_YELLOW);
    init_pair(panel_colors,COLOR_GREEN, COLOR_BLACK);
    init_pair(bar_colors, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(std_colors));


    const char * skull_ASCII =
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
"     $$$\"                         $$$$\"      ";

    //bar configs
    WINDOW * bar = newwin(3, COLS, LINES-3, 0);
    wbkgd(bar, COLOR_PAIR(bar_colors));
    box(bar, 0,0);

    //skull configs
    WINDOW * skull = newwin(26, 48, 0,0);
    wbkgd(skull, COLOR_PAIR(skull_colors));

    //panel configs
    WINDOW * panel = newwin(LINES-3, COLS-49, 0, 49);
    wbkgd(panel, COLOR_PAIR(panel_colors));
    box(panel,0,0);

    wprintw(skull,"%s", (char*) skull_ASCII);
    wprintw(panel,"Registros de propagación del ransomware ");

    std::thread bar_filling([&]() -> void {
        wmove(bar, 1,1);
        int contador = 0;
        while(contador++ < COLS - 2) {
            refresh();
            wrefresh(panel);
            wrefresh(skull);
            wrefresh(bar);
            std::this_thread::sleep_for(std::chrono::duration<float>((float) (rand() % 5) / 10));
            wattron(bar,COLOR_PAIR(text_bar_colors));
            wprintw(bar, " ");
            wattroff(bar, COLOR_PAIR(text_bar_colors));
        }
    });

    wmove(panel, 1,2);

    for(int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        wprintw(panel, "hackeando %s... ", (char*) palabras_clave[i]);
        wmove(panel, i+1,2);
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