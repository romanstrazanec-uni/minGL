#include <mingl>
#include <cstdlib>
#include <vector>

using namespace std;
using namespace Gdiplus;

int main() {
    // Vytvoríme nové okno.
    Window window("Platno", 100, 100, 600, 600);

    // Vytvoríme vector pre uchovávanie bodov.
    vector<Point> points;

    // Vytvoríme farbu.
    Color color(0, 0, 0);

    // Pridáme funkciu vykonávanú po stlačení ľavého tlačidla myši.
    // Pridáme ňou nový bod do vykreslovaného útvaru.
    window.addOnLeftMouseButtonDownHandler([&points, &window](Window *, POINT point) {
        points.emplace_back(point.x, point.y);
        window.redraw();
    });

    // Pridáme funkciu vykonávanú po stlačení pravého tlačidla myši.
    // Táto funkcia zmení farbu na náhodnú a prekreslí okno.
    window.addOnRightMouseButtonDownHandler([&color, &window](Window *, POINT point) {
        color = Color(rand() % 256, rand() % 256, rand() % 256);
        window.redraw();
    });

    // Pridáme funkciu pre vykreslovanie.
    window.addOnDrawHandler([&points, &color](Graphics *graphics) {
        // Potrebujeme vytvoriť pero s nastavenou farbou.
        Pen pen(color);

        // Metóda DrawLines() nakreslí úsečky medzi bodmi, ktoré zadáme ako druhý parameter.
        // Tento parameter je pole bodov, ktoré z vectoru získame metódou data() a tým pádom potrebujeme zadať aj
        // údaj o veľkosti pola do tretieho parametra.
        graphics->DrawLines(&pen, points.data(), points.size());
    });

    // Zobrazíme nové okno.
    window.show();
}