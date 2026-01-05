
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#include "Utils.h"

#ifndef _WIN32
int _getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

void sleep_ms(int ms) { this_thread::sleep_for(chrono::milliseconds(ms)); }

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void typeText(const string& text, int delay) {
    for (char c : text) { cout << c << flush; sleep_ms(delay); }
    cout << endl;
}
