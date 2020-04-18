#include <mingl>
#include <cstdlib> // rand()

int main() {
    // Inicializujeme okno.
    Window window("Nahodne kruhy", 100, 100, 500, 500);

    // Pridáme popis pre vstupné pole.
    window.addLabel(1, "Zadaj pocet: ", 10, 450, 100, 20);

    // Pridáme vstupné pole do okna. To nám vráti ukazovateľ na vytvorený objekt a môžeme s ním ďalej pracovať.
    NumberInput *numberInput = window.addNumberInput(2, 110, 450, 50, 20);

    // Vstupnému polu pridáme okraje a zarovnáme text doprava.
    numberInput->addBorder();
    numberInput->alignRight();

    // Potrebujeme premennú pre uchovávanie čísla zadaného zo vstupného pola.
    int number = 0;

    // Vytvoríme tlačidlo, ktorým získame číslo zo vstupného pola a prekreslíme okno.
    Button button(3, "Vykresli", 170, 450);

    // Funkciu tlačidlu môžeme pridať neskôr.
    button.addOnClickListener([&numberInput, &number, &window] {
        number = numberInput->getNumber();
        window.redraw();
    });

    // Tlačidlo pridáme do okna tak, že tlačidlu nastavíme rodiča adresu okna.
    // Každý objekt si uchováva informáciu o rodičovi.
    button.setParent(&window);

    // Pre kreslenie využijeme knižnicu Gdiplus a aby sme nemuseli pred každý jej objekt písať menný priestor,
    // napíšeme, že ideme používať menný priestor Gdiplus.
    using namespace Gdiplus;

    // Do okna pridáme funkciu, ktorá sa vykoná pri vykreslení. Tá nám poskytuje ukazovateľ na objekt Graphics,
    // ktorým vieme kresliť rôzne útvary. Taktiež zachytíme číslo zo vstupného pola z vonkajšieho prostredia.
    window.addOnDrawHandler([&number](Graphics *graphics) {
        while (number--) {
            // Pre vykreslenie kruhu potrebujeme priemer. Ten použijeme ako šírku aj výšku elipsy a keďže je rovnaký
            // pre obe hodnoty, vytvoríme tak kruh. Hodnota je nastavená od 20 po 80.
            int diameter = rand() % 61 + 20;

            // Náhodne vyberieme, či nakreslíme kružnicu alebo kruh. Útvaru nastavíme súradnice tak, aby nepretínal okno.
            if (rand() % 2) {
                // Pre kružnicu potrebujeme pero, ktorému nastavíme náhodnú farbu.
                Pen pen(Color(rand() % 256, rand() % 256, rand() % 256));
                graphics->DrawEllipse(&pen, rand() % 406 + 45, rand() % 406 + 45, diameter, diameter);
            } else {
                // Pre kruh potrebujeme štetec, ktorému takisto nastavíme náhodnú farbu.
                SolidBrush brush(Color(rand() % 256, rand() % 256, rand() % 256));
                graphics->FillEllipse(&brush, rand() % 361 + 45, rand() % 361 + 45, diameter, diameter);
            }
        }
    });

    // Nakoniec zobrazíme okno.
    return window.show();
}
