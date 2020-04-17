#include <mingl>

#include <vector>

using namespace std;
using namespace Gdiplus;

struct ColorPath {
    Color color{};
    vector<Point> path{};

    ColorPath() = default;
    ColorPath(const Color &c) : color(c) {}
    ColorPath(const Color &c, const Point &p) : color(c) { addPoint(p); }

    void addPoint(const Point &p) { path.emplace_back(p); }
};

int main() {
    Window w(100, 100, 500, 500);
    w.setTitle("Mouse interaction app");

    vector<Point> points;
    UINT8 nPoints = 0;
    Color c(255, 255, 0, 0);
    bool lButtonDown = false;

    vector<ColorPath> paths;

    // todo: mutable not required??
    w.addButton(1, "Red", 10, 10, 50, 20, [&c] {
        c = Color(255, 255, 0, 0);
    });
    w.addButton(2, "Green", 10, 40, 50, 20, [&c] {
        c = Color(255, 0, 255, 0);
    });
    w.addButton(3, "Blue", 10, 70, 50, 20, [&c] {
        c = Color(255, 0, 0, 255);
    });

    w.addOnRightMouseHandler([&](const Point &point) {
        points.emplace_back(point);
        if (nPoints > 10) points.erase(points.begin());
        else ++nPoints;

        w.redraw();
    });

    w.addOnDrawHandler([&](Graphics *g) {
        Pen pen(c);
        g->DrawLines(&pen, points.data(), points.size());

        if (!lButtonDown)
            for (const auto &path : paths) {
                pen.SetColor(path.color);
                g->DrawLines(&pen, path.path.data(), path.path.size());
            }
    });

    w.addOnLeftMouseHandler([&lButtonDown, &paths, &c](const Point &p) {
        lButtonDown = true;
        paths.emplace_back(c, p);
    });

    w.addOnLeftMouseUpHandler([&lButtonDown, &paths](const Point &p) {
        if (!paths.empty()) paths.back().addPoint(p);
        lButtonDown = false;
    });

    w.addOnMouseMoveHandler([&](const Point &p) {
        if (lButtonDown) paths.back().addPoint(p);
    });

    return w.show();
}
