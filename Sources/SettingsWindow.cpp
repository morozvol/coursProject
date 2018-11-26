//
// Created by Vladimir on 26.11.2018.
//
#include "SettingsWindow.h"
bool is_openSettings(){
    return true;
}
bool CreateSettingsWindow(HWND hWnd) {
    if (!hSettings)
        if (!RegClassSettings()) return false;
    hSettings = CreateWindow("MySettings", "", WS_CHILD | WS_OVERLAPPEDWINDOW , 100, 100, 300, 300, hWnd, (HMENU) nullptr, hInstance,
                             nullptr);
    ShowWindow(hSettings,SW_SHOW);

    return hSettings != nullptr;

}

int RegClassSettings() {
    WNDCLASS wcs;
    memset(&wcs, 0, sizeof(WNDCLASS));
    wcs.style = CS_VREDRAW | CS_HREDRAW;
    wcs.lpfnWndProc = SettingsProc;
    wcs.cbClsExtra = 0;
    wcs.cbWndExtra = 0;
    wcs.hInstance = hInstance;
    wcs.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wcs.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcs.hbrBackground = (HBRUSH) (5);
    wcs.lpszMenuName = (LPSTR) nullptr;
    wcs.lpszClassName = (LPSTR) "MySettings";
    return RegisterClass(&wcs);
}
    void CreateSettingsGUIElements(HWND hWnd) {
        CreateWindow("static", "", WS_CHILD, 100, 100, 300, 300, hWnd, (HMENU) nullptr, hInstance,
                     nullptr);
    }


LRESULT CALLBACK SettingsProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE: {
            CreateSettingsGUIElements(hWnd);
            break;
        }
        case WM_COMMAND:
            switch (LOWORD(wParam)) {

                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        case WM_SIZE:
            break;

        case WM_DESTROY: {
            ShowWindow(hSettings,SW_HIDE);
            break;
        }
        default: {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    return 0;
}
