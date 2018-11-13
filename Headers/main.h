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
#include "taglib/attachedpictureframe.h"
#include <vector>


#define ID_COMBOBOX_DIRS   3000
#define ID_BUTTON_ADD          3001
#define ID_BUTTON_DEL         3002

int RegClass();

void CreateGUIElements(HWND);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND CreateListView(HWND hwndParent);

int SetListViewColumns(HWND hWndLV, int colNum, int textMaxLen, char **header);

void loadListView(HWND hwndParent);

void loadFileFromFolders();

void Dialog(HWND hwnd);

void update();

vector<int> GetSelectetItems();

void loadToEdit(TagLib::FileRef file);


char szClassName[] = "MainClass";
BROWSEINFOW brinfo;
HINSTANCE hInstance;
unsigned int ID = 0;

MSG msg;
HWND hMain, hListViev, hComboBox, hCBox[7];
wchar_t FileName[300];
RECT rcClient;
#endif //COURSPROJECT_MAIN_H
