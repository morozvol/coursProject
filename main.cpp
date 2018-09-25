#include <Windows.h>
#include "Headers/global.h"
#include "Headers/main.h"

char* buf;
char szClassName[] = "MainClass";

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    hInstance = hInst;
    if (!RegClass()) return -1;
    hMain = CreateWindowEx(0,szClassName, "редактор Мp3 тегов",
                         WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_VISIBLE,
                         CW_USEDEFAULT, CW_USEDEFAULT,   X*0.80, Y *0.80, NULL,
                         NULL, hInstance, NULL);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

int RegClass(void) {
    WNDCLASSEX wc;
    memset(&wc, 0, sizeof(WNDCLASSEX));
    wc.cbSize= sizeof(WNDCLASSEX);
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra=0;
    wc.cbWndExtra=0;
    wc.hIconSm= LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(COLOR_WHITE);
    wc.lpszMenuName = (LPSTR)NULL;
    wc.lpszClassName = (LPSTR)szClassName;
    return RegisterClassEx(&wc);
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
            SetBkColor(hdc, COLOR_WHITE);

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

    //MENU
    HMENU hMainMenu = CreateMenu();
    HMENU hPopMenuFile = CreatePopupMenu();

    AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hPopMenuFile, "Файл");
    AppendMenu(hMainMenu, MF_STRING, 1000, "Настройки");
    AppendMenu(hMainMenu, MF_STRING, 1001, "Справка");

    AppendMenu(hPopMenuFile, MF_STRING , 1002, "Выбрать папку с файлами");
    AppendMenu(hPopMenuFile, MF_STRING , 1003, "Отправить данные");

    SetMenu(hwnd, hMainMenu);
    SetMenu(hwnd, hPopMenuFile);
    //\MENU
}
