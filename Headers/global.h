//
// Created by Владимир on 24.09.2018.
//

#ifndef COURSPROJECT_GLOBAL_H
#define COURSPROJECT_GLOBAL_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <taglib/fileref.h>
#include <vector>

#define X GetSystemMetrics(SM_CXSCREEN)
#define Y GetSystemMetrics(SM_CYSCREEN)
#define COLOR_DARK RGB(94,109,125)
#define COLOR_WHITE RGB(240,240,240)
#define MENU_ADD                  1003
#define MENU_DELETE               1004
#define MENU_EDIT                 1005
#define ID_LW_RT_VIEW             1006


extern HINSTANCE hInstance;
extern HWND hMain, hListViev;
extern MSG msg;
extern std::vector< TagLib :: FileRef>tags;

#endif //COURSPROJECT_GLOBAL_H
