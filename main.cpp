#include <windows.h>
#include <d2d1.h>
#include "GUI/Window.h"
#include "include.h"

//#define showwindow

#ifdef showwindow
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    try {
        Window window(hInstance, 0, 0, 1024, 768, (char *) ("The title of my window"));
        return (int)(window.show(nCmdShow));
    } catch (EXCEPTION_REGISTRATION exception_registration) { return 0; }
}
#else
#include <iostream>
using namespace std;
int main(){
    Point p1;
    Point p2(1,2);
    Point p3(p2);
    Point p4(Point(2, 3));

    p1 = p2;
    p2 = Point();
    Point p5 = Point(2,3);
    cout << p1.x << ", " << p1.y << endl;
    cout << p2.x << ", " << p2.y << endl;
    cout << p3.x << ", " << p3.y << endl;
    cout << p4.x << ", " << p4.y << endl;
    p5.move_to(5,16);
    cout << p5.x << ", " << p5.y << endl;
    return 0;
}
#endif