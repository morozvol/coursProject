#include "ReadTag.h"
#include <iconv.h>
#include <tchar.h>

using namespace std;

void Add_MP3_Tag(string name,vector<TagLib :: FileRef> t){
    TagLib :: FileRef f ( name.c_str() );
    cout<<"Add MP3 File: "<<convert(f.file()->name().toString().toCString(1), "utf-8", "cp1251");
    t.push_back(f);
    cout<<"\t ok!"<<endl;
}
void Add_MP3_Tag(wstring name,vector<TagLib :: FileRef> t){
    TagLib :: FileRef f ( name.c_str() );
    cout<<"Add MP3 File: "<<convert(f.file()->name().toString().toCString(1), "utf-8", "cp1251");
    t.push_back(f);
    cout<<"\t ok!"<<endl;
}
void Add_MP3_Tag(const char* name,vector<TagLib :: FileRef> t){
    TagLib :: FileRef f ( name );
    cout<<"Add MP3 File: "<<convert(f.file()->name().toString().toCString(1), "utf-8", "cp1251");
    tags.push_back(f);
    cout<<"\t ok!"<<endl;
    return;
}
void Add_MP3_Tag(const wchar_t* name,vector<TagLib :: FileRef> t){
    TagLib :: FileRef f ( name );
    cout<<"Add MP3 File: "<<convert(f.file()->name().toString().toCString(1), "utf-8", "cp1251");
    tags.push_back(f);
    cout<<"\t ok!"<<endl;
}
char* convert(const char* s, const char* from_cp, const char* to_cp)
{
    iconv_t ic = iconv_open(to_cp, from_cp);

    if (ic == (iconv_t)(-1)) {
        fprintf(stderr, "iconv: cannot convert from %s to %s\n", from_cp, to_cp);
        return "";
    }

    char* out_buf = (char*)calloc(strlen(s)+1, 1);
    char* out = out_buf;
    char* in = (char*)malloc(strlen(s)+1);
    strcpy(in, s);

    size_t in_ln = strlen(s);
    size_t out_ln = in_ln;
    size_t k = iconv(ic, &in, &in_ln, &out, &out_ln);
    if(k == (size_t)-1)
        fprintf(stderr, "iconv: %u of %d converted\n", k, strlen(s));

    if(errno != 0)
        fprintf(stderr, "iconv: %s\n", strerror(errno));

    iconv_close(ic);

    return out_buf;
}

void ScanFolder(LPTSTR pFolder)
{
    LPCSTR pMask="*.mp3";
    size_t nLen = _tcslen(pFolder);
    pFolder[nLen++] = '\\';
    auto p=pFolder;

    WIN32_FIND_DATA fd;
    HANDLE hf;

// Файлы по маске
    _tcscpy(pFolder + nLen, pMask);
    hf = FindFirstFile(pFolder, &fd);
    if ( hf != INVALID_HANDLE_VALUE )
    {
        do
        {
            if ( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
            {
                _tcscpy(p + nLen, fd.cFileName);
                cout<<p<<endl;
            }
        } while( FindNextFile(hf, &fd) );
        FindClose(hf);
    }
}
