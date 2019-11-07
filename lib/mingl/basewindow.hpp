#ifndef MINGL_BASE_WINDOW_INCLUDED
#define MINGL_BASE_WINDOW_INCLUDED

#include <string>
#include <iomanip>

#include <windows.h>

/* If no graphics needed, define NO_GDIPLUS to disable gdiplus library. */
#ifndef NO_GDIPLUS

#include <gdiplus/gdiplus.h>

#endif

#include <mingl/message.hpp>

/**
 * Base window template to be derived. Creates window by following the process:
 * <ol>
 * <li>declare derived window object.</li>
 * <li>use create() method to register window class.</li>
 * <li>use show() to show the window.</li>
 * </ol>
 *
 * Define USE_WNDCLASSEX macro to allow BaseWindow class to store WNDCLASSEX instead of WNDCLASS.
 * WNDCLASSEX (extended window class) has extra variable hIconSm and cbSize which needs to be 'size(WNDCLASSEX)'.
 * To create WNDCLASSEX use method CreateWindowEx instead of CreateWindow,
 * which needs optional window styles argument passed.
 */
template<class DerivedWindow>
class BaseWindow {
private:
#ifdef USE_WNDCLASSEX
    WNDCLASSEX
#else
    WNDCLASS
#endif
            wc{};
    HWND hwnd{nullptr};
    int x{CW_USEDEFAULT}, y{CW_USEDEFAULT}, width{CW_USEDEFAULT}, height{CW_USEDEFAULT};
    std::string title{};
    char *wndClassName{nullptr};

#ifndef NO_GDIPLUS
    Gdiplus::GdiplusStartupInput gdiplusStartupInput{};
    ULONG_PTR gdiplusToken{};
#endif

    /**
     * Checks if not already set and if not, then randomly sets window class name
     * as a hexadecimal value between "00000000" and "ffffffff".
     */
    void setClassName() {
        if (wndClassName == nullptr) {
            wndClassName = new char[8];
            srand(time(nullptr));
            int r = std::rand();
            std::stringstream stream;
            stream << std::setfill('0') << std::setw(8) << std::hex << r;
            const std::string &tmpstr = stream.str();
            lstrcpy(wndClassName, tmpstr.c_str());
            wc.lpszClassName = wndClassName;
        }
    }

    /**
     * Window procedure. Windows OS callback function. Windows OS sends messages to be handled by
     * DerivedWindow::handleMessage(Message).
     *
     * @param hwnd
     * @param msg
     * @param wParam
     * @param lParam
     * @returns result of handled message.
     */
    static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        DerivedWindow *pThis = nullptr;

        if (msg == WM_NCCREATE) {
            auto pCreate = (CREATESTRUCT *) lParam;
            pThis = (DerivedWindow *) pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) pThis);

            pThis->hwnd = hwnd;
        } else pThis = (DerivedWindow *) GetWindowLongPtr(hwnd, GWLP_USERDATA);

        if (msg == WM_DESTROY) {
            PostQuitMessage(0);
            return 0;
        }

        if (pThis) return pThis->handleMessage(Message(msg, wParam, lParam));
        else return DefWindowProc(hwnd, msg, wParam, lParam);
    }

protected:
    /**
     * This method needs to be derived by
     */
    virtual LRESULT handleMessage(Message) = 0;

public:
    /** Constructor initializes the window class with BaseWindow::initialize() method. */
    BaseWindow() {
        initialize();
    }

    virtual ~BaseWindow() {
        if (wndClassName != nullptr) delete[] wndClassName;
    }

    /**
     * Window class initialization. Creates new random class name for the window with BaseWindow::setClassName(),
     * sets the window procedure, cbSize if USE_WNDCLASSEX is defined and sets other attributes
     * with BaseWindow::setDefaultSettings(). Also starts up gdiplus, unless NO_GDIPLUS is defined.
     */
    virtual void initialize() final {
#ifndef NO_GDIPLUS
        Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
#endif
#ifdef USE_WNDCLASSEX
        wc.cbSize = sizeof(WNDCLASSEX);
#endif
        setClassName();
        setWindowProcedure(DerivedWindow::wndProc);
        setDefaultWindowAttributes();
    }

    /** Behavior declared in derived window. */
    virtual void setDefaultWindowAttributes() = 0;

    /**
     * Sets class name if not already, registers window class and creates window.
     *
     * @returns true if window was properly created.
     */
    virtual bool create() final {
        if (hwnd != nullptr) return false;
        setClassName();
        wc.hInstance = GetModuleHandle(nullptr);
#ifdef USE_WNDCLASSEX
        wc.cbSize = sizeof(WNDCLASSEX);
        if(!RegisterClassEx(&wc)) return false;
        hwnd = CreateWindowEx(
                WS_EX_CLIENTEDGE, // optional window styles
#else
        if (!RegisterClass(&wc)) return false;
        hwnd = CreateWindow(
#endif
                wndClassName, // window class
title.c_str(), // window title
WS_OVERLAPPEDWINDOW | WS_VISIBLE, // window style
x, y, width, height, // coordinates
nullptr, // parent window
nullptr, // menu
wc.hInstance, // instance handle
this // additional application data
        );
        return hwnd != nullptr;
    }

    /**
     * Shows the window and creates a loop to fetch messages. After window destruction, shuts down gdiplus if enabled.
     *
     * @returns false when not created otherwise true after the window was destroyed.
     */
    virtual bool show() final {
        if (hwnd == nullptr) return false;
        MSG msg{};
        while (GetMessage(&msg, nullptr, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
#ifndef NO_GDIPLUS
        Gdiplus::GdiplusShutdown(gdiplusToken);
#endif
        return true;
    }

    /* GETTERS */

    /** @returns window class of type either WNDCLASS or WNDCLASSEX if USE_WNDCLASSEX defined. */
    virtual
#ifdef USE_WNDCLASSEX
    WNDCLASSEX
#else
    WNDCLASS
#endif
    getWindowClass() const final {
        return wc;
    }

    virtual const char *getWindowClassName() const final {
        return wndClassName;
    }

    virtual HWND getWindowHandle() const final {
        return hwnd;
    }

    virtual std::string getTitle() const final {
        return title;
    }

    /* SETTERS */

    virtual void setTitle(std::string str) final {
        title = str;
    }

    virtual void setWindowProcedure(LRESULT CALLBACK (*wndProc)(HWND, UINT, WPARAM, LPARAM)) final {
        wc.lpfnWndProc = wndProc;
    }

    virtual void setIcon(HINSTANCE hinstance, LPCSTR icon_name) final {
        wc.hIcon = LoadIcon(hinstance, icon_name);
    }

#ifdef USE_WNDCLASSEX
    virtual void setSmallIcon(HINSTANCE hinstance, LPCSTR icon_name) final {
        wc.hIconSm = LoadIcon(hinstance, icon_name);
    }
#endif

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

#endif
