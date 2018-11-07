//
// Created by �������� on 24.09.2018.
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

#define ID_BUTTON_EDIT            1007
#define ID_LW_RT_VIEW             1006
struct File{
    TagLib::FileRef taglibFile;
    unsigned int id;
    char Title[60]="";
    char Name[60]="";
    char Album[60]="";
    char Genre[60]="";
    char Comment[60]="";
    char Year[10]="";
    char Number[10]="";
};

struct EditTag {
    char Title[60];
    char Name[60];
    char Album[60];
    char Genre[60];
    char Comment[60];
    char Year[10];
    char Number[10];

    EditTag() {};
};


extern HINSTANCE hInstance;
extern HWND hMain, hListViev, hComboBox, hCBox[7];
extern MSG msg;
extern std::vector<TagLib::FileRef> tags;

void editTags();

bool CreateEditWindow(int sX, int sY, int x, int y, HWND parent);

#endif //COURSPROJECT_GLOBAL_H
