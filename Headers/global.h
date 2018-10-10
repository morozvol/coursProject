//
// Created by Владимир on 24.09.2018.
//

#ifndef COURSPROJECT_GLOBAL_H
#define COURSPROJECT_GLOBAL_H
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#define X GetSystemMetrics(SM_CXSCREEN)
#define Y GetSystemMetrics(SM_CYSCREEN)
#define COLOR_DARK RGB(94,109,125)
#define COLOR_WHITE RGB(240,240,240)

HINSTANCE hInstance;
HWND hMain, hListViev;
MSG msg;

#endif //COURSPROJECT_GLOBAL_H
