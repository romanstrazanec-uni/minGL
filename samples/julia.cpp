#include <mingl>

int main() {
    const unsigned short width = 500;
    const unsigned short height = 500;

    const unsigned char numberOfIterations = 80;
    const double infinity = 4.;
    const double planeRange = 3.5;
    const double movePlaneToCenter = planeRange * .5;

    Window window("Julia", 100, 50, width, height);

    using namespace Gdiplus;
    Point mousePosition(width * .5, height * .5);

    window.addOnDrawHandler([&](Graphics *graphics) {
        const double ca = planeRange * mousePosition.X / width - movePlaneToCenter;
        const double cb = planeRange * mousePosition.Y / height - movePlaneToCenter;

        double cy, a, b, aa, bb;
        unsigned char iteration, color;
        for (unsigned short y = 0; y < height; ++y) {
            cy = planeRange * y / height - movePlaneToCenter;
            for (unsigned short x = 0; x < width; ++x) {
                iteration = 0;
                // MandelBrot:
                // a = 0, b = 0;

                // JuliaSet:
                a = planeRange * x / width - movePlaneToCenter, b = cy;
                while (iteration++ < numberOfIterations) {
                    aa = a * a;
                    bb = b * b;
                    if (aa + bb > infinity) break;

                    // MandelBrot:
                    // b = cy + 2 * a * b;
                    // a = cx + aa - bb;

                    // JuliaSet:
                    b = cb + 2 * a * b;
                    a = ca + aa - bb;
                }

                if (iteration == numberOfIterations) {
                    window.getCanvas().setPixel(x, y, RGBColor(0, 0, 0));
                } else {
                    color = static_cast<unsigned char>(255. * iteration / numberOfIterations);
                    window.getCanvas().setPixel(x, y, RGBColor(0, color, 0));
                }
            }
        }
    });

    window.addOnMouseMoveHandler([&mousePosition, &window](const Point &point) {
        mousePosition.X = point.X;
        mousePosition.Y = point.Y;
        window.redraw();
    });

    return window.show();
}
