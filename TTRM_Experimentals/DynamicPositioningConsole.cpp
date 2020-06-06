#include <windows.h>
#include <iostream>

#include <sstream>
#include <string>

int main(int argc, char *argv[])
{
    long Console_PosX = 0, Console_PosY = 0;
    HWND ConsoleWnd = GetConsoleWindow();
    RECT ConsoleWindow, ClientScrWindow;
    HMENU Console_BtnClose = GetSystemMenu(ConsoleWnd, FALSE);

    GetClientRect(ConsoleWnd, &ConsoleWindow);
    GetWindowRect(ConsoleWnd, &ClientScrWindow);

    // # Need to work this one better. Create another example regarding this one.
    Console_PosX = GetSystemMetrics(SM_CXSCREEN) / 2 - (ClientScrWindow.right - ClientScrWindow.left) / 2,
    Console_PosY = GetSystemMetrics(SM_CYSCREEN) / 2 - (ClientScrWindow.bottom - ClientScrWindow.top) / 2,
    MoveWindow(ConsoleWnd, Console_PosX, Console_PosY, ClientScrWindow.right - ClientScrWindow.left, (ClientScrWindow.bottom - ClientScrWindow.top) * 2, TRUE);
    EnableMenuItem(Console_BtnClose, SC_CLOSE, MF_GRAYED);

    std::cout << "Output should be one." << std::endl;

    system("pause");
    return 0;
}