/*
    Technical Project Specific Essential Function Header File by Janrey "CodexLink" Licas
    File Category Type: Core Function Definitions, "CoreDef".
*/

/*
Things To Know #1 - Virtual Functions
	is a function that can be overrided by another class by redeclaring this to a derived class.
	HOW: First we declare the function in base class with equal to 0. Then redefine to a derived class that you want
	a class to use for in the whole procedural.

Things To Know #2 - ENUMs,
	A Group or contains that specific values that classifies specialized for returning
	reference values. For example, we need a group of reference values for returning error codes.
	Hence, this example is refernced to our first ENUM called TERM_RET_ERROR
*/

#ifndef TechProSpEssential_TTRM_H
#define TechProSpEssential_TTRM_H // We define this marker for indication of "already initialized"

#include <iostream>
#include <conio.h>
#include <string>
#include <deque>
#include <stack>
#include <windows.h> // For Win32 API, We manipulate our console here.
#include "WinToastLib/wintoastlib.h"
#include "SQLite3/sqlite3.h"
//#include <conio.h> // For Character Standard Input (STDIN) Capture for Switch-Case Statement
#include <chrono>
#include <thread>
#include <limits>
#include <sstream>
#include <ctime>

// #define Function-Like Declaration and Constant Uncategorized Definitions
#define PROJECT_NAME L"Task To Remind Me | C++"
#define PROJECT_VER L"Early Testing Case"
#define NDEBUG
#define delay_time(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))
#define WinCall_CMD(x) system(x);
#define CinBuffer_ClearOptpt(__CharIgnore_Start) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), __CharIgnore_Start);
using namespace WinToastLib;

#undef max // Visual Studio Overriding Function To Be Undefined.
// TERM_RET_ERROR - An ENUM that contains Termination Return Error. Useful for Deconstructor Error Display
enum TERM_RET_ERROR : unsigned short
{
	TERM_INVALID_PARAM = 2,
	TERM_FAILED = 1,
	TERM_SUCCESS = 0
};

enum REMINDER_TYPES
{
	RemindContinous = 0,
	RemindTimeBased = 1
};
enum SET_CHOICE_PROCESS : char
{
	CONFIRMED_TRUE_LOWER = 'y',
	CONFIRMED_TRUE_UPPER = 'Y',
	CONFIRMED_FALSE_LOWER = 'n',
	CONFIRMED_FALSE_UPPER = 'N'

};
enum TERM_CONSOLE_LOG_PRESET
{

};
// CODE_CONSTRAINT_DEFAULT - An ENUM that contains Constraint to any function.
enum CODE_CONSTRAINT_DEFAULT
{
	LIMIT_ARGC_COUNTER = 5,
	MAX_TASK_EXISTING = 255 // Used for limiting possible task to enter.
};

enum DISPLAY_OPTIONS
{
	Termination,
	AddTask,
	DeleteTask,
	EditTask,
	ViewTask,
	SortQueuedTask,
	RemoveQueuedTask,
	SortDatabaseTask,
	RemoveDatabaseTask,
	RefreshContainerTask,
	ComponentStatus,
	MinimizeRunningInst,
	AtHome
};

enum SLEEP_TIMERS
{
	SLEEP_INIT_SETUP = 2000,
	SLEEP_DISPLAY_WINDOW = 1500,
	SLEEP_INIT_OBJECT = 2000,
	SLEEP_TERM = 3000,
	SLEEP_ERROR_PROMPT = 1850,
	SLEEP_SIGNIFICANT_ERR = 3000,
	SLEEP_OPRT_FAILED = 2500,
	SLEEP_OPRT_FINISHED = 1500
};
/* CODE_RET_PROCESS
	Contents: Function Returning Values for Processing Functions
	Reason for ENUM to #define: 
*/
#ifndef CODE_RET_PROCESS
#define CODE_RET_PROCESS
#define RETURN_NULL 0
#define USER_OUTOFSCOPE_TERM_SUCCESS 0
#endif

