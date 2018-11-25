//
// Created by Владимир on 24.09.2018.
//

#ifndef COURSPROJECT_MAIN_H
#define COURSPROJECT_MAIN_H

#include "global.h"
#include "ReadTag.h"
#include <shlobj.h>

int RegClass();

void CreateGUIElements(HWND);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND CreateListView(HWND hwndParent);

int SetListViewColumns(HWND hWndLV, int colNum, int textMaxLen, char **header);

void loadListView(HWND hwndParent);

void loadFileFromFolders();

void Dialog(HWND hwnd);

void clearEditBuf();

void update();

vector<int> GetSelectetItems();
void loadToEdit();


char szClassName[] = "MainClass";
BROWSEINFOW brinfo;
HINSTANCE hInstance;
unsigned int ID = 0;

MSG msg;
HWND hMain, hListViev, hComboBox, hCBox[7];
wchar_t FileName[300];
RECT rcClient;
#endif //COURSPROJECT_MAIN_H
