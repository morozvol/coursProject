//
// Created by Владимир on 24.10.2018.
//

#ifndef COURSPROJECT_READTAG_H
#define COURSPROJECT_READTAG_H

#include <windows.h>
#include "global.h"
#include <iconv.h>
#include <tchar.h>
#include <tfile.h>


using namespace std;

void Add_MP3_Tag(wstring name);

char *convert(const char *s, const char *from_cp, const char *to_cp);

void ScanFolder(wstring pFolder);

#endif //COURSPROJECT_READTAG_H
