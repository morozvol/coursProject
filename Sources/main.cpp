#include <main.h>

int quantity = 8;
EditTag editMyTag;
using namespace std;
vector<File> file;
vector<wstring> dirs;
vector<vector<string>> edit;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    hInstance = hInst;
    setlocale(LC_ALL, "");
    if (!RegClass()) return -1;
    HMENU hm = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU));
    hMain = CreateWindowEx(WS_EX_STATICEDGE,szClassName, "редактор Мp3 тегов",
                         WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                         CW_USEDEFAULT, 8, (int) (X * 0.80), (int) (Y * 0.80), nullptr,
                         hm, hInstance, nullptr);
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

int RegClass() {
    WNDCLASSEX wc;
    wc.cbSize=sizeof(wc);
    wc.cbClsExtra=0;
    wc.cbWndExtra=0;
    wc.hbrBackground=(HBRUSH) (1);
    wc.hCursor=LoadCursor(nullptr,IDC_ARROW);
    wc.hIcon= (HICON)LoadImage(hInstance,MAKEINTRESOURCE(IDI_MY_ICON),IMAGE_ICON,128,128,0);
    wc.hIconSm=(HICON) LoadImage(hInstance,MAKEINTRESOURCE(IDI_MY_ICON),IMAGE_ICON,16,16,0);
    wc.hInstance=hInstance;
    wc.lpfnWndProc=WndProc;
    wc.lpszClassName=(LPSTR) szClassName;
    wc.lpszMenuName=(LPSTR) nullptr;
    wc.style=CS_HREDRAW | CS_VREDRAW;
    return RegisterClassEx(&wc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE: {
            edit.resize(7);
            break;
        }
        case WM_SIZE:
            GetWindowRect(hwnd, &rcClient);
            ShowWindow(hListViev, SW_HIDE);
            if (!CreateEditWindow((int) ((rcClient.right - rcClient.left) * 0.75) - 12, 0,
                                  (int) ((rcClient.right - rcClient.left) - (rcClient.right - rcClient.left) * 0.75),
                                  rcClient.bottom - rcClient.top - 60, hwnd))
                MessageBox(nullptr, "", "", MB_OK);
            hListViev = CreateListView(hwnd);
            CreateGUIElements(hwnd);
            loadListView(hListViev);

            break;
        case WM_NOTIFY: {
            auto pnmhdr = (LPNMHDR) lParam;

            switch (pnmhdr->code) {
                case NM_CUSTOMDRAW: {
                    switch (((LPNMLVCUSTOMDRAW) lParam)->nmcd.dwDrawStage) {
                        case CDDS_PREPAINT: {
                            return CDRF_NOTIFYITEMDRAW;
                        }
                        case CDDS_ITEMPREPAINT: {
                            if (((LPNMLVCUSTOMDRAW) lParam)->nmcd.dwItemSpec % 2 == 0) {
                                ((LPNMLVCUSTOMDRAW) lParam)->clrTextBk = RGB(152, 179, 224);
                                return CDRF_NEWFONT;
                            }
                        }
                        default:
                            return DefWindowProc(hwnd, message, wParam, lParam);
                    }
                }
                case LVN_ITEMCHANGED: {//Обработчик события выбора элемента
                    vector<int> i = GetSelectetItems();
                    clearEdit();
                    clearEditBuf();
                    selectToEdit(i, lParam);
                    loadToEdit();
                    break;
                }
                default:
                    return DefWindowProc(hwnd, message, wParam, lParam);
            }
            break;
        }
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case MENU_OPEN_DIRECTORY:
                    Dialog(hwnd);
                    break;
                case ID_BUTTON_ADD:
                    Dialog(hwnd);
                    break;
                case ID_BUTTON_DEL:
                    // Dialog(hwnd);
                    break;
                case MENU_UPDATE:
                    update();
                    break;
                case MENU_SETTINGS:
                    CreateSettingsWindow(hwnd);
                    break;
                case MENU_CLOSE :
                    PostQuitMessage(0);
                default:
                    return DefWindowProc(hwnd, message, wParam, lParam);
            }
            break;
        case WM_GETMINMAXINFO: //Для настройки минимального и максимального размера окна
        {
            auto *pInfo = (MINMAXINFO *) lParam;
            POINT Min = {(int) (X * 0.750), (int) (Y * 0.750)};
            POINT Max = {X, Y};
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
    ShowWindow(hComboBox,SW_HIDE);
    ShowWindow(hButtonAdd,SW_HIDE);
    ShowWindow(hButtonDel,SW_HIDE);
    // GetWindowRect(hwnd,&rcClient);
    int wLV = (int) ((rcClient.right - rcClient.left) * 0.75);
    int hLV = (int) (rcClient.bottom - rcClient.top);
    hComboBox = CreateWindow("combobox", nullptr,
                             WS_CHILD | WS_VISIBLE | CBS_AUTOHSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWN |
                             CBS_DROPDOWNLIST | CBS_SORT, 0, hLV - 25, wLV - 50, 120,
                             hwnd, (HMENU) ID_COMBOBOX_DIRS, hInstance, nullptr);
    hButtonAdd=CreateWindow("button", "+", WS_CHILD | WS_VISIBLE, wLV - 25, hLV - 25, 25, 25,
                 hwnd, (HMENU) ID_BUTTON_ADD, hInstance, nullptr);
    hButtonDel=CreateWindow("button", "-", WS_CHILD | WS_VISIBLE, wLV - 50, hLV - 25, 25, 25,
                 hwnd, (HMENU) ID_BUTTON_DEL, hInstance, nullptr);

}

BOOL WINAPI AddListViewItems(HWND hWndLV, int colNum, int textMaxLen, char item[][400]) {
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
    lvc.cx = (int) ((rcl.right - rcl.left) / 3.5);
    lvc.cchTextMax = textMaxLen;

    for (int i = 0; i < colNum; i++) {
        if (i == 7) lvc.cx = 0;
        lvc.pszText = header[i];
        index = ListView_InsertColumn(hWndLV, i, &lvc);
        if (index == -1) break;
    }

    return index;
}

HWND CreateListView(HWND hwndParent) {
    GetClientRect(hwndParent, &rcClient);

    HWND hlwRTView = CreateWindow(WC_LISTVIEW, "",
                                  WS_CHILD | LVS_REPORT | LVS_SHOWSELALWAYS,
                                  0, 0,
                                  (int) ((rcClient.right - rcClient.left) * 0.75),
                                  rcClient.bottom - rcClient.top - 25, hwndParent, (HMENU) ID_LW_RT_VIEW, hInstance,
                                  nullptr);

    ShowWindow(hlwRTView, SW_SHOW);
    char *header[8] = {(char *) ("Название трека"),
                       (char *) ("Артист"),
                       (char *) ("Альбом"),
                       (char *) ("Жанр"),
                       (char *) ("Коментарий"),
                       (char *) ("Год выпуска"),
                       (char *) ("Путь к файлу"),
                       (char *) ("ID")
    };
    SetListViewColumns(hlwRTView, quantity, 31, header);
    ListView_SetExtendedListViewStyle(hlwRTView,
                                      ListView_GetExtendedListViewStyle(hlwRTView) | LVS_EX_FULLROWSELECT |
                                      LVS_EX_GRIDLINES);
    ShowWindow(hlwRTView, SW_SHOW);

    return (hlwRTView);
}

void loadListView(HWND hwndParent) {
    ListView_DeleteAllItems(hwndParent);
    for (auto &f : file)
        AddListViewItems(hListViev, quantity, 400, f.loadLV);
    int s = SendMessage(hListViev, LVM_GETCOUNTPERPAGE, 0, 0);
    char buffer[quantity][400];
    memset(buffer, 0, sizeof(buffer));
    strcmp(buffer[0], "");
    strcmp(buffer[1], "");
    strcmp(buffer[2], "");
    strcmp(buffer[3], "");
    strcmp(buffer[4], "");
    strcmp(buffer[5], "");
    strcmp(buffer[6], "");
    strcmp(buffer[7], "");
    for (int i = file.size(); i < s + 1; i++) {
        AddListViewItems(hListViev, quantity, 400, buffer);
    }

}

void loadFileFromFolders() {
    for (const auto &dir : dirs) {
        ScanFolder(dir);
    }

}

void Dialog(HWND hwnd) {
    wchar_t folderpath[400];
    brinfo.hwndOwner = hwnd;
    brinfo.lpszTitle = L"Choose folder";
    brinfo.pszDisplayName = nullptr;
    brinfo.ulFlags = BIF_RETURNONLYFSDIRS;
    brinfo.lpfn = nullptr;

    auto folder = SHBrowseForFolderW(&brinfo);
    if (folder) {
        SHGetPathFromIDListW(folder, (LPWSTR) folderpath);
        dirs.emplace_back(folderpath);
        SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM) folderpath);
        update();
    }
}

