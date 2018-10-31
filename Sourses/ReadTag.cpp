#include "ReadTag.h"
#include <iconv.h>
#include <tchar.h>
#include <tfile.h>

using namespace std;

void Add_MP3_Tag(wstring name){
    TagLib :: FileRef f ( name.c_str() );
    tags.push_back(f);
}

char* convert(const char* s, const char* from_cp, const char* to_cp)
{
    iconv_t ic = iconv_open(to_cp, from_cp);

    if (ic == (iconv_t)(-1)) {
        fprintf(stderr, "iconv: cannot convert from %s to %s\n", from_cp, to_cp);
        return (char*)("");
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

void ScanFolder(wstring folderpath)
{
    setlocale(LC_ALL, "");
    WIN32_FIND_DATAW wfd;
    HANDLE  hFind = FindFirstFileW((L"\\\\?\\" + folderpath+L"\\*mp3").c_str(), &wfd);
    if (INVALID_HANDLE_VALUE != hFind)
    {
        do
        {
           Add_MP3_Tag(folderpath+L"\\"+wstring(&wfd.cFileName[0]));
        } while ((BOOL)NULL != FindNextFileW(hFind, &wfd));

        FindClose(hFind);
    }
}
