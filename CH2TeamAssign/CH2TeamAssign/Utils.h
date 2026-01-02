#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#include <iostream>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
int _getch();
#endif

using namespace std;

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_ENTER = 13;
const int KEY_ESC = 27;
const int STORE_DISPLAY_COUNT = 5;

#define COLOR_YELLOW "\033[33m"
#define COLOR_RESET  "\033[0m"

void sleep_ms(int ms);
void clearScreen();
void typeText(const string& text, int delay = 25);
