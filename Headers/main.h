//
// Created by Владимир on 24.09.2018.
//

#ifndef COURSPROJECT_MAIN_H
#define COURSPROJECT_MAIN_H

#define ID_BUTTON_1 1001
#define ID_BUTTON_2 1002
#define ID_BUTTON_3 1003
#define ID_BUTTON_4 1004
#define ID_BUTTON_5 1005
#define ID_BUTTON_6 1006
#define ID_BUTTON_7 1007

int RegClass(void);
void CreateGUIElements(HWND);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#endif //COURSPROJECT_MAIN_H
