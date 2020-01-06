#define NO_GDIPLUS

#include <mingl>
#include <iostream>

using namespace std;

int main() {
    Window w(100, 100, 500, 500);

    EditText eName(1, 200, 50, 90, 38);
    EditText eAge(2, 200, 90, 98, 38);
    EditText eOut(3, 100, 200, 300, 200);

    eName.addStyle(WS_BORDER);
    eAge.addStyle(WS_BORDER);
    eOut.addStyle(WS_BORDER);

    Button b(6, "Generate", 150, 140, 98, 38, [](Window *w) {
        cout << "Click" << endl;
        char name[30], age[10], out[50];

        EditText *eName = w->find<EditText>(1);
        EditText *eAge = w->find<EditText>(2);
        EditText *eOut = w->find<EditText>(3);

        /*HWND hName = eName->getWindowHandle();
        cout << "hName gets a handle" << endl;

        if (eName->isCreated()) cout << "hName is created" << endl;
        else cout << "hName is not created" << endl;

        cout << "get hName window text" << endl;
        GetWindowText(hName, name, 30);
        cout << "get hAge window text" << endl;
        GetWindowText(eAge->getWindowHandle(), age, 30);

        cout << "str copy" << endl;
        strcpy(out, name);
        strcat(out, " is ");
        strcat(out, age);
        strcat(out, " yo.");

        cout << "set hOut window text" << endl;
        SetWindowText(eOut->getWindowHandle(), out);
*/
        cout << "end of onClick" << endl;
    });
    w.addButton(&b);

    Label lAge(5, "Age: ", 100, 90, 98, 38);
    w.addLabel(4, "Name: ", 100, 50, 98, 38);
    w.addLabel(&lAge);

    w.addEditText(&eName);
    w.addEditText(&eAge);
    w.addEditText(&eOut);

    w.show();
    return 0;
}

