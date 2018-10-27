//
// Created by Владимир on 24.09.2018.
//

#ifndef COURSPROJECT_MAIN_H
#define COURSPROJECT_MAIN_H

#include "global.h"
#include "Menu.h"
#include "ReadTag.h"
#include <iostream>
#include <io.h>
#include <stdio.h>
#include <sys/stat.h>
#include <commctrl.h>
#include <shlobj.h>
#include <taglib/fileref.h>
#include <vector>

int RegClass(void);
void CreateGUIElements(HWND);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND CreateListView(HWND hwndParent);
BOOL WINAPI AddListViewItems(HWND hWndLV, int colNum, int textMaxLen, char item[][20]);
int SetListViewColumns(HWND hWndLV, int colNum, int textMaxLen, char **header);
void loadListView(HWND hwndParent);
void loadFileFromFolders();



char szClassName[] = "MainClass";
BROWSEINFO brinfo;
char dispname[256];
HINSTANCE hInstance;
MSG msg;
HWND hMain, hListViev;
#endif //COURSPROJECT_MAIN_H
