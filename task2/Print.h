#include <windows.h>
#include <string>
#include <iostream>

using namespace std;

namespace print {

    class Print {
    public:
        void printRes(int color, string message, int id);
    };

    void Print::printRes(int color, string message, int id = -1) {

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (id == -1) {
            SetConsoleTextAttribute(hConsole, color | FOREGROUND_INTENSITY);
            cout << message << endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        else {
            SetConsoleTextAttribute(hConsole, color | FOREGROUND_INTENSITY);
            cout << "Клиент " << id << message << endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
    }
}
