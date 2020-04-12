#include <mingl>

#include <iostream>

int main() {
    Window window;
    window.setTitle("title");
    window.addHandler(WindowMessage::onClose(), [](Window *w, WindowMessage) {
        HWND h = w->getWindowHandle();
        if (MessageBox(h, "Really quit?", "My application", MB_OKCANCEL) == IDOK) DestroyWindow(h);
    });

    // constructing a button and assigning it to window
    Button btn1(1, "stack button", 50, 50, 100, 50, [] {
        std::cout << "stack button" << std::endl;
    });
    window.addButton(&btn1);

    // creating button with parent
    Button btn2(&window, 0, "button with parent", 50, 100, 100, 50, [] {
        std::cout << "button with parent" << std::endl;
    });

    // allocating memory for button and assigning it to window
    auto btn3 = new Button(2, "heap button", 50, 150, 100, 50, [] {
        std::cout << "heap button" << std::endl;
    });
    window.addButton(btn3);

    // passing button as rvalue
    window.addButton(Button(3, "rvalue button", 50, 200, 100, 50, [] {
        std::cout << "rvalue button" << std::endl;
    }));

    // passing label as rvalue
    window.addLabel(Label(4, "rvalue label", 50, 0, 100, 50));

    window.addTextInput(5, "edit text", 50, 250, 100, 50);

    return window.show();
}
