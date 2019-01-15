#include "Window.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_LBUTTONDOWN: {
                char szFileName[MAX_PATH];
                HINSTANCE hInstance = GetModuleHandle(NULL);

                GetModuleFileName(hInstance, szFileName, MAX_PATH);
                MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
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

Window::Window(HINSTANCE hInstance, char * windowTitle):
        hInstance(hInstance),
        windowTitle(windowTitle) {
    initialize();
    registerWindow();
    create();
}

Window::Window(HINSTANCE hInstance, unsigned int x, unsigned int y, unsigned int width, unsigned int height, char * windowTitle):
        x(x), y(y), width(width), height(height),
        hInstance(hInstance),
        windowTitle(windowTitle) {
    initialize();
    registerWindow();
    create();
}

WPARAM Window::show(int nCmdShow){
    MSG msg;
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

void Window::initialize(){
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
}

void Window::registerWindow(){
    if(!RegisterClassEx(&wc)) throw EXCEPTION_REGISTRATION();
}

bool Window::create(){
    hwnd = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            szClassName, windowTitle,
            WS_OVERLAPPEDWINDOW,
            x, y, width, height,
            NULL, NULL, hInstance, NULL);
    return hwnd != NULL;
}