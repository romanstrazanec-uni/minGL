#include <mingl>
#include <cstdlib> // rand()
#include <vector> // std::vector

using namespace Gdiplus;

int main() {
    // Vytvoríme nové okno.
    Window window("Platno", 100, 100, 600, 600);

    // Vytvoríme vector pre uchovávanie bodov.
    std::vector<Point> points;

    // Vytvoríme farbu.
    Color color(0, 0, 0);

    // Pridáme funkciu vykonávanú po stlačení ľavého tlačidla myši.
    // Pridáme ňou nový bod do vykreslovaného útvaru.
    // Typ druhého parametra je bod z knižnice Gdiplus. Obsahuje pozíciu kliknutia myši teda jeho súradnice x a y.
    // Aby sme predišli zbytočnému kopírovaniu objektu, môžeme ho označiť ako odkaz na L-hodnotu (const Point &) alebo
    // odkaz na R-hodnotu (Point &&). Preferovanou voľbou je odkaz na R-hodnotu keďže je objekt vytvorený na mieste.
    window.addOnLeftMouseButtonDownHandler([&points, &window](Point &&point) {
        points.emplace_back(point); // todo: SIGSEGV
        window.redraw();
    });

    // Pridáme funkciu vykonávanú po stlačení pravého tlačidla myši.
    // Táto funkcia zmení farbu na náhodnú a prekreslí okno.
    window.addOnRightMouseButtonDownHandler([&color, &window](Point &&) {
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
    return window.show();
}