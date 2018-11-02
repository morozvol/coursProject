#include <main.h>

using namespace std;
std::vector< TagLib :: FileRef>tags;
std::vector<wstring>dirs;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    hInstance = hInst;
    setlocale(LC_ALL, "");
    if (!RegClass()) return -1;
    HMENU hm = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU));
    hMain = CreateWindow( szClassName, "редактор Мp3 тегов",
                          WS_OVERLAPPEDWINDOW| WS_VISIBLE,
                          CW_USEDEFAULT,8, (int)(X * 0.80), (int)(Y  * 0.80), nullptr,
                          hm, hInstance, nullptr);
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

int RegClass() {
    WNDCLASS wc;
    memset(&wc, 0, sizeof(WNDCLASS));
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra=0;
    wc.cbWndExtra=0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(1);
    wc.lpszMenuName = (LPSTR)nullptr;
    wc.lpszClassName = (LPSTR)szClassName;
    return RegisterClass(&wc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE: {
            break;
        }
        case WM_SIZE:
            GetWindowRect(hwnd,&rcClient);
            ShowWindow(hListViev,SW_HIDE);
            if(!CreateEditWindow((int)((rcClient.right-rcClient.left)*0.75)-12, 0, (int)((rcClient.right-rcClient.left)-(rcClient.right-rcClient.left)*0.75),rcClient.bottom-rcClient.top-60,hwnd))MessageBox(nullptr,"","",MB_OK);
            hListViev = CreateListView(hwnd);
            CreateGUIElements(hwnd);
            loadListView(hListViev);
            break;
        case WM_NOTIFY: {
            auto pnmhdr = (LPNMHDR) lParam;

            switch (pnmhdr->code) {
                case NM_CUSTOMDRAW:
                {
                    switch(((LPNMLVCUSTOMDRAW) lParam)->nmcd.dwDrawStage)
                    {
                        case CDDS_PREPAINT:
                        {
                            return CDRF_NOTIFYITEMDRAW;
                        }
                        case CDDS_ITEMPREPAINT:
                        {
                            if(((LPNMLVCUSTOMDRAW) lParam)->nmcd.dwItemSpec%2==0)
                            {
                                ((LPNMLVCUSTOMDRAW) lParam)->clrTextBk=RGB(152, 179, 224);
                                return CDRF_NEWFONT;
                            }
                        }
                        default:
                            return DefWindowProc(hwnd, message, wParam, lParam);                    }
                }
                case LVN_ITEMCHANGED: {//Обработчик события выбора элемента
                    vector<int> i = GetSelectetItems();
                    if (i.size() == 1) {
                        loadToEdit(tags[i[0]]);
                    } else {}
                    break;
                }
                default:
                    return DefWindowProc(hwnd, message, wParam, lParam);
            }
            break;
        }
        case WM_COMMAND:
            switch (LOWORD(wParam)){
                case  MENU_OPEN_DIRECTORY:
                    Dialog(hwnd);
                    break;
                case ID_BUTTON:
                    Dialog(hwnd);
                    break;
                case MENU_UPDATE:
                    update();
                    break;
                case MENU_SETTINGS:
                    break;
                case MENU_CLOSE :
                    PostQuitMessage(0);
                default:
                    return DefWindowProc(hwnd, message, wParam, lParam);
            }
            break;
        case WM_GETMINMAXINFO: //Для настройки минимального и максимального размера окна
        {
            auto *pInfo = (MINMAXINFO *)lParam;
            POINT Min = {(int)(X * 0.750), (int)(Y * 0.750)};
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
   // GetWindowRect(hwnd,&rcClient);
    int wLV = (int) ((rcClient.right - rcClient.left) * 0.75);
    int hLV = (int) (rcClient.bottom - rcClient.top);
    hComboBox = CreateWindow("combobox", nullptr,
                             WS_CHILD | WS_VISIBLE | CBS_AUTOHSCROLL | CBS_DISABLENOSCROLL | CBS_DROPDOWN |
                             CBS_DROPDOWNLIST | CBS_SORT, 0, hLV - 25, wLV - 25, 120,
                             hwnd, (HMENU) ID_COMBOBOX_DIRS, hInstance, nullptr);
    hButton = CreateWindow("button", "+", WS_CHILD | WS_VISIBLE, wLV - 25, hLV - 25, 25, 25,
                           hwnd, (HMENU) ID_BUTTON, hInstance, nullptr);

}

BOOL WINAPI AddListViewItems(HWND hWndLV, int colNum, int textMaxLen, char  item[][400]) {
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
    lvc.cx = (int)((rcl.right - rcl.left) / 3.5);
    lvc.cchTextMax = textMaxLen;

    for (int i = 0; i < colNum; i++) {
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
                                  0,0,
                                  (int)((rcClient.right - rcClient.left)*0.75) ,
                                  rcClient.bottom-rcClient.top - 25 , hwndParent, (HMENU) ID_LW_RT_VIEW, hInstance,
                                  nullptr);

    ShowWindow(hlwRTView,SW_SHOW);
    char *header[7] = {(char*)("Название трека"),
                       (char*)("Артист"),
                       (char*)("Альбом"),
                       (char*)("Жанр"),
                       (char*)("Год выпуска"),
                       (char*)("Коментарий"),
                       (char*)("Путь к файлу")
                      };
    SetListViewColumns(hlwRTView, 7, 31, header);
    ListView_SetExtendedListViewStyle(hlwRTView,
                                      ListView_GetExtendedListViewStyle(hlwRTView) | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    ShowWindow(hlwRTView,SW_SHOW);

    return (hlwRTView);
}
void loadListView(HWND hwndParent) {
    ListView_DeleteAllItems(hwndParent);
    char  buffer[7][400];
    memset(buffer, 0, sizeof(buffer));
    for (auto &tag : tags) {
        strcpy(buffer[0],convert(tag.tag()->title().toCString(TRUE), "utf-8", "cp1251"));
        strcpy(buffer[1],convert(tag.tag()->artist().toCString(TRUE), "utf-8", "cp1251"));
        strcpy(buffer[2],convert(tag.tag()->album().toCString(TRUE), "utf-8", "cp1251"));
        strcpy(buffer[3],convert(tag.tag()->genre().toCString(TRUE), "utf-8", "cp1251"));
        strcpy(buffer[4],to_string(tag.tag()->year()).c_str());
        strcpy(buffer[5],convert(tag.tag()->comment().toCString(TRUE), "utf-8", "cp1251"));
        strcpy(buffer[6],convert(tag.file()->name().toString().toCString(TRUE), "utf-8", "cp1251"));

        AddListViewItems(hListViev, 7, 400, buffer);
    }
    int s=SendMessage(hListViev,LVM_GETCOUNTPERPAGE,0,0);
    for(int i=tags.size();i<s+1;i++){
        strcpy(buffer[0],"");
        strcpy(buffer[1],"");
        strcpy(buffer[2],"");
        strcpy(buffer[3],"");
        strcpy(buffer[4],"");

        AddListViewItems(hListViev, 7, 400, buffer);
    }

}
void loadFileFromFolders(){
    for (const auto &dir : dirs) {
        ScanFolder(dir);
    }

}
void Dialog(HWND  hwnd){
    wchar_t folderpath[400];
    brinfo.hwndOwner = hwnd;
    brinfo.lpszTitle = L"Choose folder";
    brinfo.pszDisplayName = nullptr;
    brinfo.ulFlags = BIF_RETURNONLYFSDIRS ;
    brinfo.lpfn = nullptr;

    auto folder=SHBrowseForFolderW(&brinfo);
    if(folder) {
        SHGetPathFromIDListW(folder,(LPWSTR)folderpath);
        dirs.emplace_back(folderpath);
        update();

    }
}
void update(){
    tags.clear();
    loadFileFromFolders();
    loadListView(hListViev);
}
vector<int>GetSelectetItems(){
    vector <int>i;
    int iPos = ListView_GetNextItem(hListViev,-1,LVNI_SELECTED);
    while(iPos!=-1 && iPos<tags.size()){
        i.push_back(iPos);
        iPos = ListView_GetNextItem(hListViev,iPos,LVNI_SELECTED);
    }
    return i;
}
void loadToEdit( TagLib :: FileRef file){
   SetWindowText(hComboBoxTitle,convert(file.tag()->title().toCString(TRUE), "utf-8", "cp1251"));
   SetWindowText(hComboBoxName,convert(file.tag()->artist().toCString(TRUE), "utf-8", "cp1251"));
   SetWindowText(hComboBoxAlbom,convert(file.tag()->album().toCString(TRUE), "utf-8", "cp1251"));
   SetWindowText(hComboBoxGenre,convert(file.tag()->genre().toCString(TRUE), "utf-8", "cp1251"));
   SetWindowText(hComboBoxComment,convert(file.tag()->comment().toCString(TRUE), "utf-8", "cp1251"));
   SetWindowText(hComboBoxYear,to_string(file.tag()->year()).c_str());
   SetWindowText(hComboBoxNumber,to_string(file.tag()->track()).c_str());

}