#include <windows.h>
#include <gdiplus/gdiplus.h>

LRESULT CALLBACK WindowProcessMessages(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE, PSTR, INT) {
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

    if (!RegisterClass(&wc)) return -1;

    CreateWindow(CLASS_NAME, "GDI+ Test", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 50,
                 800, 600, nullptr, nullptr, nullptr, nullptr);

    MSG msg{};
    while (GetMessage(&msg, nullptr, NULL, NULL) > 0) {
        DispatchMessage(&msg);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);
    return 0;
}

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            Gdiplus::Graphics gf(BeginPaint(hwnd, &ps));
            Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));
            Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 255, 0));

            gf.DrawLine(&pen, 0, 0, 500, 500);
            gf.FillRectangle(&brush, 400, 200, 100, 100);
            gf.DrawRectangle(&pen, 450, 400, 100, 150);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, msg, wparam, lparam);
    }
}
