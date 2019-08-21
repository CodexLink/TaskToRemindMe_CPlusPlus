/*
    Technical Project Specific Essential Function Header File by Janrey "CodexLink" Licas
    File Category Type: Core Function Definitions, "CoreDef".
*/
#ifndef TechProSpEssential_H
#define TechProSpEssential_H // We define this marker for indication of "already initialized"

#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <windows.h> // For Win32 API, We manipulate our console here.
#include "WinToastLib/wintoastlib.h"
#include "SQLite3/sqlite3.h"
#include <conio.h> // For Character Standard Input (STDIN) Capture for Switch-Case Statement
#include <chrono>
#include <thread>


// #define Function-Like Declaration
#define delay_time(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));

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
    LIMIT_ARGC_COUNTER = 5,
    MAX_TASK_EXISTING = 255 // Used for limiting possible task to enter.
};

enum DISPLAY_OPTIONS 
{
	AddTask,
	DeleteTask,
	EditTask,
	ViewTask,
	SortTask,
	AutoStartup,
	WinToastIntegration,
	Termination
};

enum SLEEP_TIMERS
{
	SLEEP_INIT_SETUP = 2000,
	SLEEP_DISPLAY_WINDOW = 1500,
	SLEEP_INIT_OBJECT = 2000,
	SLEEP_TERM = 3000
};
/* CODE_RET_PROCESS
	Contents: Function Returning Values for Processing Functions
	Reason for ENUM to #define: 
*/
#ifndef CODE_RET_PROCESS
#define CODE_RET_PROCESS
#define RETURN_NULL 0
#define RETURN_BACK_NOTHING 0
#endif

/* CODE_CONSTANTS is using Define not ENUM.
	Technical Reason: Not Usable as an Incrementable Reference.
*/
#ifndef CODE_CONSTANTS
#define CODE_CONSTANTS
#define INIT_NULL 0
#define POS_OFFSET_BY_ONE 1
// Superposition Method, Parameters used for when we want to run this function content or not. Used for Selected Technical  Functions only.
#define IGNORE_PROCESS 0
#define RUN_PROCESS 1
#define NOT_REQ_TERM 1
#define INIT_STR_NULL ""
#define INIT_CHAR_NULL '0'
#endif
/*
    TTRM_TechFunc is a derived class that contains only technical functions that utilizes
    debugging, non-related proposed system functions such as printing some data, readjustment 
    of Console Window and more. This class contains Win32API User-Defined Functions, WinToast API for Windows 10
    Notifications and lastly MySQL Library. Keep in mind that this is the place where external libraries added on this class.
*/


class TTRM_CoreFunc
{
public:
    TTRM_CoreFunc(void) 
	{
		std::cout << "[OBJECT] TTRM Core Function has been successfully initialized." << std::endl;
	}

    virtual bool DisplayMenu(void) const = 0;
private:
protected:
};


class TTRM_TechFunc : public IWinToastHandler
{
public:
	TTRM_TechFunc(void) 
	{
		std::cout << "Task To Remind Me C++ in CLI version. BETA" << std::endl << std::endl 
		<< "Created by Data Structure Group 5, Group Members {\n Header Core Developer: 'Janrey Licas',\n AppFlow Director: 'Rejay Mar'\n};" << std::endl << std::endl
		<< "[OBJECT] TTRM Technical Function with WinToastHandler has been successfully initialized." << std::endl;
	}

    virtual void ParseGivenParam(unsigned short argcount, char *argcmd[]) = 0;
    virtual bool ComponentCheck(bool isNeededToRun) = 0;

    /* Virtual Functions
        is a function that can be overrided by another class by redeclaring this to a derived class.
        HOW: First we declare the function in base class with equal to 0. Then redefine to a derived class that you want
        a class to use for in the whole procedural.
    */
    // Functions for WinToast Library
    virtual void toastActivated(void) const = 0;
    virtual void toastActivated(int actionIndex) const = 0;
    virtual void toastDismissed(WinToastDismissalReason state) const = 0;
    virtual void toastFailed(void) const = 0;
private:
protected:
};
/*
    TTRM is derived class that initializes multiple (two or more) (base / another derived) class
    that can be intialized in a single form factor. This means I want to use all of them by referencing only one class. 
*/

class TTRM : public TTRM_TechFunc, public TTRM_CoreFunc
{
public:
	TTRM(void)
	{
		std::cout << "[OBJECT] TTRM Derived Main Class has been successfully initialized." << std::endl << std::endl;
		delay_time(SLEEP_INIT_OBJECT);
		system("CLS");
	}
	~TTRM(void)
	{
		std::cout << std::endl << "[OBJECT] Object Class is at the End of Scopee. Goodbye!" << std::endl;
		delay_time(SLEEP_INIT_OBJECT);
		exit(TERM_SUCCESS);
	}

    // TTRM's TechFunc and CoreFunc Functions
    virtual void ParseGivenParam(unsigned short argcount, char *argcmd[]);
    virtual bool ComponentCheck(bool isNeededToRun);
    virtual bool DisplayMenu(void) const;
    // WinToast Library Functions
    virtual void toastActivated(void) const;
    virtual void toastActivated(int actionIndex) const;
    virtual void toastDismissed(WinToastDismissalReason state) const;
    virtual void toastFailed(void) const;
private:
protected:
};

/*
 TTRM_ScheduleList is an important base class that utilizes System-Proposed Functions specificially used for scheduler. This means that all functions residing
 in this class is basically related to the Proposed System that we wanted to make. This base class was not on a confirmed status. Please be advised.
*/
class TTRM_ScheduleList
{
public:
	TTRM_ScheduleList(void)
	{
		std::cout << "[TERMINATION] Closing Objects and Database before closing the program. (~using Deconstructors)" << std::endl
		<< "[OBJECT] TTRM_Scheduler has been successfully initialized." << std::endl;
	}
	~TTRM_ScheduleList(void)
	{
	}
    void Initialize_ScheduleList(void);
    void Display_ScheduleList(void);
private:
    const std::string DB_Path = ".db";       // Unconfirmed
    std::queue<unsigned int> DB_DisplayList; // Used unsigned int just to reference a specific specific number id.
};
#endif