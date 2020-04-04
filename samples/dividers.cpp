#include <mingl>
#include <iostream>

int main() {
    Window window;
    window.setTitle("Delitele cisla");

    window.addLabel(1, "Zadaj cislo: ", 10, 10);

    NumberInput input(2, 130, 10, 50, 20);
    window.addNumberInput(&input);
    input.addStyle(WS_BORDER | ES_CENTER);

    TextInput output(&window, 3, 10, 40, 250, 250);
    output.addStyle(WS_BORDER | ES_AUTOVSCROLL | ES_MULTILINE);

    window.addButton(Button(4, "Vypocitaj", 190, 10, [&input, &output](Window *) {
        int number = std::stoi(input.getText());

        std::string result = "1\r\n";
        for (int i = 2; i < number; ++i) {
            if (number % i == 0) {
                result += std::to_string(i) + "\r\n";
            }
        }
        result += std::to_string(number);
        output.setText(result.c_str());
    }));

    window.show();
}