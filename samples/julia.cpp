#include <mingl>

int main() {
    const unsigned short width = 500;
    const unsigned short height = 500;

    const unsigned char numberOfIterations = 80;
    const double infinity = 4.;
    const double planeRange = 3.5;
    const double movePlaneToCenter = planeRange * .5;

    Window window("Julia", 100, 50, width, height);

    window.addOnMouseMoveHandler([&](const Gdiplus::Point &mousePosition) {
        const double ca = planeRange * mousePosition.X / width - movePlaneToCenter;
        const double cb = planeRange * mousePosition.Y / height - movePlaneToCenter;

        double zy, a, b, aa, bb;
        unsigned char iteration, color;
        for (unsigned short y = 0; y < height; ++y) {
            zy = planeRange * y / height - movePlaneToCenter;
            for (unsigned short x = 0; x < width; ++x) {
                iteration = 0;
                // MandelBrot:
                // a = 0, b = 0;

                // JuliaSet:
                a = planeRange * x / width - movePlaneToCenter, b = zy;
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
        window.redraw();
    });

    return window.show();
}
