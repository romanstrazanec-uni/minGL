#include "Window.h"

LRESULT CALLBACK callback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
        }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

BYTE Window::wndCount = 0;

Window::Window(HINSTANCE hInstance, char *title) {
    *this = Window(hInstance, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, title);
}

Window::Window(HINSTANCE hInstance, int x, int y, int width, int height, char *title) :
        x(x), y(y), width(width), height(height),
        title(title) {
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = callback;
    wc.style = 0;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = nullptr;
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    char strwndCount[3];
    wsprintf(strwndCount, "%d", ++wndCount);
    lstrcpy(wndClass, "WND_");
    lstrcat(wndClass, strwndCount);
    wc.lpszClassName = wndClass;
}

Window::~Window() {
    --wndCount;
}

bool Window::create(){
    RegisterClassEx(&wc);
    hwnd = CreateWindowEx(
            WS_EX_CLIENTEDGE, // optional window styles
            wndClass, // window class
            title, // window title
            WS_OVERLAPPEDWINDOW, // window style
            x, y, width, height, // coordinates
            nullptr, // parent window
            nullptr, // menu
            wc.hInstance, // instance handle
            nullptr // additional application data
    );
    return hwnd != nullptr;
}

WPARAM Window::show(int nCmdShow) {
    MSG msg;
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

void Window::setWindowProcedure(LRESULT CALLBACK (*wndProc)(HWND, UINT, WPARAM, LPARAM)) {
    wc.lpfnWndProc = wndProc;
}
