#pragma once

#include <windows.h>
#include "../IOHandler/IOHandler.h"

class SelectionMethods : private IOHandler {
public:

    SelectionMethods();
    ~SelectionMethods();

    void waitInput(const char *msgBeforeIn, char ASCIISeperator);

private:
    enum SEL_METHODS : unsigned char {
        ARROW_SELECTION,
        NUMBER_SELECTION,
        AGGRESIVE_NUMBER_SELECTION // ! Same with NUMBER_SELECTION. This one doesn't need enter input to proceed further.
    };

    void changeSelection(SEL_METHODS viewType);

};