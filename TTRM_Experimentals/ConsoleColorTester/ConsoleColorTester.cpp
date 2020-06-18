#include <iostream>
#include <windows.h>

int main(int argc, char const *argv[])
{
    HANDLE ConsoleBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD lengthRef = 0; // ! This wasn't required but supply it anyway.
    CONSOLE_SCREEN_BUFFER_INFO ConsAttribute;
    std::string payLoad = "Hello World!";

    // # Implementation seem's unusual but this is how it should be I guess.

    GetConsoleScreenBufferInfo(ConsoleBuffer, &ConsAttribute);
    std::cout << payLoad << std::endl;
    FillConsoleOutputAttribute(ConsoleBuffer, (BACKGROUND_RED | (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)), payLoad.size(), ConsAttribute.dwCursorPosition, &lengthRef);

    SetConsoleCursorPosition(ConsoleBuffer, {5, 5});

    GetConsoleScreenBufferInfo(ConsoleBuffer, &ConsAttribute);
    std::cout << payLoad << std::endl;
    FillConsoleOutputAttribute(ConsoleBuffer, (BACKGROUND_RED | (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)), payLoad.size(), ConsAttribute.dwCursorPosition, &lengthRef);

    char a;
    std::cin >> a;
    return 0;
}