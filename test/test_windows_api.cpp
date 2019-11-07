#include <windows.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_EXIT 3

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void addMenus(HWND);

HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow) {
    WNDCLASSW wc{0};

    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc)) return -1;

    CreateWindowW(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  100, 100, 500, 500, nullptr, nullptr, nullptr, nullptr);

    MSG msg{};
    while (GetMessage(&msg, nullptr, NULL, NULL) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_COMMAND:
            switch (wp) {
                case FILE_MENU_EXIT:
                    DestroyWindow(hwnd);
                    break;
                case FILE_MENU_NEW:
                    MessageBeep(MB_ICONINFORMATION);
                    break;
                default:
                    break;
            }
            break;
        case WM_CREATE:
            addMenus(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hwnd, msg, wp, lp);
    }
}

void addMenus(HWND hwnd) {
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hSubMenu, MF_STRING, NULL, "SubMenu Item");

    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR) hSubMenu, "Open SubMenu");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, nullptr);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hFileMenu, "File");
    AppendMenu(hMenu, MF_STRING, NULL, "Help");

    SetMenu(hwnd, hMenu);
}
