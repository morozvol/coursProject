//
// Created by Владимир on 01.11.2018.
//
#include "WindowEdit.h"
HWND hEdit;
RECT rcEdit;
int RegClassEdit() {
    WNDCLASS wcs;
    memset(&wcs, 0, sizeof(WNDCLASS));
    wcs.style = CS_VREDRAW | CS_HREDRAW;
    wcs.lpfnWndProc = EditProc;
    wcs.cbClsExtra=0;
    wcs.cbWndExtra=0;
    wcs.hInstance = hInstance;
    wcs.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wcs.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcs.hbrBackground = (HBRUSH)(5);
    wcs.lpszMenuName = (LPSTR)nullptr;
    wcs.lpszClassName = (LPSTR)"MyEdit";
    return RegisterClass(&wcs);
}
bool CreateEditWindow(int sX, int sY, int x, int y,HWND parent){
    if(!hEdit)
    if (!RegClassEdit()) return false;
     hEdit = CreateWindow("MyEdit", "", WS_CHILD |WS_VISIBLE, sX, sY, x,y , parent, (HMENU)nullptr, hInstance, nullptr);
    if(!hEdit)MessageBox(parent,"","",MB_OK);
    return true;
}

LRESULT CALLBACK EditProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE: {
            CreateEditElements(hwnd);
            break;
        }
        case WM_SIZE:
            break;

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

void CreateEditElements(HWND hwnd){
    HideGUI() ;
    GetWindowRect(hwnd,&rcEdit);
    int x=rcEdit.right-rcEdit.left;
    int y=rcEdit.bottom-rcEdit.top;
    CreateWindow("static", "название:", WS_CHILD | WS_VISIBLE, 5, 10, 70,14,
                 hwnd, nullptr,hInstance,nullptr);
    CreateWindow("static", "исполнитель:", WS_CHILD | WS_VISIBLE, 5, 40, 90,14,
                 hwnd, nullptr,hInstance,nullptr);
    CreateWindow("static", "альбом:", WS_CHILD | WS_VISIBLE, 5, 70, 60,14,
                 hwnd, nullptr,hInstance,nullptr);
    CreateWindow("static", "жанр:", WS_CHILD | WS_VISIBLE, 5, 100, 45,14,
                 hwnd, nullptr,hInstance,nullptr);
    CreateWindow("static", "коментарий:", WS_CHILD | WS_VISIBLE, 5, 130, 85,14,
                 hwnd, nullptr,hInstance,nullptr);
    CreateWindow("static", "год:", WS_CHILD | WS_VISIBLE, 5, 160, 40,14,
                 hwnd, nullptr,hInstance,nullptr);
    CreateWindow("static", "номер трека в плейлисте:", WS_CHILD | WS_VISIBLE,5, 190, 175,14,
                 hwnd, nullptr,hInstance,nullptr);
    CreateWindow("static", "путь к файлу:", WS_CHILD | WS_VISIBLE, 5, y- 50, 100,14,
                 hwnd, nullptr,hInstance,nullptr);
    CreateWindow("static", "Simple Rate:", WS_CHILD | WS_VISIBLE, 5, y-20, 100,14,
                 hwnd, nullptr,hInstance,nullptr);
    CreateWindow("static", "битрейт:", WS_CHILD | WS_VISIBLE, 5, y- 80, 100,14,
                 hwnd, nullptr,hInstance,nullptr);
    CreateWindow("static", "длинна трека:", WS_CHILD | WS_VISIBLE,5,y- 110, 100,14,
                 hwnd, nullptr,hInstance,nullptr);


    hComboBoxTitle=CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 105 , 10, x-115,20,
                                hwnd, nullptr,hInstance,nullptr);
    hComboBoxName=CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 105, 40, x-115,20,
                               hwnd, nullptr,hInstance,nullptr);
    hComboBoxAlbom=CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 105, 70, x-115,20,
                                hwnd, nullptr,hInstance,nullptr);
    hComboBoxGenre=CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 105, 100, x-115,20,
                                hwnd, nullptr,hInstance,nullptr);
    hComboBoxComment=CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 105, 130, x-115,20,
                                  hwnd, nullptr,hInstance,nullptr);
    hComboBoxYear=CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 105, 160, x-115,20,
                               hwnd, nullptr,hInstance,nullptr);
    hComboBoxNumber=CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 200, 190,45,20,
                                 hwnd, nullptr,hInstance,nullptr);
}
void HideGUI() {
    ShowWindow(hComboBoxAlbom, SW_HIDE);
    ShowWindow(hComboBoxComment, SW_HIDE);
    ShowWindow(hComboBoxGenre, SW_HIDE);
    ShowWindow(hComboBoxName, SW_HIDE);
    ShowWindow(hComboBoxNumber, SW_HIDE);
    ShowWindow(hComboBoxTitle, SW_HIDE);
    ShowWindow(hComboBoxYear, SW_HIDE);
}