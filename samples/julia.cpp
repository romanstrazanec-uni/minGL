#include <mingl>
#include <graphics/bitmap.hpp>

int main() {
    const unsigned short width = 500;
    const unsigned short height = 500;
    BitMap bitmap(width, height);

    const unsigned char number_of_iterations = 80;
    const double infinity = 4.;
    const double plane_range = 3.5;
    const double move_plane_to_center = plane_range * .5;

    Window window("Julia", 100, 50, width, height);

    using namespace Gdiplus;
    Point mousePosition(width * .5, height * .5);

    window.addOnDrawHandler([&](Graphics *graphics) {
        const double ca = plane_range * mousePosition.X / width - move_plane_to_center;
        const double cb = plane_range * mousePosition.Y / height - move_plane_to_center;

        double cy, a, b, aa, bb;
        unsigned char iteration, color;
        for (unsigned short y = 0; y < height; ++y) {
            cy = plane_range * y / height - move_plane_to_center;
            for (unsigned short x = 0; x < width; ++x) {
                iteration = 0;
                // MandelBrot:
                // a = 0, b = 0;

                // JuliaSet:
                a = plane_range * x / width - move_plane_to_center, b = cy;
                while (iteration++ < number_of_iterations) {
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

                if (iteration == number_of_iterations) {
                    bitmap.setPixel(x, y, 0, 0, 0);
                } else {
                    color = static_cast<unsigned char>(255. * iteration / number_of_iterations);
                    bitmap.setPixel(x, y, 0, color, 0);
                }
            }
        }
        Bitmap bitmap2(width, height, width * 3, PixelFormat24bppRGB, bitmap.getData());
        graphics->DrawImage(&bitmap2, 0, 0);
    });

    window.addOnLeftMouseButtonDownHandler([&mousePosition, &window](Point &&point) {
        mousePosition.X = point.X;
        mousePosition.Y = point.Y;
        window.redraw();
    });

    return window.show();
}
