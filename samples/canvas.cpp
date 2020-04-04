#include <mingl>
#include <cstdlib>
#include <vector>

using namespace std;
using namespace Gdiplus;

int main() {
    Window window("Platno", 100, 100, 600, 600);

    vector<Point> points;

    Color color(0, 0, 0);

    window.addOnLeftMouseButtonDownHandler([&points, &window](Window *, POINT point) {
        points.emplace_back(point.x, point.y);
        window.redraw();
    });

    window.addOnDrawHandler([&points, &color](Graphics *graphics) {
        Pen pen(color);
        graphics->DrawLines(&pen, points.data(), points.size());
    });

    window.addOnRightMouseButtonDownHandler([&color, &window](Window *, POINT point) {
        color = Color(rand() % 256, rand() % 256, rand() % 256);
        window.redraw();
    });

    window.show();
}