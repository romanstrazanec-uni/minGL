#include <mingl>

int main() {
    // Inicializujeme nové okno.
    Window window{"Vypocet objemu a povrchu kocky", 100, 100, 250, 100};

    // Pridáme text pre použitie editovacieho pola.
    window.addLabel(1, "Zadaj dlzku hrany: ", 10, 20, 100, 20);

    // Pridáme editovacie pole pre zadávanie dĺžky hrany.
    // Prvý parameter tejto metódy je identifikátor objektu. Je dôležitý pri vyhľadávaní objektov v okne.
    window.addTextInput(2, "", 140, 20, 50, 20);

    // Pridáme tlačidlo pre výpočet.
    // Posledný parameter tejto metódy je funkcia, ktorú tlačidlo po jeho stlačení vykoná.
    // Túto funkciu je možné definovať mimo funkcie main, ale v tomto prípade ju vytvoríme
    // na mieste pomocou výrazu lambda, ktorého parametrom je ukazovateľ na vytvorené okno.
    window.addButton(3, "Vypocitaj", 10, 40, 50, 20, [](Window *w) {
        // Získame objekt pomocou jeho identifikátoru.
        auto textInput = w->find<TextInput>(2);

        // Pretypujeme text z objektu na číslo.
        int length = std::stoi(textInput->getText());

        // Vypočítame objem a povrch.
        int volume = length * length * length;
        int surface = 6 * length * length;

        // Vytvoríme správu pre MessageDialog.
        // Keďže potrebujeme správu poskladať použíjeme reťazcový dátový typ string.
        // Na konverziu čísla do reťazcu použijeme funkciu zo štandardnej knižnice to_string().
        std::string message = "Objem: " + std::to_string(volume) + "; povrch: " + std::to_string(surface);

        // Zobrazíme MessageDialog.
        // Táto metóda si namiesto reťazcov pýta ukazovateľ na typ char, ktorým sa v jazyku C reťazce nahrádzali.
        // Preto treba pomocou metódy c_str() tento ukazovateľ získať.
        w->showMessageDialog("Vypocet", message.c_str());
    });

    // Otvoríme okno a tým spustíme aplikáciu.
    window.show();
}
