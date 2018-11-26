//
// Created by Vladimir on 26.11.2018.
//

#ifndef COURSPROJECT_SETTINGSWINDOW_H
#define COURSPROJECT_SETTINGSWINDOW_H

#include "global.h"

HWND hSettings;


int RegClassSettings();

void CreateSettingsGUIElements(HWND hWnd);

LRESULT CALLBACK SettingsProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif //COURSPROJECT_SETTINGSWINDOW_H
