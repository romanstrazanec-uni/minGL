#ifndef MINGL_WINDOW_INCLUDED
#define MINGL_WINDOW_INCLUDED

#include <map>
#include <mingl/basewindow.hpp>
#include <mingl/messagehandler.hpp>

class Window : public BaseWindow<Window> {
    std::map<UINT, MessageHandler> messageHandlers;
public:
    LRESULT handleMessage(Message msg) override {
        if (messageHandlers.count(msg.getMsg()) == 0)
            return DefWindowProc(getWindowHandle(), msg.getMsg(), msg.getWparam(), msg.getLparam());
        messageHandlers[msg.getMsg()].handleMessage(getWindowHandle(), msg);
        return 0;
    }

    /**
     * Sets icon, small icon, cursor, background, menu name, style, windows extra bytes and class extra bytes.
     */
    virtual void setDefaultWindowAttributes() override {
        setIcon(nullptr, IDI_APPLICATION);
#ifdef USE_WNDCLASSEX
        setSmallIcon(nullptr, IDI_APPLICATION);
#endif
        setCursor(nullptr, IDI_APPLICATION);
        setBackground((HBRUSH) (COLOR_WINDOW + 1));
        setMenuName(nullptr);
        setStyle(0);
        setWindowExtraBytes(0);
        setClassExtraBytes(0);
    }

    void addHandler(MessageHandler msgHandler) {
        messageHandlers[msgHandler.getMessage().getMsg()] = msgHandler;
    }

    void addHandler(Message msg, void (*handle)(HWND, Message)) {
        addHandler(MessageHandler(msg, handle));
    }
};

#endif
