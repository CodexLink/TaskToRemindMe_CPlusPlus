/*

    # IO Handler Header Library for TTRM and Generic Console Library
    # ioHandlerDecl.cpp | Version PostWork.06202020.1633
    # Made by Janrey "CodexLink" Licas

    @descrip: Handles Outputs Elegantly By Requiring Only One Call Function Instead Of Stray ASCII Exposed in Source Code.
    @descrip: Core Function Definition Declared at ioHandler.h

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
#include "ioHandlerDecl.h"

// # Constructor - START POINT

IOHandler::IOHandler(LAUNCH_OPTIONS launchType = LAUNCH_OPTIONS::NONE, EMBRACE_TYPE defaultEmbrace = LAUNCH_OPTIONS::EMBRACE_OUTPUT_LEVEL)
{
}

// # Constructor - END POINT

// # Technical Overrider Functions - START POINT

void IOHandler::changeDefStdOutColors(_COLOR_OUTPUT colorSet, OUTPUT_TYPE targetOutput)
{
}

void IOHandler::changeDefOutColors(_COLOR_OUTPUT colorSet)
{
}

void IOHandler::changeDefSeperator(const char sepSymbol)
{
}

void IOHandler::changeDefEmbrace(const char embBegin, const char embEnd)
{
}

// # Technical Overrider Functions - END POINT

// # Output Handler Functions - START POINT

template <typename dtMin>
void showOutputMin(dtMin literalOutput, STATE_CONFIG storeConfigToUse = STATE_CONFIG::RETAIN_LAST_SET_FLAG)
{
}

template <typename dt>
void IOHandler::showOutput(dt literalOutput, COLOR_DEFINITIONS colorOutput = COLOR_DEFINITIONS::BRIGHT_WHITE, COLOR_DEFINITIONS colorMsg = COLOR_DEFINITIONS::BRIGHT_WHITE, OUTPUT_TYPE levelOutput = OUTPUT_TYPE::OUTPUT_NORMAL, EMBRACE_TYPE embraceOutputType = EMBRACE_TYPE::EMBRACE_OUTPUT_LEVEL)
{
}

template <typename dtEX>
void IOHandler::showOutputEx(dtEX literalOutput, _COLOR_OUTPUT textColorSetOutput, _COLOR_OUTPUT textColorSetMsg, bool appendOutputType = true, OUTPUT_TYPE levelOutput, EMBRACE_TYPE embraceOutputType)
{
}

// # Output Handler Functions - END POINT

// # Special Output Handler Functions - START POINT

#ifdef REQUIRE_SPECIAL_LAYOUTS
void printLine(unsigned short w, unsigned short h, COORD curPos, unsigned char hexVal, PRINT_METHODS printDirection)
{
}

void IOHandler::printLineEX(unsigned short w, unsigned short h, _LAYOUT_HEX_CONTAINER hexStruct, _LAYOUT_COLOR_CONTAINER colorStruct, COORD curPos, PRINT_METHODS printDirection)
{
}
#endif

// # Special Output Handler Functions - END POINT

// # Input Handler Functions - START POINT

template <typename dtInRet>
dtInRet IOHandler::handleInput(dtInRet *varRef = NULL)
{
}

template <typename dtInRetEx, typename dtInRetFuncEx>
dtInRetEx IOHandler::handleInputEx(dtInRetEx *varRef = NULL, IN_RET_FAIL_ACTIONS overridenRet = IN_RET_FAIL_ACTIONS::DO_NOTHING, dtInRetFuncEx (*triggerFunc)(...) = NULL)
{
}

// # Input Handler Functions - END POINT

// # Private Class Scope Functions - START POINT

// # Initializer Functions - START POINT

void IOHandler::initOutColors()
{
}
void IOHandler::initOutStdColors()
{
}
void IOHandler::initSeperator()
{
}
void IOHandler::initEmbrace()
{
}

// # Initializer Functions - END POINT

// # Color Modifier Functions - START POINT

inline void IOHandler::setOutBG(unsigned char bgValue)
{
}
inline void IOHandler::setOutFG(unsigned char fgValue)
{
}

// # Color Modifier Functions - END POINT

// # General Callable Functions - START POINT

inline void IOHandler::appendOutputType(const char *dataToAppend)
{
}
void IOHandler::calculateColor(_COLOR_OUTPUT textColorSet)
{
}

// # General Callable Functions - END POINT

// # Private Class Scope Functions - END POINT