void update() {
    file.clear();
    loadFileFromFolders();
    loadListView(hListViev);
}

vector<int> GetSelectetItems() {
    vector<int> i;
    i.clear();
    int iPos = ListView_GetNextItem(hListViev, -1, LVNI_SELECTED);
    while (iPos != -1 && iPos < file.size()) {
        i.push_back(iPos);
        iPos = ListView_GetNextItem(hListViev, iPos, LVNI_SELECTED);
    }
    return i;
}

void loadToEdit() {
    for (int i = 0; i < 7; i++) {
        for (auto &v : edit[i])
            SendMessage(hCBox[i], CB_ADDSTRING, 0, (LPARAM) v.c_str());
        if (edit[i].size() == 1)
            SetWindowText(hCBox[i], (LPCSTR) edit[i][0].c_str());
        else if (!edit[i].empty())
            SendMessage(hCBox[i], CB_INSERTSTRING, 0, (LPARAM) "<оставить>");
    }
}

bool is_ok(int ok) {
    return ok == IDOK;
}

void updateFile(File *f) {
    if (is_leave(editMyTag.Title))
        f->taglibFile.tag()->setTitle(string(editMyTag.Title));
    if (is_leave(editMyTag.Name))
        f->taglibFile.tag()->setArtist(string(editMyTag.Name));
    if (is_leave(editMyTag.Album))
        f->taglibFile.tag()->setAlbum(string(editMyTag.Album));
    if (is_leave(editMyTag.Genre))
        f->taglibFile.tag()->setGenre(string(editMyTag.Genre));
    if (is_leave(editMyTag.Comment))
        f->taglibFile.tag()->setComment(string(editMyTag.Comment));
    if (is_leave(editMyTag.Year))
        f->taglibFile.tag()->setYear((unsigned int) stol(editMyTag.Year));
    if (is_leave(editMyTag.Number))
        f->taglibFile.tag()->setTrack((unsigned int) stol(editMyTag.Number));
    f->taglibFile.save();
    if (is_leave(editMyTag.Title))
        strcpy(f->loadLV[0], editMyTag.Title);
    if (is_leave(editMyTag.Name))
        strcpy(f->loadLV[1], editMyTag.Name);
    if (is_leave(editMyTag.Album))
        strcpy(f->loadLV[2], editMyTag.Album);
    if (is_leave(editMyTag.Genre))
        strcpy(f->loadLV[3], editMyTag.Genre);
    if (is_leave(editMyTag.Comment))
        strcpy(f->loadLV[4], editMyTag.Comment);
    if (is_leave(editMyTag.Year))
        strcpy(f->loadLV[5], editMyTag.Year);
    if (is_leave(editMyTag.Number))
        strcpy(f->loadLV[6], editMyTag.Number);
}

