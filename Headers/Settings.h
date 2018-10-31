//
// Created by Владимир on 29.10.2018.
//

#ifndef COURSPROJECT_SETTINGS_H
#define COURSPROJECT_SETTINGS_H

#include "global.h"
#define ID_SETTINGS             2000
void settings(HWND hwndParent);
LRESULT CALLBACK SetProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) ;
int RegSettingsClass(void);
#endif //COURSPROJECT_SETTINGS_H