/* CODE_CONSTANTS is using Define not ENUM.
	Technical Reason: Not Usable as an Incrementable Reference.
*/
#ifndef CODE_CONSTANTS
#define CODE_CONSTANTS
#define INIT_NULL_INT 0
#define INIT_BY_LITERAL_ONE 1
#define INIT_NULL_STR ""
#define INIT_NULL_CHAR '0'
#define POS_OFFSET_BY_ONE 1
#define BY_ONE_OR_LESS 1

// Superposition Method, Parameters used for when we want to run this function content or not. Used for Selected Technical  Functions only.
#define IGNORE_PROCESS 0
#define RUN_PROCESS 1
#define NOT_REQ_TERM 1
#define PROCESS_AWAIT_CMPLT 1 // Awaiting Completion
#endif

// SYS_CONSTRAINTS is a set of definition for parameter constraints designed for stopping operation when user execeeded to one of the range definitions declared below.
#ifndef SYS_CONSTRAINTS
#define SYS_CONSTRAINTS
#define MIN_CHAR_TASKNAME 2
#define MIN_CHAR_INCHARGE 2
#define MIN_TIME_DAY 1
#define MAX_TIME_DAY 31
#define MIN_TIME_MONTH 1
#define MAX_TIME_MONTH 12
#define MIN_TIME_HOUR 00
#define MAX_TIME_HOUR 23
#define MIN_TIME_MIN 0
#define MAX_TIME_MIN 59
#define MIN_EARLYTIME 0
#define MAX_EARLYTIME 180

#define TASK_DISPLAY_LIMIT 5
#define TASK_DISPLAY_CRUD 10
#define MAX_TASK_ATTACH 255
#define MAX_TASK_DATABASE 255
#define START_CTIME 1900
#define MAX_SIZE ...
#endif
/*
	TTRM_CoreFunc is a base class that contains only functions that is mainly focused on the system itself.
	It doesn't include any external libraries function but only includes for display menus, etc.
*/
class TTRM_CoreFunc
{
public:
	TTRM_CoreFunc(void)
	{
		std::cout << "[OBJECT] TTRM Core Function Initialized." << std::endl << std::endl;
	}
	// Variable for Storing Status Indicators of an Components
	typedef enum
	{
		WinToastID = 10,
		AutoStartID = 11,
		SQLiteID = 12
	} ComponentID; // This enum is only used for identifying Components To Check.
	virtual void runSystemMenu() noexcept(false) = 0;
	virtual void DisplayTasks_AtWindow(DISPLAY_OPTIONS WindowID_INT) noexcept = 0;
	// TTRM_WinToast Relative Functions. Not Decalred to TTRM_WinToast due to Function Structure of the whole class.
	virtual std::string runSystem_GetTimeLocal() const noexcept = 0;
	virtual void WinToast_RemindTask() noexcept = 0;
	virtual void WinToast_ShowTaskCForToday() noexcept = 0;
	virtual void WinToast_ShowReminder() noexcept = 0;
	// Status Indicators
	virtual std::string ComponentStats_Indicator(ComponentID CompToCheck) noexcept = 0;
	// runSystemMenu Sub Functions
	// Basic Task Functions
	virtual void MenuSel_ATask() noexcept(false) = 0;
	virtual void MenuSel_DTask() noexcept = 0;
	virtual void MenuSel_ETask() noexcept(false) = 0;
	virtual void MenuSel_VTask() noexcept(false) = 0;
	// Advanced Task Functions
	virtual void MenuSel_SQT() noexcept(false) = 0; // SortQueuedTask
	virtual void MenuSel_RQT() noexcept(false) = 0; // RemoveQueuedTask
	virtual void MenuSel_SDT() noexcept(false) = 0; // SortDatabaseTask
	virtual void MenuSel_RDT() noexcept(false) = 0; // RemoveDatabaseTask
	virtual void MenuSel_RCT() noexcept(false) = 0; // RefreshContainerTask
	virtual void MenuSel_CS() const noexcept(false) = 0; // ComponentStatus
	virtual void MenuSel_MRI() const noexcept(false) = 0; // MinimizeRunningInst
};

