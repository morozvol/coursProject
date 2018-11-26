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
#include "resource.h"

extern unsigned int ID;

struct File {
    TagLib::FileRef taglibFile;
    unsigned int id;
    char loadLV[8][400]{};
    std::wstring path;

    File(unsigned int id, const TagLib::FileRef &f) {
        this->id = id;
        this->taglibFile = f;
    };
};

struct EditTag {
    char Title[60];
    char Name[60];
    char Album[60];
    char Genre[60];
    char Comment[60];
    char Year[11];
    char Number[11];
};


extern HINSTANCE hInstance;
extern HWND hMain, hListViev, hComboBox, hCBox[7];
extern MSG msg;
extern std::vector<File> file;

void editTags();

bool CreateEditWindow(int sX, int sY, int x, int y, HWND parent);

bool CreateSettingsWindow(HWND hWnd);

BOOL WINAPI AddListViewItems(HWND hWndLV, int colNum, int textMaxLen, char item[][400]);

#endif //COURSPROJECT_GLOBAL_H
