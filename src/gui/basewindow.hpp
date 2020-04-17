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
 */
template<class DerivedWindow>
class BaseWindow : public GUIObject {
private:
    /**
     * Backing property for initializing window.
     */
    bool initialized{false};

    WNDCLASSEX wc{};

    Gdiplus::GdiplusStartupInput gdiplusStartupInput{};
    ULONG_PTR gdiplusToken{};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedGlobalDeclarationInspection"
    // Used when BaseWindow::show() -> DispatchMessage(MSG) is called.

    /**
     * Window procedure. Windows OS callback function. Windows OS sends messages to be handled by
     * DerivedWindow::handleMessage(WindowMessage).
     *
     * @returns result of handled message.
     */
    static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        DerivedWindow *pThis;

        if (msg == WM_NCCREATE) {
            auto *pCreate = (CREATESTRUCT *) lParam;
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
    /**
     * This method needs to be derived by subclass window.
     */
    virtual LRESULT handleMessage(WindowMessage &&) = 0;
#pragma clang diagnostic pop

    /**
     * Override this method to manage window attributes.
     */
    virtual void setWindowAttributes() = 0;

public:
    BaseWindow(const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
            : GUIObject("CustomWindowClass", title, x, y, width, height, GetModuleHandle(nullptr), this) {
        // ^ WS_THICKFRAME to disable resizing of the window.
        addStyle(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME);
    }

    virtual void initialize() final {
        if (initialized) return;
        Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

        wc.lpszClassName = getClassName();
        wc.hInstance = getInstance();
        wc.lpfnWndProc = DerivedWindow::wndProc;
        setWindowAttributes();
        wc.cbSize = sizeof(WNDCLASSEX);
        if (RegisterClassEx(&wc)) initialized = true;
    }

    /**
     * Shows the window and creates an event loop.
     * After window destruction, shuts down gdiplus if enabled.
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

    virtual WNDCLASSEX getWindowClass() const final { return wc; }
    virtual const char *getTitle() const final { return getName(); }

    /* SETTERS */

    virtual void setTitle(char const *title) final { setName(title); }
    virtual void setIcon(LPCTSTR iconName) final {
        if (!initialized) wc.hIcon = LoadIcon(wc.hInstance, iconName);
    }
    virtual void setSmallIcon(LPCTSTR iconName) final {
        if (!initialized) wc.hIconSm = LoadIcon(wc.hInstance, iconName);
    }
    virtual void setCursor(LPCTSTR cursorName) final {
        if (!initialized) wc.hCursor = LoadCursor(wc.hInstance, cursorName);
    }
    virtual void setMenuName(LPCSTR menuName) final { if (!initialized) wc.lpszMenuName = menuName; }
    virtual void setBackground(HBRUSH color) final { if (!initialized) wc.hbrBackground = color; }
    virtual void setStyle(UINT style) final { if (!initialized) wc.style = style; }
    virtual void setWindowExtraBytes(int nBytes) final { if (!initialized) wc.cbWndExtra = nBytes; }
    virtual void setClassExtraBytes(int nBytes) final { if (!initialized) wc.cbClsExtra = nBytes; }
};

#endif
