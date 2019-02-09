#include "Window.h"

BYTE Window::wndCount = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
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

Window::Window(HINSTANCE hInstance, char *wndTitle) {
    *this = Window(hInstance, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, wndTitle);
}

Window::Window(HINSTANCE hInstance, int x, int y, int width, int height, char *wndTitle) :
        x(x), y(y), width(width), height(height),
        hInstance(hInstance),
        wndTitle(wndTitle) {
    char strwndCount[3];
    wsprintf(strwndCount, "%d", ++wndCount);
    lstrcpy(wndClass, "_WND_");
    lstrcat(wndClass, strwndCount);
    initialize();
    create();
}

Window::~Window() { --wndCount; }

WPARAM Window::show(int nCmdShow){
    MSG msg;
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

int Window::initialize() {
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = wndClass;
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    return RegisterClassEx(&wc);
}

bool Window::create(){
    hwnd = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            wndClass,
            wndTitle,
            WS_OVERLAPPEDWINDOW,
            x, y, width, height,
            nullptr, nullptr, hInstance, nullptr);
    return hwnd != nullptr;
}