/*
	TTRM_TechFunc is a base class that contains only technical functions that utilizes
	debugging, non-related proposed system functions such as printing some data, readjustment
	of Console Window and more. This class contains Win32API User-Defined Functions, WinToast API for Windows 10
	Notifications and lastly MySQL Library. Keep in mind that this is the place where external libraries added on this class.
*/
class TTRM_TechFunc
{
public:
	enum SQLite_QueryType
	{
		AddData,
		EditData, // Equivalent to Update
		DeleteData
	};

	TTRM_TechFunc(void)
	{
		std::cout << "Task To Remind Me C++ in CLI version. BETA" << std::endl
				  << std::endl
				  << "Created by Data Structure Group 5, Group Members {Header Core Developer: 'Janrey Licas',\n AppFlow Director: 'Rejay Mar'};" << std::endl
				  << std::endl;
	}
	// Literal Technical Functions Declaration
	virtual void ParseGivenParam(unsigned short argcount, char *argcmd[]) = 0;
	virtual unsigned short ComponentCheck(bool isNeededToRun) noexcept(false) = 0;

	// Database SQLite3 Functions and Declarations
	virtual void SQLite_Initialize() const noexcept(false) = 0; // CreateTable Must Be Here
	virtual void SQLite_CheckDatabase() const noexcept(false) = 0;
	virtual void SQLite_ReloadQueue() const noexcept(false) = 0;
	virtual void SQLite_CRUD_Data(SQLite_QueryType ExecutionQueryType) const noexcept(false) = 0;

protected:
	const std::string DB_Path = "SQL_DataTest.db"; // Unconfirmed
};

/*
    TTRM is derived class that initializes multiple (two or more) (base / another derived) class
    that can be intialized in a single form factor. This means I want to use all of them by referencing only one class. 
*/
class TTRM : public TTRM_TechFunc, public TTRM_CoreFunc
{
	/*
		This class class contain variables, objects structors and functions (virtuals).
		So here's na overview.
		- Constructors
		- Variables
		- Structs
		- Enums
		- Functions
	*/
public:
	TTRM(void)
	{
		std::cout << "[OBJECT] TTRM Derived Main Class has been successfully initialized." << std::endl;
		delay_time(SLEEP_INIT_OBJECT);
	}
	~TTRM(void)
	{
		std::cout << "Termination |> Closing Objects and Database before closing the program." << std::endl;
		std::cout << "Termination |> All Modules Is Closed. Program Terminates!" << std::endl;
		delay_time(SLEEP_INIT_OBJECT);
		exit(USER_OUTOFSCOPE_TERM_SUCCESS);
	}

	// TTRM's CoreFunc Functions
	virtual void ParseGivenParam(unsigned short argcount, char *argcmd[]) override;
	virtual unsigned short ComponentCheck(bool isNeededToRun) noexcept(false) override;

	virtual void runSystemMenu() noexcept(false) override;
	virtual void DisplayTasks_AtWindow(DISPLAY_OPTIONS WindowID_INT) noexcept override;

	// TTRM_WinToast Relative Functions. Not Decalred to TTRM_WinToast due to Function Structure of the whole class.

