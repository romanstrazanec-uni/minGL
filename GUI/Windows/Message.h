#pragma once

#include <windows.h>

class Message {
    UINT messageCode{0};
    WPARAM wparam{0};
    LPARAM lparam{0};

public:
    Message() = default;
    Message(UINT code) : messageCode(code) {}
    Message(UINT code, WPARAM wparam, LPARAM lparam) : messageCode(code), wparam(wparam), lparam(lparam) {}

    WPARAM getWparam() {
        return wparam;
    }

    LPARAM getLparam() {
        return lparam;
    }

    friend bool operator==(Message &msg, UINT code) {
        return msg.messageCode == code;
    }

    friend bool operator!=(Message &msg, UINT code) {
        return !(msg == code);
    }

    friend bool operator==(UINT code, Message &msg) {
        return msg == code;
    }

    friend bool operator!=(UINT code, Message &msg) {
        return msg != code;
    }

    friend bool operator==(Message &msg1, Message &msg2) {
        return msg1.messageCode == msg2.messageCode;
    }

    friend bool operator!=(Message &msg1, Message &msg2) {
        return msg1.messageCode != msg2.messageCode;
    }

    UINT getMsg() {
        return messageCode;
    }

    static Message onPaint() {
        return {WM_PAINT};
    }

    static Message onClose() {
        return {WM_CLOSE};
    }
};
