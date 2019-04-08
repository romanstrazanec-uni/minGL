#pragma once
#include <windows.h>

class MessageHandler {
public:
    UINT messageCode{0};
    virtual LRESULT handleMessage(UINT msg, WPARAM wparam, LPARAM lparam) = 0;
};
