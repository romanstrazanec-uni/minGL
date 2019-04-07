#pragma once
#include <windows.h>

class MessageHandler {
    virtual LRESULT handleMessage(UINT msg, WPARAM wparam, LPARAM lparam) = 0;
};
