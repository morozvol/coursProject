#include <windows.h>
#include "global.h"
#include "main.h"
#include "Menu.h"
#include <iostream>
#include <io.h>
#include <stdio.h>
#include <sys/stat.h>
#include <commctrl.h>
#include <shlobj.h>

#define MENU_ADD        1003
#define MENU_DELETE     1004
#define MENU_EDIT       1005
#define IDLW_RT_VIEW    3000

using namespace std;

char szClassName[] = "MainClass";
BROWSEINFO brinfo;
char dispname[256];


HWND CreateListView(HWND hwndParent);
BOOL WINAPI AddListViewItems(HWND hWndLV, int colNum, int textMaxLen, char item[][20]);
int SetListViewColumns(HWND hWndLV, int colNum, int textMaxLen, char **header);
void Dialog();


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
 SetConsoleOutputCP(1251);
    hInstance = hInst;

    if (!RegClass()) return -1;
    HMENU hm = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
    hMain = CreateWindow( szClassName, "редактор Мp3 тегов",
                           WS_OVERLAPPEDWINDOW| WS_VISIBLE,
                           CW_USEDEFAULT, CW_USEDEFAULT, X * 0.80, Y  * 0.80, NULL,
                           hm, hInstance, NULL);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

int RegClass(void) {
    WNDCLASS wc;
    memset(&wc, 0, sizeof(WNDCLASS));
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra=0;
    wc.cbWndExtra=0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(COLOR_DARK);
    wc.lpszMenuName = (LPSTR)NULL;
    wc.lpszClassName = (LPSTR)szClassName;
    return RegisterClass(&wc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

    switch (message) {
        case WM_CREATE: {
            brinfo.hwndOwner = NULL;
            brinfo.lpszTitle = "Browse for folder";
            brinfo.pszDisplayName =(char *) &dispname;
            brinfo.ulFlags = BIF_RETURNONLYFSDIRS ;
            brinfo.lpfn = NULL;

            break;
        }
        case WM_SIZE:
           ShowWindow(hListViev,SW_HIDE);
           CreateGUIElements(hwnd);
            break;
        case WM_PAINT: {
            hdc = BeginPaint(hwnd, &ps);

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_COMMAND:
            switch (LOWORD(wParam)){
                case MENU_OPEN_DIRECTORY:
                    Dialog();
                    break;
                case MENU_CLOSE :
                    PostQuitMessage(0);
                default:
                    return DefWindowProc(hwnd, message, wParam, lParam);

            }
        case WM_GETMINMAXINFO: //Для настройки минимального и максимального размера окна
        {
            MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
            POINT Min = { X/2, Y/2 };
            POINT  Max = {X,Y };
            pInfo->ptMinTrackSize = Min; // Установили минимальный размер
            pInfo->ptMaxTrackSize = Max; // Установили максимальный размер
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default: {
            return DefWindowProc(hwnd, message, wParam, lParam);
        }
    }
    return 0;
}

void CreateGUIElements(HWND hwnd) {
    hListViev= CreateListView(hwnd);
}

BOOL WINAPI AddListViewItems(HWND hWndLV, int colNum, int textMaxLen, char item[][20]) {
    int iLastIndex = ListView_GetItemCount(hWndLV);

    LVITEM lvi;
    lvi.mask = LVIF_TEXT;
    lvi.cchTextMax = textMaxLen;
    lvi.iItem = iLastIndex;
    lvi.pszText = item[0];
    lvi.iSubItem = 0;

    if (ListView_InsertItem(hWndLV, &lvi) == -1)
        return FALSE;
    for (int i = 1; i < colNum; i++) ListView_SetItemText(hWndLV, iLastIndex, i, item[i]);

    return TRUE;
}

int SetListViewColumns(HWND hWndLV, int colNum, int textMaxLen, char **header) {
    RECT rcl;
    GetClientRect(hWndLV, &rcl);

    int index = -1;

    LVCOLUMN lvc;
    lvc.mask = LVCF_TEXT | LVCF_WIDTH;
    lvc.cx = (rcl.right - rcl.left) / colNum;
    lvc.cchTextMax = textMaxLen;

    for (int i = 0; i < colNum; i++) {
        lvc.pszText = header[i];
        index = ListView_InsertColumn(hWndLV, i, &lvc);
        if (index == -1) break;
    }

    return index;
}

HWND CreateListView(HWND hwndParent) {
    //InitCommonControls();

    RECT rcClient;                       // The parent window's client area.

    GetClientRect(hwndParent, &rcClient);

    HWND hlwRTView = CreateWindow(WC_LISTVIEW, "",
                                  WS_CHILD | LVS_REPORT,
                                  0,rcClient.bottom - rcClient.top- (rcClient.bottom - rcClient.top)/2 ,
                                  rcClient.right - rcClient.left ,
                                  (rcClient.bottom - rcClient.top)/2 , hwndParent, (HMENU) IDLW_RT_VIEW, hInstance,
                                  nullptr);
    ListView_SetExtendedListViewStyleEx(hlwRTView, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    ShowWindow(hlwRTView,SW_SHOW);
    char *header[5] = {"Название","Автор", "Альбом", "Год выпуска", "Жанр"};
    SetListViewColumns(hlwRTView, 5, 25, header);

    ShowWindow(hlwRTView,SW_SHOW);

    return (hlwRTView);
}
void Dialog(){
    brinfo.hwndOwner = NULL;
    brinfo.lpszTitle = "Выберите папку";
    brinfo.pszDisplayName =(char *) &dispname;
    brinfo.ulFlags = BIF_RETURNONLYFSDIRS ;
    brinfo.lpfn = NULL;

    SHBrowseForFolder(&brinfo);
}