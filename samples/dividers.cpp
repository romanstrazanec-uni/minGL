#include <mingl>
#include <iostream>

int main() {
    Window window;
    window.setTitle("Delitele cisla");

    window.addLabel(1, "Zadaj cislo: ", 10, 10);

    NumberInput input(2, 130, 10, 50, 20);
    input.addBorder();
    input.alignCenter();
    window.addNumberInput(&input);

    TextInput output(&window, 3, 10, 40, 250, 100);
    output.addBorder();
    output.enableVerticalScroll();
    output.enableMultiLine();
    output.readOnly();

    window.addButton(Button(4, "Vypocitaj", 190, 10, [&input, &output](Window *) {
        unsigned long number = input.getNumber();

        /*
        std::string result = "1\r\n";
        for (int i = 2; i < number; ++i) {
            if (number % i == 0) {
                result += std::to_string(i) + "\r\n";
            }
        }
        result += std::to_string(number);
        output.setText(result.c_str());
        */

        output.setText("");

        output.writeLine("1");
        for (int i = 2; i < number; ++i) {
            if (number % i == 0) {
                output.writeLine(std::to_string(i));
            }
        }
        output.writeLine(std::to_string(number));
    }));

    window.show();
}