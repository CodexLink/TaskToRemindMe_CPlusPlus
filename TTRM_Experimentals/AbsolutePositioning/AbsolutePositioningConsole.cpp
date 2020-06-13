#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>

void outputWndSize(HWND Console, RECT &ClientWindow);
unsigned int millis(double);

constexpr unsigned short TARGET_X = 970;
constexpr unsigned short TARGET_Y = 460;
unsigned int pX = 0, pY = 0;

int main(int argc, char *argv[])
{
    std::string consoleTitle = "Task To Remind Me Console Test.";
    HWND ConsoleWnd = GetConsoleWindow();
    RECT ConsoleWindow, ClientScrWindow;
    HMENU Console_BtnClose = GetSystemMenu(ConsoleWnd, FALSE);
    SetConsoleTitle(consoleTitle.c_str());
    outputWndSize(ConsoleWnd, ClientScrWindow);
    MoveWindow(ConsoleWnd, GetSystemMetrics(SM_CXSCREEN) / 4, GetSystemMetrics(SM_CYSCREEN) / 4, TARGET_X, TARGET_Y, true);
    outputWndSize(ConsoleWnd, ClientScrWindow);
    EnableMenuItem(Console_BtnClose, SC_CLOSE, MF_GRAYED);
    std::cout
        << "Output should be one." << std::endl;

    //  # OFFSET IS 14PX FOR WIDTH, 960 is desired. W /2 = 480
    // # OFFSET IS 7PX FOR HEIGHT,  460 is desired. H /2 = 230

    Sleep(millis(2.5));
    system("pause");
    return 0;
}

void outputWndSize(HWND Console, RECT &ClientWindow)
{
    static unsigned funcCalledTimes;
    funcCalledTimes++;
    GetWindowRect(Console, &ClientWindow);
    LONG dynaL = ClientWindow.left - ClientWindow.right, dynaR = ClientWindow.right - ClientWindow.left;
    std::cout << "Function Called " << funcCalledTimes << " Times. | "
              << "L < " << (int)(ClientWindow.left) << " | R > " << (int)(ClientWindow.right)
              << " | L Diff with R = " << dynaL
              << " | R Diff with L = " << dynaR << std::endl;
}

unsigned int millis(double sec)
{
    return (unsigned int)sec * 1000;
}