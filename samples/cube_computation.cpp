#include <mingl>

int main() {
    // Inicializujeme nové okno.
    Window window{"Vypocet objemu a povrchu kocky", 100, 100, 250, 100};

    // Pridáme text pre použitie číselného vstupu pola.
    window.addLabel(1, "Zadaj dlzku hrany: ", 10, 20, 100, 20);

    // Pridáme pole pre zadávanie dĺžky hrany.
    // Prvý parameter tejto metódy je identifikátor objektu. Je dôležitý pri vyhľadávaní objektov v okne.
    window.addNumberInput(2, 140, 20, 50, 20);

    // Pridáme tlačidlo pre výpočet.
    // Posledný parameter tejto metódy je funkcia, ktorú tlačidlo po jeho stlačení vykoná.
    // Túto funkciu je možné definovať mimo funkcie main, ale v tomto prípade ju vytvoríme
    // na mieste pomocou výrazu lambda a zachytíme okno z vonkajšieho prostredia.
    window.addButton(3, "Vypocitaj", 10, 40, 50, 20, [&window] {
        // Získame objekt pomocou jeho identifikátoru.
        auto numberInput = window.find<NumberInput>(2);

        // Z objektu získame zadané číslo.
        unsigned long length = numberInput->getNumber();

        // Vypočítame objem a povrch.
        unsigned long volume = length * length * length;
        unsigned long surface = 6 * length * length;

        // Vytvoríme správu pre MessageDialog.
        // Keďže potrebujeme správu poskladať použíjeme reťazcový dátový typ string.
        // Na konverziu čísla do reťazcu použijeme funkciu zo štandardnej knižnice to_string().
        std::string message = "Objem: " + std::to_string(volume) + "; povrch: " + std::to_string(surface);

        // Zobrazíme MessageDialog.
        // Táto metóda si namiesto reťazcov pýta ukazovateľ na typ char, ktorým sa v jazyku C reťazce nahrádzali.
        // Preto treba pomocou metódy c_str() tento ukazovateľ získať.
        window.showMessageDialog("Vypocet", message.c_str());
    });

    // Otvoríme okno a tým spustíme aplikáciu.
    return window.show();
}
