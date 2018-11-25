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
    wcs.cbClsExtra = 0;
    wcs.cbWndExtra = 0;
    wcs.hInstance = hInstance;
    wcs.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wcs.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcs.hbrBackground = (HBRUSH) (5);
    wcs.lpszMenuName = (LPSTR) nullptr;
    wcs.lpszClassName = (LPSTR) "MyEdit";
    return RegisterClass(&wcs);
}

bool CreateEditWindow(int sX, int sY, int x, int y, HWND parent) {
    if (!hEdit)
        if (!RegClassEdit()) return false;
    hEdit = CreateWindow("MyEdit", "", WS_CHILD | WS_VISIBLE, sX, sY, x, y, parent, (HMENU) nullptr, hInstance,
                         nullptr);
    if (!hEdit)MessageBox(parent, "", "", MB_OK);
    return true;
}

LRESULT CALLBACK EditProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE: {
            CreateEditElements(hwnd);
            break;
        }
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_BUTTON_EDIT:
                    editTags();
                    break;
                default:
                    return DefWindowProc(hwnd, message, wParam, lParam);
            }
            break;
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

void CreateEditElements(HWND hwnd) {
    HideGUI();
    GetWindowRect(hwnd, &rcEdit);
    int x = rcEdit.right - rcEdit.left;
    int y = rcEdit.bottom - rcEdit.top;
    CreateWindow("static", "название:", WS_CHILD | WS_VISIBLE, 5, 10, 70, 14,
                 hwnd, nullptr, hInstance, nullptr);
    CreateWindow("static", "исполнитель:", WS_CHILD | WS_VISIBLE, 5, 40, 90, 14,
                 hwnd, nullptr, hInstance, nullptr);
    CreateWindow("static", "альбом:", WS_CHILD | WS_VISIBLE, 5, 70, 60, 14,
                 hwnd, nullptr, hInstance, nullptr);
    CreateWindow("static", "жанр:", WS_CHILD | WS_VISIBLE, 5, 100, 45, 14,
                 hwnd, nullptr, hInstance, nullptr);
    CreateWindow("static", "коментарий:", WS_CHILD | WS_VISIBLE, 5, 130, 85, 14,
                 hwnd, nullptr, hInstance, nullptr);
    CreateWindow("static", "год:", WS_CHILD | WS_VISIBLE, 5, 160, 40, 14,
                 hwnd, nullptr, hInstance, nullptr);
    CreateWindow("static", "номер трека в плейлисте:", WS_CHILD | WS_VISIBLE, 5, 190, 175, 14,
                 hwnd, nullptr, hInstance, nullptr);
    CreateWindow("static", "Simple Rate:", WS_CHILD | WS_VISIBLE, 5, y - 20, 100, 14,
                 hwnd, nullptr, hInstance, nullptr);
    CreateWindow("static", "битрейт:", WS_CHILD | WS_VISIBLE, 5, y - 50, 100, 14,
                 hwnd, nullptr, hInstance, nullptr);
    CreateWindow("static", "длинна трека:", WS_CHILD | WS_VISIBLE, 5, y - 80, 100, 14,
                 hwnd, nullptr, hInstance, nullptr);


    hCBox[0] = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN | CBS_AUTOHSCROLL, 105, 10,
                            x - 115, 90,
                            hwnd, nullptr, hInstance, nullptr);
    hCBox[1] = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN | CBS_AUTOHSCROLL, 105, 40,
                            x - 115, 90,
                            hwnd, nullptr, hInstance, nullptr);
    hCBox[2] = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN | CBS_AUTOHSCROLL, 105, 70,
                            x - 115, 90,
                            hwnd, nullptr, hInstance, nullptr);
    hCBox[3] = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN | CBS_AUTOHSCROLL, 105,
                            100, x - 115, 90,
                            hwnd, nullptr, hInstance, nullptr);
    hCBox[4] = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN | CBS_AUTOHSCROLL, 105,
                            130, x - 115, 90,
                            hwnd, nullptr, hInstance, nullptr);
    hCBox[5] = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN | CBS_AUTOHSCROLL, 105,
                            160, x - 115, 90,
                            hwnd, nullptr, hInstance, nullptr);
    hCBox[6] = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN | CBS_AUTOHSCROLL, 200,
                            190, x - 210, 90,
                            hwnd, nullptr, hInstance, nullptr);
    CreateWindow("button", "редактировать", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 220, 120, 20, hwnd,
                 (HMENU) ID_BUTTON_EDIT, hInstance, nullptr);

    CreateWindow("static", "456565", WS_CHILD | WS_VISIBLE, 105, y - 20, x - 115, 14,
                 hwnd, nullptr, hInstance, nullptr);
    CreateWindow("static", "6546848", WS_CHILD | WS_VISIBLE, 105, y - 50, x - 115, 14,
                 hwnd, nullptr, hInstance, nullptr);
    CreateWindow("static", "02:30", WS_CHILD | WS_VISIBLE | WS_BORDER, 105, y - 80, x - 115, 14,
                 hwnd, nullptr, hInstance, nullptr);
    setLimitEditText(60);
}

void HideGUI() {
    for (auto &i : hCBox) {
        ShowWindow(i, SW_HIDE);
    }
}

void setLimitEditText(int limit){
    for (int i=0;i<7;i++){
        SendMessage(hCBox[i],CB_LIMITTEXT,limit,0L);
    }
}