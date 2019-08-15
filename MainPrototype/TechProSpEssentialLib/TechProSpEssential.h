// Technical Project Specific Essential Function Header File by Janrey "CodexLink" Licas

#ifndef TECHPROSPESSENTIAL_H
#define TECHPROSPESSENTIAL_H // We define this marker for indication of "already initialized"

#include <iostream>
#include <string>
#include "WinToastLib/wintoastlib.h"
#include <windows.h> // For Win32 API, We manipulate our console here.
using namespace WinToastLib;
/*
    ENUMs, A Group or contains that specific values that classifies specialized for returning
    reference values. For example, we need a group of reference values for returning error codes.
    Hence, this example is refernced to our first ENUM called TERM_RET_ERROR
*/
// TERM_RET_ERROR - An ENUM that contains Termination Return Error. Useful for Deconstructor Error Display
enum TERM_RET_ERROR
{
    TERM_SUCCESS = 0,
    TERM_FAILED = -1,
    TERM_INVALID_PARAM = -2
};

// CODE_RET_PROCESS - An ENUM that contains Function Returning Values for Processing Functions
enum CODE_RET_PROCESS
{
    RETURN_NULL = 0
};

// CODE_CONSTRAINT_DEFAULT - An ENUM that contains Constraint to any function.
enum CODE_CONSTRAINT_DEFAULT
{
    LIMIT_ARGV_COUNTER = 5
};

namespace TTRM
{

/*
 TTRM_SystemFunc is a derived class that utilizes System-Proposed Functions. THis means that all functions residing
 in this class is basically related to the Proposed System that we wanted to make.
*/

class TTRM_SystemFunc
{
protected:
private:
public:
    // Constructors
    TTRM_SystemFunc(unsigned short DEBUG_MODE);

    //Processing Functions

    //Deconstructor
    ~TTRM_SystemFunc();
};

/*
    TTRM_TechFunc is a derived class that contains only technical functions that utilizes
    debugging, non-related proposed system functions such as printing some data, readjustment 
    of Console Window and more. This class contains Win32API User-Defined Functions, WinToast API for Windows 10
    Notifications and lastly MySQL Library. Keep in mind that this is the place where external libraries added on this class.
*/
class TTRM_TechFunc : public IWinToastHandler
{
public:
    inline void ParseGivenParam(unsigned short argcount, std::string argcmd[]);
    virtual void toastActivated() const = 0;
    virtual void toastActivated(int actionIndex) const = 0;
    virtual void toastDismissed(WinToastDismissalReason state) const = 0;
    virtual void toastFailed() const = 0;


private:
protected:
};

class TTRM_ClassInitializer : public TTRM_SystemFunc, public TTRM_TechFunc
{
private:
public:
    virtual void toastActivated() const;
    virtual void toastActivated(int actionIndex) const;
    virtual void toastDismissed(WinToastDismissalReason state) const;
    virtual void toastFailed() const;
protected:
};

/*
class WinToastHandler_TTRM : public IWinToastHandler    
{
public:
    void toastActivated(void) const
    {
        std::wcout << L"The user clicked in this toast" << std::endl;
        exit(0);
    }

    void toastActivated(int actionIndex) const
    {
        std::wcout << L"The user clicked on action #" << actionIndex << std::endl;
        exit(16 + actionIndex);
    }

    void toastDismissed(WinToastDismissalReason state) const
    {
        switch (state)
        {
        case UserCanceled:
            std::wcout << L"The user dismissed this toast" << std::endl;
            exit(1);
            break;
        case TimedOut:
            std::wcout << L"The toast has timed out" << std::endl;
            exit(2);
            break;
        case ApplicationHidden:
            std::wcout << L"The application hid the toast using ToastNotifier.hide()" << std::endl;
            exit(3);
            break;
        default:
            std::wcout << L"Toast not activated" << std::endl;
            exit(4);
            break;
        }
    }

    void toastFailed() const
    {
        std::wcout << L"Error showing current toast" << std::endl;
        exit(5);
    }
};
*/
} // namespace TTRM
#endif