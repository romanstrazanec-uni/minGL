#include <windows.h>
#include <gdiplus/gdiplus.h>

LRESULT CALLBACK WindowProcessMessages(HWND, UINT, WPARAM, LPARAM);

void draw(HDC hdc);

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount) {
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    const char *CLASS_NAME = "myWin32WindowClass";
    WNDCLASS wc{};
    wc.hInstance = currentInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.lpfnWndProc = WindowProcessMessages;
    RegisterClass(&wc);

    CreateWindow(CLASS_NAME, "Win32 Tutorial", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
                 800, 600, nullptr, nullptr, nullptr, nullptr);

    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);
    return 0;
}

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    HDC hdc;
    PAINTSTRUCT ps;
    switch (msg) {
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            draw(hdc);
            EndPaint(hwnd, &ps);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, msg, wparam, lparam);
    }
}

void draw(HDC hdc) {
    Gdiplus::Graphics gf(hdc);
    Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));
    Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 255, 0));

    gf.DrawLine(&pen, 0, 0, 500, 500);
    gf.FillRectangle(&brush, 400, 200, 100, 100);
    gf.DrawRectangle(&pen, 450, 400, 100, 150);
}
