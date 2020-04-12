#include <mingl>

int main() {
    Window window("GDI+ Test", 100, 50, 800, 600);

    window.addOnDrawHandler([](Gdiplus::Graphics *graphics) {
        Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));
        Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 255, 0));

        graphics->DrawLine(&pen, 0, 0, 500, 500);
        graphics->FillRectangle(&brush, 400, 200, 100, 100);
        graphics->DrawRectangle(&pen, 450, 400, 100, 150);
    });

    return window.show();
}
