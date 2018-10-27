//
// Created by Владимир on 24.10.2018.
//

#ifndef COURSPROJECT_READTAG_H
#define COURSPROJECT_READTAG_H

#include <iostream>
#include <windows.h>
#include "global.h"
#include <vector>
#include "fileref.h"
#include "taglib.h"
#include "tag.h"
using namespace std;

void Add_MP3_Tag(string name, vector<TagLib :: FileRef> t);
void Add_MP3_Tag(wstring name,vector<TagLib :: FileRef> t);
void Add_MP3_Tag(const char* name,vector<TagLib :: FileRef> t);
void Add_MP3_Tag(const wchar_t* name,vector<TagLib :: FileRef> t);
char* convert(const char* s, const char* from_cp, const char* to_cp);
void ScanFolder(LPTSTR pFolder);
#endif //COURSPROJECT_READTAG_H
