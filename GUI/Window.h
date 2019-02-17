#pragma once

#include "../include.h"

template<class DerivedWindow>
class Window {
private:
    WNDCLASSEX wc{};
    HWND hwnd{};
    int x{CW_USEDEFAULT}, y{CW_USEDEFAULT}, width{CW_USEDEFAULT}, height{CW_USEDEFAULT};
    std::string title{};
    char CLASS_NAME[16]{};
    static UINT32 wndCount;

    void setClassName(){
        char strwndCount[10];
        wsprintf(strwndCount, "%d", ++wndCount);
        lstrcpy(CLASS_NAME, "_WND_");
        lstrcat(CLASS_NAME, strwndCount);
    }

    static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
        DerivedWindow *pThis = nullptr;

        if(msg == WM_NCCREATE) {
            auto pCreate = (CREATESTRUCT *)lParam;
            pThis = (DerivedWindow *)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

            pThis->hwnd = hwnd;
        } else pThis = (DerivedWindow *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if(msg == WM_DESTROY) {
            PostQuitMessage(0);
            return 0;
        }

        if(pThis) return pThis->handleMessage(msg, wParam, lParam);
        else return DefWindowProc(hwnd, msg, wParam, lParam);
    }

protected:
    virtual LRESULT handleMessage(UINT msg, WPARAM, LPARAM) = 0;

public:
    Window(){
        initialize();
    }
    explicit Window(std::string title): title(std::move(title)) {
        *this = DerivedWindow();
    }
    Window(int x, int y, int width, int height, std::string title):
        x(x), y(y), width(width), height(height), title(std::move(title)){
        *this = DerivedWindow();
    }
    virtual ~Window(){
        --wndCount;
    }

    virtual void initialize() final {
        setClassName();
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.lpszClassName = CLASS_NAME;
        setWindowProcedure(DerivedWindow::wndProc);
        setDefaultSettings();
    }
    virtual void setDefaultSettings(){
        setIcon(nullptr, IDI_APPLICATION);
        setSmallIcon(nullptr, IDI_APPLICATION);
        setCursor(nullptr, IDI_APPLICATION);
        setBackground((HBRUSH) (COLOR_WINDOW + 1));
        setMenuName(nullptr);
        setStyle(0);
        setWindowExtraBytes(0);
        setClassExtraBytes(0);
    }
    virtual bool create(HINSTANCE hInstance) final {
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.lpszClassName = CLASS_NAME;
        wc.hInstance = hInstance;
        RegisterClassEx(&wc);
        hwnd = CreateWindowEx(
                WS_EX_CLIENTEDGE, // optional window styles
                CLASS_NAME, // window class
                title.c_str(), // window title
                WS_OVERLAPPEDWINDOW, // window style
                x, y, width, height, // coordinates
                nullptr, // parent window
                nullptr, // menu
                wc.hInstance, // instance handle
                this // additional application data
        );
        return hwnd != nullptr;
    }
    virtual WPARAM show(int nCmdShow) final {
        MSG msg{};
        ShowWindow(hwnd, nCmdShow);
        UpdateWindow(hwnd);
        while (GetMessage(&msg, nullptr, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return msg.wParam;
    }

    virtual WNDCLASSEX getWindowClass() const final {
        return wc;
    }
    virtual const char *getWindowClassName() const final {
        return CLASS_NAME;
    }
    virtual HWND getWindowHandle() const final {
        return hwnd;
    }

    virtual std::string getTitle() const final {
        return title;
    }

    virtual void setTitle(std::string str) final {
        title = str;
    }
    virtual void setWindowProcedure(LRESULT CALLBACK (*wndProc)(HWND, UINT, WPARAM, LPARAM)) final {
        wc.lpfnWndProc = wndProc;
    }
    virtual void setIcon(HINSTANCE hinstance, LPCSTR icon_name) final {
        wc.hIcon = LoadIcon(hinstance, icon_name);
    }
    virtual void setSmallIcon(HINSTANCE hinstance, LPCSTR icon_name) final {
        wc.hIconSm = LoadIcon(hinstance, icon_name);
    }
    virtual void setCursor(HINSTANCE hinstance, LPCSTR cursor_name) final {
        wc.hCursor = LoadCursor(hinstance, cursor_name);
    }
    virtual void setMenuName(LPCSTR menu_name) final {
        wc.lpszMenuName = menu_name;
    }
    virtual void setBackground(HBRUSH color) final {
        wc.hbrBackground = color;
    }
    virtual void setStyle(UINT style) final {
        wc.style = style;
    }
    virtual void setWindowExtraBytes(int n_bytes) final {
        wc.cbWndExtra = n_bytes;
    }
    virtual void setClassExtraBytes(int n_bytes) final {
        wc.cbClsExtra = n_bytes;
    }
};

template<class DC>
UINT32 Window<DC>::wndCount = 0;
