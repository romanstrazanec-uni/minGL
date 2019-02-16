#include <iostream>
#include "include.h"

class MainWindow: public Window<MainWindow> {
public:
    LRESULT handleMessage(UINT uint, WPARAM wparam, LPARAM lparam) override {
        if(uint == WM_PAINT){
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(getWindowHandle(), &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
            EndPaint(getWindowHandle(), &ps);
        }
        return 0;
    }
};

using namespace std;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) {
    MainWindow window{};
    cout << window.getWindowClassName() << endl;
    cout << window.getTitle() << endl;
    window.setTitle("title");
    cout << window.getTitle() << endl;
    if(!window.create(hInstance)) return 1;
    return (int) (window.show(nCmdShow));
}
