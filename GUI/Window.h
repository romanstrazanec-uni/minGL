#pragma once
#include "BaseWindow.h"

class Window: public BaseWindow<Window> {
public:
    LRESULT handleMessage(UINT msg, WPARAM wparam, LPARAM lparam) override;
};