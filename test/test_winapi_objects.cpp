#include <windows.h>
#include <cstdlib>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HWND hName, hAge, hOut;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    WNDCLASS wc{};
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = "myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClass(&wc)) return -1;

    CreateWindow("myWindowClass", "My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                 100, 100, 500, 500, nullptr, nullptr, nullptr, nullptr);

    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_COMMAND:
            if (wp == 1) {
                char name[30], age[10], out[50];
                GetWindowText(hName, name, 30);
                GetWindowText(hAge, age, 30);

                strcpy(out, name);
                strcat(out, " is ");
                strcat(out, age);
                strcat(out, " yo.");

                SetWindowText(hOut, out);
            }
            break;
        case WM_CREATE: {
            CreateWindow("Static", "Name: ", WS_VISIBLE | WS_CHILD,
                         100, 50, 98, 38, hwnd, nullptr, nullptr, nullptr);
            hName = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                 200, 50, 98, 38, hwnd, nullptr, nullptr, nullptr);

            CreateWindow("Static", "Age: ", WS_VISIBLE | WS_CHILD,
                         100, 90, 98, 38, hwnd, nullptr, nullptr, nullptr);
            hAge = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                200, 90, 98, 38, hwnd, nullptr, nullptr, nullptr);

            CreateWindow("Button", "Generate", WS_VISIBLE | WS_CHILD,
                         150, 140, 98, 38, hwnd, (HMENU) 1, nullptr, nullptr);

            hOut = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                100, 200, 300, 200, hwnd, nullptr, nullptr, nullptr);
        }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}
