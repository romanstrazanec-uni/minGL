#include <mingl/mingl.h>

#include <iostream>

int main() {
    Window window;
    window.setTitle("title");
    window.addHandler(MessageHandler(Message::onPaint(), [](Window *w, Message) {
        HWND h = w->getWindowHandle();
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(h, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
        EndPaint(h, &ps);
    }));
    window.addHandler(Message::onClose(), [](Window *w, Message) {
        HWND h = w->getWindowHandle();
        if (MessageBox(h, "Really quit?", "My application", MB_OKCANCEL) == IDOK) DestroyWindow(h);
    });
    Button btn1(1, "hello", 50, 50, 50, 50, [] {
        std::cout << "hello" << std::endl;
    });
    Button btn2(0, "hi", 100, 50, 50, 50, [] {
        std::cout << "hi" << std::endl;
    });
    Button *btn3 = new Button(2, "new", 150, 50, 50, 50, [] {
        std::cout << "new" << std::endl;
    });
    window.addButton(&btn1);
    window.addButton(&btn2);
    window.addButton(btn3);
    if (!window.create()) return 1;
    window.show();
    return 0;
}
