/*
    # IO Handler Header Library for TTRM and Generic Console Library
    # ioHandlerDecl.h | Version PostWork.06202020.1633
    # Made by Janrey "CodexLink" Licas

    @descrip: Handles Outputs Elegantly By Requiring Only One Call Function Instead Of Stray ASCII Exposed in Source Code.
    @descrip: Handles Inputs By Logic [...]. Think of a handler with additional features on it such as actions to do when it returns false or something, it could run referenced function.

    ! Copyright
    
    # Copyright (C) 2020  Janrey "CodexLink" Licas

    ! This program is free software: you can redistribute it and/or modify
    ! it under the terms of the GNU General Public License as published by
    ! the Free Software Foundation, either version 3 of the License, or
    ! (at your option) any later version.

    ! This program is distributed in the hope that it will be useful,
    ! but WITHOUT ANY WARRANTY; without even the implied warranty of
    ! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    ! GNU General Public License for more details.

    ! You should have received a copy of the GNU General Public License
    ! along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <iostream>
#include <windows.h>

#define REQUIRE_SPECIAL_LAYOUTS

class IOHandler
{
    // # Private Class Scope for Struct and Variables
    // ! This is required to put up so that public and private functions could see any references.
private:
    // # Standard Output Colors. These are used for specific level or plays as important role of messages.
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

    typedef struct outCharStyle
    {
        char EMBRACE_START = '[',
             EMBRACE_END = ']',
             SEPERATOR_MID = '|';
    } _OUTPUT_SEP_N_EMBR; // ! Output Seperator and Embracer

    // # This struct contains all typedef structs which are Attributes.
    // ! We want to make things quite easier to access and quite visualizable to debug at.
    typedef struct outAttrs
    {
        static _OUTPUT_LVL_MESSAGE OUTPUT_LVL_MESSAGE;
        static _OUTPUT_SEP_N_EMBR OUTPUT_SEP_N_EMBR;
        static _COLOR_OUTPUT COLOR_OUTPUT;           // # static struct. This is where we modify things and store it here.
        static _STD_OUTPUT_COLORS STD_OUTPUT_COLORS; // # static struct. This is where we modify the Standard Outputs and apply it anytime.
    } _OUT_ATTRIBUTES;

    // ! Special Variables
    static _OUT_ATTRIBUTES OUT_ATTRS;    // # An Attribute To Access By Private Functions To Modify and Referenced at.
    CONSOLE_SCREEN_BUFFER_INFO ConsInfo; // # Required Struct. This is where we pust all information that HANDLE has.
    HANDLE ConsBuffHandler;              // # Required as we need to more information about the Console Information.
    DWORD lengthRef = NULL;              // # This will not be used. However required by Win32API. NULL'ing this will result in crash.

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
        EMBRACE_WHOLE_OUTPUT,
        EMBRACE_BOTH
    };

    enum IN_RET_FAIL_ACTIONS : unsigned
    {
        DO_NOTHING,
        RETURN_TRUE,
        RETURN_FALSE,
        RELAUNCH_FUNC
    };

    // # Constructor
    IOHandler(LAUNCH_OPTIONS launchType, EMBRACE_TYPE defaultEmbrace);

    // # Technical Overrider Functions
    /*
        @descrip: Most of the Extended Version Functions Overrides what's Inside of the following structs.
        ! 1. OUTPUT_LVL_MESSAGE
        ! 2. OUTPUT_SEP_N_EMBR
        ! 3. COLOR_OUTPUT
        * These are static structs and is under parent struct called (static)(typedef struct outAttr) _OUT_ATTRIBUTES.
        # Keep in mind that, if we used standard versions of Output Handler or used Extended Version but leaving it empty.
        # Anything that is inside of the following structs will be used further. This was the intended functionality to avoid re-calling
        # long @ss output handler functions with confusing arguments on it.
    */
    void changeDefStdOutColors(_COLOR_OUTPUT colorSet, OUTPUT_TYPE targetOutput); // ! This function cannot change output simulatenously. Has to call one by one for each output level / importance. This was intended to ensure that we're colorizing each output levels right.
    void changeDefOutColors(_COLOR_OUTPUT colorSet);
    void changeDefSeperator(const char sepSymbol); // Changes
    void changeDefEmbrace(const char embBegin, const char embEnd);

    /*
        # Output Handler Functions
        ! Involves Templates for Dynamic Acceptance of Value's Respective Data Type.
    */

    template <typename dt>
    void showOutput(dt literalOutput, COLOR_DEFINITIONS colorOutput, COLOR_DEFINITIONS colorMsg, OUTPUT_TYPE levelOutput, EMBRACE_TYPE embraceOutputType);
    /*
        ! 1. void showOutput()
            # Description: Standard Version of Output Handler. It Handles String and Outputs According To Parameters Given.
            # Parameters
            *   1. dt(anyDataType by template) literalOutput - Any Value That Follows Referenced Variable Data Type. WILL CONVERT TO STD::STRING AS POSSIBLE.
            *   2. COLOR_DEFINITIONS(enum) colorOutput - Colorizes the output of this one in particular. Default by WHITE. Illegal Workaround by using | operator is not recommended. Use showOutputEx() instead!
            *   3. OUTPUT_TYPE(enum) levelOutput - Appends Additional String to indicate the importance of message. Default by NONE. If user indicates other than that, it will automatically append it.
            *   4. EMBRACE_TYPE(enum) embraceOutputType - Add Styling by embracing output or the whole message or both with "[ ]". Secondary embracer is "( )".
            ! @returns > Styled Output.

            # Examples.
            1. -
            2. -
            3. -
    */

    template <typename dtEX>
    void showOutputEx(dtEX literalOutput, _COLOR_OUTPUT textColorSetOutput = {COLOR_DEFINITIONS::BRIGHT_WHITE, COLOR_DEFINITIONS::BRIGHT_YELLOW}, _COLOR_OUTPUT textColorSetMsg = {COLOR_DEFINITIONS::BRIGHT_WHITE, COLOR_DEFINITIONS::BRIGHT_YELLOW}, bool appendOutputType = true, OUTPUT_TYPE levelOutput = OUTPUT_TYPE::OUTPUT_NORMAL, EMBRACE_TYPE embraceOutputType = EMBRACE_TYPE::EMBRACE_OUTPUT_LEVEL); //# Uses fillColor();
