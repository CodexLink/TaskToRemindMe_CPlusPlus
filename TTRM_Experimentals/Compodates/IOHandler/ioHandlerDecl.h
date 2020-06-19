#pragma once

#include <iostream>
#include <windows.h>

#define REQUIRE_SPECIAL_LAYOUTS

class IOHandler
{
public:
    // # This was done by observation. After compiling Demo.cpp and running Demo.exe inside this folder.
    // # As we searched further for more colors. I found this website similar to the patterns found on running Demo.exe
    // ! http://smallvoid.com/article/winnt-command-prompt-color.html

    // * Color Definitions declared here is a part of a legacy code in this library header.
    // ! i cannot further implement custom coloring such as the use case of RGB Macro.
    // @o We just have to embrace of what FillConsoleOutputAttribute() could offer by attribute manipulation.

    enum COLOR_DEFINITIONS : unsigned char
    {
        BLACK,
        DARK_ER_BLUE,
        DARK_GREEN,
        DARK_SKY_BLUE,
        DARK_RED,
        DARK_PINK,
        DARK_YELLOW,
        DARK_WHITE,
        DARK_GREY,
        DARK_BLUE,
        BRIGHT_GREEN,
        BRIGHT_SKY_BLUE,
        BRIGHT_RED,
        BRIGHT_PINK,
        BRIGHT_YELLOW,
        BRIGHT_WHITE
    };

    enum LAUNCH_OPTIONS : unsigned
    {
        NONE,                              // # Literally None. Use this generally if you dont want to apply unforseen changes.
        FORCE_IGNORE_STD_COLOR,            // # Apply only if we dont want to get blinded by rainbow everytime we want to debug or for other issues / reasons.
        FORCE_OVERRIDE_DEFAULT_COLOR_SETS, // # Apply if you want to change colors for problemIndicators. For instance, (Warning, Note, Critical, Reminder, etc...)
    };

    enum OUTPUT_TYPE : unsigned
    {
        OUTPUT_NORMAL,
        OUTPUT_INFO,
        OUTPUT_WARNING,
        OUTPUT_CRITICAL,
        OUTPUT_ERROR
    };

    enum EMBRACE_TYPE : unsigned
    {
        EMBRACE_NOTHING,
        EMBRACE_OUTPUT_LEVEL,
        EMBRACE_WHOLE_OUTPUT
    };

    enum IN_RET_FAIL_ACTIONS : unsigned
    {
        DO_NOTHING,
        RETURN_TRUE,
        RETURN_FALSE,
        RELAUNCH_FUNC,
        TRIGGER_REDO_ON_VAR // # Triggers a variable referenced to this class.
    };

    // # Constructor and Destructor.
    IOHandler(LAUNCH_OPTIONS launchType, EMBRACE_TYPE defaultEmbrace);
    // ! ~IOHandler(); Removal Possible.

    // void setColors();

    // # Technical Functions
    void changeSeperator(const char sepSymbol);

    // # Output Handler Functions
    template <typename dt>
    void showOutput(dt literalOutput, COLOR_DEFINITIONS colorOutput, OUTPUT_TYPE levelOutput, EMBRACE_TYPE embraceOutputType);
    template <typename dtEX>
    void showOutputEx(dtEX literalOutput, COORD textColorSet, bool appendOutputType, OUTPUT_TYPE levelOutput, EMBRACE_TYPE embraceOutputType); //# Uses fillColor();


// # Special Output Handler Functions
/*
    ! ...
*/
#ifdef REQUIRE_SPECIAL_LAYOUTS

    typedef struct sLayoutHexStorage {
        unsigned char HEX_START = 0,
                      HEX_RISE = 0,
                      HEX_CLIMAX = 0,
                      HEX_FALL = 0,
                      HEX_END = 0;
    } _LAYOUT_HEX_CONTAINER;

    enum PRINT_METHODS {
        PRINT_X,
        PRINT_Y
    };