void editTags() {
    int ok;
    vector<int> s = GetSelectetItems();
    if (!s.empty()) {
        if (s.size() == 1) {//выделен один элемент
            ok = MessageBox(hMain, "Вы точно хотите изменить выделенный файл", "Внимание",
                            MB_OKCANCEL | MB_ICONQUESTION);
        } else {
            ok = MessageBox(hMain, "Вы точно хотите изменить выделенные файлы?", "Внимание",
                            MB_OKCANCEL | MB_ICONQUESTION);
        }
        if (is_ok(ok)) {
            GetWindowText(hCBox[0], editMyTag.Title, 30);
            GetWindowText(hCBox[1], editMyTag.Name, 30);
            GetWindowText(hCBox[2], editMyTag.Album, 30);
            GetWindowText(hCBox[3], editMyTag.Genre, 30);
            GetWindowText(hCBox[4], editMyTag.Comment, 30);
            GetWindowText(hCBox[5], editMyTag.Year, 11);
            GetWindowText(hCBox[6], editMyTag.Number, 11);

            for (int i : s) {
                updateFile(&file[i]);
            }
            loadListView(hListViev);
        }
    }
}

void clearEdit() {
    for (auto &i : hCBox) {
        SendMessage(i, CB_RESETCONTENT, 0, 0L);
    }

}

bool is_finded(vector<string> vstr, const string &s) {
    for (auto &vs : vstr) {
        if (s.empty())return true;
        if (vs == s)return true;
    }
    return false;
}
char buf[60] = "123";
void selectToEdit(vector<int> selected, LPARAM lParam) {
    int id;
    auto pnmhdr = (LPNMHDR) lParam;
    for (auto &t : selected) {
        for (int i = 0; i < 7; i++) {
            ListView_GetItemText(pnmhdr->hwndFrom, t, i, buf, 60);
            if (!is_finded(edit[i], string(buf))){
                if (i == 6) {
                    ListView_GetItemText(pnmhdr->hwndFrom, t, 7, buf, 60);
                  id=stoi(string(buf),nullptr,10);
                    for (auto &f : file) {
                        if (f.id == id)
                            if (!is_finded(edit[6], string(buf))) {
                                edit[i].emplace_back(to_string(f.taglibFile.tag()->track()));
                                break;
                            }
                    }
                } else
                    edit[i].emplace_back(string(buf));
            }
        }
    }
}

void clearEditBuf() {
    for (auto &e :edit) {
        e.clear();
    }
}

bool is_leave(char *string) {
    return (strcmp(string, "<оставить>") != 0);
}