/*
        ! 2. void showOutputEx()
            # Description: Extended Version of Output Handler. It has more arguments for further customizations to the output the user wants.
            # Parameters
            *   1. dt (anyDataType by template) literalOutput - Refer to void showOutput() regarding this one.
            *   2. _COLOR_OUTPUT textColorSetOutput = {COLOR_BACKGROUND, COLOR_FOREGROUND} - Sets Output Color Text Background and Foreground Under Provided Values or By Default On Storage Struct.
            *   3. _COLOR_OUTPUT textColorSetMsg = {COLOR_BACKGROUND, COLOR_FOREGROUND} - Sets Output Color Text Background and Foreground Under Provided Values or By Default On Storage Struct.
            *   4. appendOutputType(bool) - Check if appended Output Level Type should be done or not.
            *   5. OUTPUT_TYPE levelOutput(enum) = OUTPUT_TYPE::OUTPUT_NORMAL - Outputs Level Importance of Message.
            *   6. EMBRACE_TYPE embraceOutputType = EMBRACE_TYPE::EMBRACE_OUTPUT_LEVEL - A type of embracement should be done.
            *   7. bool shouldAddSeperator - Checks whether the output should have a seperator in between output level / importnace and message.
            *   8. char seperatorSymbol - Overrides Seperator indicated in the struct _OUTPUT_SEP_N_EMBR.SEPERATOR_MID. If (6) is set to false, (7) argument inputs will be ignored!
            ! @retuns > Even More Styled Output.

            # Examples.
            1. -
            2. -
            3. -
    */

// # Special Output Handler Functions
/*
        ! ...
    */
#ifdef REQUIRE_SPECIAL_LAYOUTS
    typedef struct sLayoutHexStorage
    {
        unsigned char HEX_START = 0,
                      HEX_RISE = 0,
                      HEX_CLIMAX = 0,
                      HEX_FALL = 0,
                      HEX_END = 0;
    } _LAYOUT_HEX_CONTAINER;

    typedef struct sLayoutColorStorage
    {
        unsigned char COLOR_START = 0,
                      COLOR_RISE = 0,
                      COLOR_CLIMAX = 0,
                      COLOR_FALL = 0,
                      COLOR_END = 0;
    } _LAYOUT_COLOR_CONTAINER;

    enum PRINT_METHODS
    {
        PRINT_X_LEFT,
        PRINT_X_RIGHT,
        PRINT_Y_UP,
        PRINT_Y_DOWN
    };

    static _LAYOUT_HEX_CONTAINER HEX_CONTAINER;

    // # Use case of this should be simple. Intention was to create a structure design without overrides such as a text to place in.
    void printLine(unsigned short w, unsigned short h, COORD curPos, unsigned char hexVal, PRINT_METHODS printDirection);

    // # Extended Versions of General Functions.
    void printLineEX(unsigned short w, unsigned short h, _LAYOUT_HEX_CONTAINER hexStruct, _LAYOUT_COLOR_CONTAINER colorStruct, COORD curPos, PRINT_METHODS printDirection);
#endif

    // # Input Handler Functions
    template <typename dtInRet>
    dtInRet handleInput(dtInRet *varRef = NULL); // # Variable Dynamic. Even though returned dynamically. We should give options to user to change something else.

    // # Investigate further if I want to go for std::function of normal pointer function such as void (*caller)(dt), where dt is DataType
    template <typename dtInRetEx, typename dtInRetFuncEx>
    dtInRetEx handleInputEx(dtInRetEx *varRef = NULL, IN_RET_FAIL_ACTIONS overridenRet = IN_RET_FAIL_ACTIONS::DO_NOTHING, dtInRetFuncEx (*triggerFunc)(...) = NULL); // # Variable Dynamic. Even though returned dynamically. We should give options to user to change something else.

    // # Private Class Scope Functions
private:
    // ! @todo | Need More Documentation About These Functions.
    // # // # Initializer Functions
    void initOutColors(); // # Argument To Modify is STD_OUTPUT_COLORS. Though since we're in Class Scope, no need to reference it since it's accessible.
    void initOutStdColors(); // # Argument To Modify is STD_OUTPUT_COLORS. Though since we're in Class Scope, no need to reference it since it's accessible.
    void initSeperator();
    void initEmbrace();

    // # Color Modifier Functions. Sets Output Type Strings Color. Both Two Functions Modify COLOR_OUTPUT static struct. No Default as this functions are modifiers.
    inline void setOutBG(unsigned char bgValue);
    inline void setOutFG(unsigned char fgValue);

    // # General Callable Function. This was a required function to void showOutputEx();
    inline void appendOutputType(const char *dataToAppend); // # Appends String along with output Type for Specified Importance of the Message. Also uses outSeperator.
    void calculateColor(_COLOR_OUTPUT textColorSet);
};