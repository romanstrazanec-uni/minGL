#ifndef MINGL_BASE_WINDOW_INCLUDED
#define MINGL_BASE_WINDOW_INCLUDED

#include "guiobject.hpp"
#include "../messages/windowmessage.hpp"

#include <gdiplus.h>

/**
 * Base window template to be derived. Creates window by following the process:
 * <ol>
 * <li>declare</li>
 * <li>initialize()</li>
 * <li>show()</li>
 * </ol>
 *
 * Define USE_WNDCLASSEX macro to allow BaseWindow class to store WNDCLASSEX instead of WNDCLASS.
 * WNDCLASSEX (extended window class) has extra variable hIconSm and cbSize which needs to be 'size(WNDCLASSEX)'.
 * To create WNDCLASSEX use method CreateWindowEx instead of CreateWindow,
 * which needs optional window styles argument passed.
 */
template<class DerivedWindow>
class BaseWindow : public GUIObject {
private:
    /** Backing property for initializing window. */
    bool initialized{false};

#ifdef USE_WNDCLASSEX
    WNDCLASSEX
#else
    WNDCLASS
#endif
            wc{};

    Gdiplus::GdiplusStartupInput gdiplusStartupInput{};
    ULONG_PTR gdiplusToken{};

    /**
     * Window procedure. Windows OS callback function. Windows OS sends messages to be handled by
     * DerivedWindow::handleMessage(WindowMessage).
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

            pThis->setWindowHandle(hwnd);
        } else pThis = (DerivedWindow *) GetWindowLongPtr(hwnd, GWLP_USERDATA);

        if (msg == WM_DESTROY) {
            PostQuitMessage(0);
            return 0;
        }

        return pThis ? pThis->handleMessage(WindowMessage(msg, wParam, lParam))
                     : DefWindowProc(hwnd, msg, wParam, lParam);
    }

protected:
    /** This method needs to be derived by subclass window. */
    virtual LRESULT handleMessage(WindowMessage &&) = 0;

public:
    BaseWindow(const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
            : GUIObject("CustomWindowClass", title, x, y, width, height, GetModuleHandle(nullptr), this) {
        addStyle(WS_OVERLAPPEDWINDOW);
    }

    virtual void initialize() final {
        if (initialized) return;
        Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

        wc.lpszClassName = getClassName();
        wc.hInstance = getHinstance();
        wc.lpfnWndProc = DerivedWindow::wndProc;
        setDefaultWindowAttributes();
#ifdef USE_WNDCLASSEX
        wc.cbSize = sizeof(WNDCLASSEX);
        if(RegisterClassEx(&wc))
#else
        if (RegisterClass(&wc))
#endif
            initialized = true;
    }

    /**
     * Override this method to manage window attributes.
     */
    virtual void setDefaultWindowAttributes() {
        setIcon(nullptr, IDI_APPLICATION);
#ifdef USE_WNDCLASSEX
        setSmallIcon(nullptr, IDI_APPLICATION);
#endif
        setCursor(nullptr, IDI_APPLICATION);
        setBackground((HBRUSH) COLOR_WINDOW);
        setMenuName(nullptr);
        setStyle(0);
        setWindowExtraBytes(0);
        setClassExtraBytes(0);
    }

    /**
     * Shows the window and creates a loop to fetch messages. After window destruction, shuts down gdiplus if enabled.
     *
     * @returns false when not created otherwise true after the window was destroyed.
     */
    virtual bool show() final {
        if (!isCreated()) computeSize();
        if (!create()) return false;
        MSG msg{};
        while (GetMessage(&msg, nullptr, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Gdiplus::GdiplusShutdown(gdiplusToken);
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
    getWindowClass() const final { return wc; }
    virtual const char *getTitle() const final { return getName(); }

    /* SETTERS */

    virtual void setTitle(char const *title) final { setName(title); }
    virtual void setIcon(HINSTANCE hinstance, LPCSTR icon_name) final {
        if (!initialized) wc.hIcon = LoadIcon(hinstance, icon_name);
    }
#ifdef USE_WNDCLASSEX
    virtual void setSmallIcon(HINSTANCE hinstance, LPCSTR icon_name) final {
        if (!initialized) wc.hIconSm = LoadIcon(hinstance, icon_name);
    }
#endif
    virtual void setCursor(HINSTANCE hinstance, LPCSTR cursor_name) final {
        if (!initialized) wc.hCursor = LoadCursor(hinstance, cursor_name);
    }
    virtual void setMenuName(LPCSTR menu_name) final { if (!initialized) wc.lpszMenuName = menu_name; }
    virtual void setBackground(HBRUSH color) final { if (!initialized) wc.hbrBackground = color; }
    virtual void setStyle(UINT style) final { if (!initialized) wc.style = style; }
    virtual void setWindowExtraBytes(int n_bytes) final { if (!initialized) wc.cbWndExtra = n_bytes; }
    virtual void setClassExtraBytes(int n_bytes) final { if (!initialized) wc.cbClsExtra = n_bytes; }
};

#endif
