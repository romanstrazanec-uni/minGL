#include "Window.h"

LRESULT CALLBACK defaultWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
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

UINT32 Window::wndCount = 0;

Window::Window(char *title) {
    *this = Window(CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, title);
}

Window::Window(int x, int y, int width, int height, char *title) :
        x(x), y(y), width(width), height(height),
        title(title) {
}

Window::~Window() {
    --wndCount;
}

bool Window::create(WNDCLASSEX &wc) {
    wc.cbSize = sizeof(WNDCLASSEX);
    char strwndCount[10];
    wsprintf(strwndCount, "%d", ++wndCount);
    lstrcpy(CLASS_NAME, "_WND_");
    lstrcat(CLASS_NAME, strwndCount);
    wc.lpszClassName = CLASS_NAME;
    RegisterClassEx(&wc);
    hwnd = CreateWindowEx(
            WS_EX_CLIENTEDGE, // optional window styles
            CLASS_NAME, // window class
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

WNDCLASSEX Window::getDefaultClass() {
    WNDCLASSEX wc = {};
    setIcon(wc, nullptr, IDI_APPLICATION);
    setSmallIcon(wc, nullptr, IDI_APPLICATION);
    setCursor(wc, nullptr, IDI_APPLICATION);
    setBackground(wc, (HBRUSH) (COLOR_WINDOW + 1));
    setMenuName(wc, nullptr);
    setStyle(wc, 0);
    setWindowExtraBytes(wc, 0);
    setClassExtraBytes(wc, 0);
    setWindowProcedure(wc, defaultWndProc);
    return wc;
}

void Window::setWindowProcedure(WNDCLASSEX &wc, LRESULT CALLBACK (*wndProc)(HWND, UINT, WPARAM, LPARAM)) {
    wc.lpfnWndProc = wndProc;
}

void Window::setIcon(WNDCLASSEX &wc, HINSTANCE hinstance, LPCSTR icon_name) {
    wc.hIcon = LoadIcon(hinstance, icon_name);
}

void Window::setSmallIcon(WNDCLASSEX &wc, HINSTANCE hinstance, LPCSTR icon_name) {
    wc.hIconSm = LoadIcon(hinstance, icon_name);
}

void Window::setCursor(WNDCLASSEX &wc, HINSTANCE hinstance, LPCSTR cursor_name) {
    wc.hCursor = LoadCursor(hinstance, cursor_name);
}

void Window::setMenuName(WNDCLASSEX &wc, LPCSTR menu_name) {
    wc.lpszMenuName = menu_name;
}

void Window::setBackground(WNDCLASSEX &wc, HBRUSH color) {
    wc.hbrBackground = color;
}

void Window::setStyle(WNDCLASSEX &wc, UINT style) {
    wc.style = style;
}

void Window::setWindowExtraBytes(WNDCLASSEX &wc, int n_bytes) {
    wc.cbWndExtra = n_bytes;
}

void Window::setClassExtraBytes(WNDCLASSEX &wc, int n_bytes) {
    wc.cbClsExtra = n_bytes;
}
