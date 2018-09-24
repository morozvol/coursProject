#include <Windows.h>
#include "Headers/global.h"
#include "Headers/main.h"

char* buf;
char szClassName[] = "MainClass";

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    hInstance = hInst;
    if (!RegClass()) return -1;
    hMain = CreateWindow(szClassName, "редактор mp3 тегов",
                         WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_VISIBLE,
                         0, 0, X - 200, Y - 200, NULL,
                         NULL, hInstance, NULL);
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
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
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
        case WM_CREATE:
            CreateGUIElements(hwnd);

            break;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            SetBkColor(hdc, COLOR_DARK);

            EndPaint(hwnd, &ps);

            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

void CreateGUIElements(HWND hwnd) {

}