    static _LAYOUT_HEX_CONTAINER HEX_CONTAINER;
    // # Use case of this should be simple. Intention was to create a structure design without overrides such as a text to place in.
    void printLine(unsigned short w, unsigned short h, COORD curPos, unsigned char hexVal, PRINT_METHODS printDirection);

    // # Extended Versions of General Functions.
    void printLineEX( unsigned short w, unsigned short h, _LAYOUT_HEX_CONTAINER hexStruct, _COLOR_OUTPUT colorOut, COORD curPos, PRINT_METHODS printDirection);
#endif

    // # Input Handler Functions
    template <typename dtInRet>
    dtInRet handleInput(dtInRet *varRef); // # Variable Dynamic. Even though returned dynamically. We should give options to user to change something else.
    template <typename dtInRetEx>
    dtInRetEx handleInputEx(dtInRetEx *varRef); // # Variable Dynamic. Even though returned dynamically. We should give options to user to change something else.

    // void handleInputEx(dtIn dataTypeReturn);

private:
    // # Standard Output Colors. These are used for specific level of messages.
    typedef struct stdOutputColors
    {
        unsigned char OUT_CLR_NORMAL = 0,
                      OUT_CLR_INFO = 0,
                      OUT_CLR_WARNING = 0,
                      OUT_CLR_CRITICAL = 0,
                      OUT_CLR_ERROR = 0;
    } _STD_OUTPUT_COLORS;

    // # Color Props. To Be Stored For Continuous Mode. (Apply The Following Till I Say False)
    typedef struct colorProps
    {
        unsigned char C_BG = 0,
                      C_FG = 0;
    } _COLOR_OUTPUT;

    // # Standard Output Message. These are being appended to the string provided appendOutputType() function.
    typedef struct outMsg
    {
        std::string OUT_MSG_NORMAL = "",
                    OUT_MSG_INFO = "INFO",
                    OUT_MSG_WARNING = "WARNING",
                    OUT_MSG_CRITICAL = "CRITICAL",
                    OUT_MSG_ERROR = "ERROR";
    } _OUTPUT_LVL_MESSAGE;

    typedef struct outEmbracer
    {
        char EMBRACE_START = '[',
             EMBRACE_END = ']';
    } _OUTPUT_EMBRACER;

    // # This struct contains all typedef structs which are Attributes.
    // ! We want to make things quite easier to access and quite visualizable to debug at.
    typedef struct outAttrs
    {
        static _OUTPUT_LVL_MESSAGE OUTPUT_LVL_MESSAGE;
        static _OUTPUT_EMBRACER OUTPUT_EMBRACER;
        static _COLOR_OUTPUT COLOR_OUTPUT;           // # static struct. This is where we modify things and store it here.
        static _STD_OUTPUT_COLORS STD_OUTPUT_COLORS; // # static struct. This is where we modify the Standard Outputs and apply it anytime.
    } _OUT_ATTRIBUTES;

    // ! Special Variables
    CONSOLE_SCREEN_BUFFER_INFO ConsInfo; // # Required Struct. This is where we put all information that HANDLE has.
    HANDLE ConsBuffHandler;              // # Required as we need to more information about the Console Information.
    DWORD lengthRef = NULL;              // # This will not be used. However required by Win32API. NULL'ing this will result in crash.

    // ! Standard Variables
    char outSeperator = '|';

    // # Class Functions
    void initOutColors(); // # Argument To Modify is STD_OUTPUT_COLORS STD_OUTPUT_COLORS. Though since we're in Class Scope, no need to reference it since it's accessible.
    void initEmbraceOutput();
    // # Sets Output Type Strings Color. Both Two Functions Modify COLOR_OUTPUT static struct.
    inline void setOutBG(unsigned char bgValue);
    inline void setOutFG(unsigned char fgValue);

    inline void appendOutputType(const char *dataToAppend); // # Appends String along with output Type for Specified Importance of the Message. Also uses outSeperator.
    // # Callable Function. This was a required function to void showOutputEx();
    void calculateColor(COORD textColorSet);
};