#include <mingl>

#include <vector>
#include <memory>

using namespace std;
using namespace Gdiplus;

struct ColorPath {
    Color color{};
    unique_ptr<vector<Point>> path{new vector<Point>};

    ColorPath() = default;
    ColorPath(const Color &c) : color(c) {}
    ColorPath(const Color &c, const POINT &p) : color(c) { addPoint(p); }

    void addPoint(const POINT &p) { path->emplace_back(p.x, p.y); }

    Point *points() const { return path->data(); }

    ULONG size() const { return path->size(); }
};

int main() {
    Window w(100, 100, 500, 500);
    w.setTitle("Mouse interaction app");

    vector<Point> points;
    UINT8 nPoints = 0;
    Color c(255, 255, 0, 0);
    bool lButtonDown = false;

    vector<ColorPath> paths;

    w.addButton(1, "Red", 10, 10, 50, 20, [&c](Window *) {
        c = Color(255, 255, 0, 0);
    });
    w.addButton(2, "Green", 10, 40, 50, 20, [&c](Window *) {
        c = Color(255, 0, 255, 0);
    });
    w.addButton(3, "Blue", 10, 70, 50, 20, [&c](Window *) {
        c = Color(255, 0, 0, 255);
    });

    w.addOnRightMouseButtonDownHandler([&](Window *w, POINT point) {
        points.emplace_back(point.x, point.y);
        if (nPoints > 10) points.erase(points.begin());
        else ++nPoints;

        w->redraw();
    });

    w.addOnDrawHandler([&](Graphics *g) {
        Pen pen(c);
        g->DrawLines(&pen, points.data(), points.size());

        if (!lButtonDown)
            for (const auto &path : paths) {
                pen.SetColor(path.color);
                g->DrawLines(&pen, path.points(), path.size());
            }
    });

    w.addOnLeftMouseButtonDownHandler([&](Window *, POINT p) {
        lButtonDown = true;
        paths.emplace_back(c, p);
    });

    w.addOnLeftMouseButtonUpHandler([&](Window *, POINT p) {
        paths.end()->addPoint(p);
        lButtonDown = false;
    });

    w.addOnMouseMoveHandler([&](Window *, POINT p) {
        if (lButtonDown) paths.end()->addPoint(p); // todo: segmentation fault
    });

    w.show();
    return 0;
}