	virtual void WinToast_RemindTask() noexcept override;
	virtual void WinToast_ShowTaskCForToday() noexcept override;
	virtual void WinToast_ShowReminder() noexcept override;
	virtual std::string runSystem_GetTimeLocal() const noexcept override;
	// Status Indicator Checkers
	virtual std::string ComponentStats_Indicator(ComponentID CompToCheck) noexcept override;
	virtual void MenuSel_ATask() noexcept(false) override;
	virtual void MenuSel_DTask() noexcept override;
	virtual void MenuSel_ETask() noexcept(false) override;
	virtual void MenuSel_VTask() noexcept(false) override;
	virtual void MenuSel_SQT() noexcept(false) override; // SortQueuedTask
	virtual void MenuSel_RQT() noexcept(false) override; // RemoveQueuedTask
	virtual void MenuSel_SDT() noexcept(false) override; // SortDatabaseTask
	virtual void MenuSel_RDT() noexcept(false) override; // RemoveDatabaseTask
	virtual void MenuSel_RCT() noexcept(false) override; // RefreshContainerTask
	virtual void MenuSel_CS() const noexcept(false) override; // ComponentStatus
	virtual void MenuSel_MRI() const noexcept(false) override; // MinimizeRunningInst
	// TTRM's TechFunc Functions
	virtual void SQLite_Initialize() const noexcept(false) override; // CreateTable Must Be Here
	virtual void SQLite_CheckDatabase() const noexcept(false) override;
	virtual void SQLite_ReloadQueue() const noexcept(false) override;
	virtual void SQLite_CRUD_Data(SQLite_QueryType ExecutionQueryType) const noexcept(false) override;
	// These variables will be globally use by functions to reduce variable initialization by candidating only few ones from the class state.
	unsigned short TASK_LIMIT_SIZE = TASK_DISPLAY_LIMIT; // By Default, 5. 
	char handleInputChar = INIT_NULL_CHAR;
	unsigned short handleInputInt = INIT_NULL_INT;
};

/*
	TTRM_WinToast is a base class specifically seperated to use WinToast Class 'IWinToastHandler'
	We seperated this for a reason. The reason why is because according to the template or the 
	same code, we have to call 'this' (TTRM_WinToast) class everytime we are gonna display some toast.
	IF we didn't seperate this class from one another, we cannot initiate it.
*/
class TTRM_WinToast : public IWinToastHandler
{
public:
	TTRM_WinToast(void) {}
	~TTRM_WinToast(void)
	{
		WinToast::instance()->clear();
	}
	void toastActivated() const override
	{
		;
		//	std::wcout << L"The user clicked in this toast" << std::endl;
		//	exit(0);
	}
	void toastActivated(int actionIndex) const override
	{
		;
		//	std::wcout << L"The user clicked on action #" << actionIndex << //std::endl;
		//	exit(16 + actionIndex);
	}
	void toastDismissed(WinToastDismissalReason state) const override
	{
		switch (state)
		{
		case UserCanceled:
			//		std::wcout << L"The user dismissed this toast" << std::endl;
			//		exit(1);
			break;
			//	case TimedOut:
			//		std::wcout << L"The toast has timed out" << std::endl;
			//		exit(2);
			//		break;
		case ApplicationHidden:
			//		std::wcout << L"The application hid the toast using //ToastNotifier.hide()" << std::endl;
			//		exit(3);
			break;
		default:
			//		std::wcout << L"Toast not activated" << std::endl;
			//		exit(4);
			break;
		}
	}
	void toastFailed() const override
	{
		;
		//	std::wcout << L"Error showing current toast" << std::endl;
		//	exit(5);
	}
};

/*
 TTRM_TaskData is an important base class that utilizes System-Proposed Functions specificially used for scheduler. This means that all functions residing
 in this class is basically related to the Proposed System that we wanted to make. This base class was not on a confirmed status. Please be advised.
*/
class TTRM_TaskData
{

public:
	std::string TaskName = INIT_NULL_STR;
	std::string TaskInCharge = INIT_NULL_STR;
	unsigned short ReminderType = INIT_NULL_INT;
	tm DateStartTime; // Use YYYY-MM-DD, Does Not Use Time
	tm DateEndTime;   // Use YYYY-MM-DD, Does Not Use Time
	tm TimeTrigger;
	unsigned short NotifierOffset = INIT_NULL_INT; // Id NOT Required...

	//std::queue<> DB_DisplayList; // Used unsigned int just to reference a specific specific number id.
};
#endif