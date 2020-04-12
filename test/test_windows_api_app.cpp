#include <windows.h>
#include <cstdlib>

#define FILE_MENU_NEW 1
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void addMenus(HWND);

void addControls(HWND);

HMENU hMenu;
HWND hName, hAge, hOut;

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
                case GENERATE_BUTTON:
                    char name[30], age[10], out[50];
                    GetWindowText(hName, name, 30);
                    GetWindowText(hAge, age, 30);

                    strcpy(out, name);
                    strcat(out, " is ");
                    strcat(out, age);
                    strcat(out, " yo.");

                    SetWindowText(hOut, out);
                    break;
                default:
                    break;
            }
            break;
        case WM_CREATE:
            addMenus(hwnd);
            addControls(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hwnd, msg, wp, lp);
    }
    return 0;
}

void addMenus(HWND hwnd) {
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hSubMenu, MF_STRING, NULL, "Change title");

    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR) hSubMenu, "Open SubMenu");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, nullptr);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hFileMenu, "File");
    AppendMenu(hMenu, MF_STRING, NULL, "Help");

    SetMenu(hwnd, hMenu);
}

void addControls(HWND hwnd) {
    CreateWindowW(L"Static", L"Name: ", WS_VISIBLE | WS_CHILD,
                  100, 50, 98, 38, hwnd, nullptr, nullptr, nullptr);
    hName = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
                          200, 50, 98, 38, hwnd, nullptr, nullptr, nullptr);

    CreateWindowW(L"Static", L"Age: ", WS_VISIBLE | WS_CHILD,
                  100, 90, 98, 38, hwnd, nullptr, nullptr, nullptr);
    hAge = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
                         200, 90, 98, 38, hwnd, nullptr, nullptr, nullptr);

    CreateWindowW(L"Button", L"Generate", WS_VISIBLE | WS_CHILD,
                  150, 140, 98, 38, hwnd, (HMENU) GENERATE_BUTTON, nullptr, nullptr);

    hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
                         100, 200, 300, 200, hwnd, nullptr, nullptr, nullptr);
}
