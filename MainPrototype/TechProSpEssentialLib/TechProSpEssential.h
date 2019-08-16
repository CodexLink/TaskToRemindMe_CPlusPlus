// Technical Project Specific Essential Function Header File by Janrey "CodexLink" Licas

#ifndef TechProSpEssential_H
#define TechProSpEssential_H // We define this marker for indication of "already initialized"

#include <iostream>
#include <string>
#include "WinToastLib/wintoastlib.h"
#include <windows.h> // For Win32 API, We manipulate our console here.
#include "SQLite3/sqlite3.h"

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


// CODE_CONSTRAINT_DEFAULT - An ENUM that contains Constraint to any function.
enum CODE_CONSTRAINT_DEFAULT
{
    LIMIT_ARGV_COUNTER = 5,
    MAX_TASK_EXISTING = 255 // Used for limiting possible task to enter.
};

/* CODE_RET_PROCESS
	Contents: Function Returning Values for Processing Functions
	Reason for ENUM to #define: 
*/
#ifndef CODE_RET_PROCESS
	#define CODE_RET_PROCESS
	#define RETURN_NULL  0
#endif

/* CODE_CONSTANTS is using Define not ENUM.
	Technical Reason: Not Usable as an Incrementable Reference.
*/
#ifndef CODE_CONSTANTS
    #define CODE_CONSTANTS
    #define INIT_NULL 0
    #define POS_OFFSET_BY_ONE 1
#endif


/*
 TTRM_SystemFunc is a derived class that utilizes System-Proposed Functions. THis means that all functions residing
 in this class is basically related to the Proposed System that we wanted to make.
*/

class TTRM_SystemFunc
{
public:
    TTRM_SystemFunc(void) {}
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
    TTRM_TechFunc(void) {}

    virtual void ParseGivenParam(unsigned short argcount, char* argcmd[]) = 0;
    virtual void toastActivated() const = 0;
    virtual void toastActivated(int actionIndex) const = 0;
    virtual void toastDismissed(WinToastDismissalReason state) const = 0;
    virtual void toastFailed() const = 0;
};

class TTRM_ClassInitializer : public TTRM_SystemFunc, public TTRM_TechFunc
{
public:
    TTRM_ClassInitializer(void) {}

    virtual void ParseGivenParam(unsigned short argcount, char* argcmd[]);
    virtual void toastActivated() const;
    virtual void toastActivated(int actionIndex) const;
    virtual void toastDismissed(WinToastDismissalReason state) const;
    virtual void toastFailed() const;
};
#endif