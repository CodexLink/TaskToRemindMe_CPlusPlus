#include <iostream>
#include <windows.h>

int main(int argc, char const *argv[])
{
    HANDLE ConsoleBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD lengthRef = 0; // ! This wasn't required but supply it anyway.
    CONSOLE_SCREEN_BUFFER_INFO ConsAttribute;
    std::string payLoad = "I want to be nice today!";

    // # Implementation seem's unusual but this is how it should be I guess.

    GetConsoleScreenBufferInfo(ConsoleBuffer, &ConsAttribute);
    std::cout << payLoad << std::endl;
    FillConsoleOutputAttribute(ConsoleBuffer, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE), payLoad.size(), ConsAttribute.dwCursorPosition, &lengthRef);

    SetConsoleCursorPosition(ConsoleBuffer, {5, 5});

    GetConsoleScreenBufferInfo(ConsoleBuffer, &ConsAttribute);
    std::cout << payLoad << std::endl;
    /*
    # FOREGROUND COLORS = 0 TO 15 (1 TO 16)
    # BACKGROUND COLORS = CONTAINS 16 COLORS BUT COLOR STARTS AT INDEX 1 WHEN BASED ON FOREGROUND COLORS
    #
    #
    # FOR INSTANCE, IF WE WANT DARK BLUE BACKGROUND AND ALSO WANTS YELLOW FOREGROUND
    #
    # THEN, AS WE BASED FROM FOREGROUND COLORS FROM (1 < X < 16)
    #
    # LET A AS BACKGROUND  |> VALUE AS 1
    # LET B AS FOREGROUND  |> VALUE AS 14
    #
    # CALCULATE ALSO THE DISTANCE FOR EACH COLOR ON BACKGROUND = 16 * COLOR BASED FROM FOREGROUND
    # IF WE WANT DARK BLUE BACKGROUND = THEN 16 * 1
    #
    #
    # FORMULA IS = (16 * FOREGROUND_BASE_COLOR) + FOREGROUND
*/
    FillConsoleOutputAttribute(ConsoleBuffer, ((16 * 1) + 14), payLoad.size(), ConsAttribute.dwCursorPosition, &lengthRef);
    char a;
    std::cin >> a;
    return 0;
}