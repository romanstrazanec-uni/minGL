#define NO_GDIPLUS

#include <mingl/mingl.h>
#include <iostream>

using namespace std;

// todo: no global object creation allowed
EditText *eName;
EditText *eAge;
EditText *eOut;

void onClick(Window *w) {
    cout << "Click" << endl;
    char name[30], age[10], out[50];
    HWND hName = eName->getWindowHandle();
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

    cout << "end of onClick" << endl;
}

int main() {
    Window w(100, 100, 500, 500);

    eName = new EditText(200, 50, 90, 38);
    eAge = new EditText(200, 90, 98, 38);
    eOut = new EditText(100, 200, 300, 200);

    // todo: this does not create a label
    cout << "adding name label..." << endl;
    w.addLabel("Name: ", 100, 50, 98, 38);

    cout << "adding age label..." << endl;
    Label l("Age: ", 100, 90, 98, 38);
    w.addLabel(&l);

    cout << "editing styles of edittext..." << endl;
    eName->addStyle(WS_BORDER);
    eAge->addStyle(WS_BORDER);
    eOut->addStyle(WS_BORDER);

    cout << "passing edittexts to window..." << endl;
    w.addEditText(eName);
    w.addEditText(eAge);
    w.addEditText(eOut);

    cout << "creating a button..." << endl;
    Button b(4, "Generate", 150, 140, 98, 38, onClick);
    cout << "adding button..." << endl;
    w.addButton(&b);

    w.show();
    return 0;
}

