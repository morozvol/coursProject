//
// Created by Владимир on 01.11.2018.
//

#ifndef COURSPROJECT_WINDOWEDIT_H
#define COURSPROJECT_WINDOWEDIT_H

#include "windows.h"
#include "global.h"

void CreateEditElements(HWND hwnd);

LRESULT CALLBACK EditProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

void setLimitEditText(int limit);

void HideGUI();

#endif //COURSPROJECT_WINDOWEDIT_H
