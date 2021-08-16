/*
	# Task To Remind Me Core Declarations | TTRM_CoreDecl.cpp
    # File Category Type: Core Function Declaration
	# Version: Version Post.06042020.1955

	# Created by Janrey Licas | http://github.com/CodexLink
	! Licensed in GPL-3.0
*/

#pragma once

#pragma warning(disable : 4996) // ! _CRT_SECURE_NO_WARNINGS | Regarding 'This' Pragma. The reason of declaring this one is because of an issue about arguments that can be passed both on localtime_s and mktime. localtime_s needs a struct tm while mktime needs a struct *tm. This issue was caused on code issue where allocation happens and possible memory leak might be the result which is a bad idea.
#pragma warning(disable : 6031) // ! Disable _Getche Return Value Ignored.

// ! Input, Output, Strings Handler, File Handler Declarations
#include <conio.h>	// * For _getche Function, Stopper Function, System("pause") Equivalent.
#include <fstream>	// * For File Streaming In Any Given Format Readable Text.
#include <iostream> // * For STDIN, STDOUT And Other Equivalents.
#include <iomanip>	// * For String Display Decorator By SetFill and SetWidth.
#include <limits>	// * Defined Constraints For Data Type Particulars.
#include <string>	// * For STD::STRING, Other Equivalents and STL.
#include <sstream>	// * String Handler

// ! Container Source Declarations
#include <deque>  // * Special Case of Queue Combined with Queue and Vector
#include <vector> // * File Streaming Temporary Diced String Holder

// ! Process-Threading Declarations
#include <chrono>
#include <ctime>
#include <process.h>
#include <thread>
#include <windows.h> // * For Win32 API Console Manipulation Such as Cursor Coordinate Setter and Color Foreground and Background.

// ! Custome Library Declaration
#include "WinToastLib/wintoastlib.h"

// ! Namespace Declaration
using namespace WinToastLib;

#undef max // # Visual Studio Overriding Function To Be Undefined.

class TTRM
{
private:
	// # ASCII Equivalents Declarations (in HEX Form To Keep C4309 Warning from Visual Studio 2019 	)
	enum ASCII_CHARS : char
	{
		ASCII_VLDivider = 0xDD, // * Vertical Left
		ASCII_VRDivider = 0xDE, // * Vertical Right
		ASCII_HDivider = 0xCD,	// * Horizontal Line Render
		ASCII_FullBlock = 0xDB, // * Big Block
	};

	// # Console Positioning and Other Such-Related Declarations
	// @promise | POTENTIAL DEPRECATION.
	enum CONSOLE_INIT_POS : char
	{
		START_POSX = 5,
		START_POSY = 5

	};

	// # DISPLAY_OPTIONS, Used for Switch-Case Situations.
	enum DISPLAY_OPTIONS : char
	{
		Termination,
		AddTask,
		DeleteTask,
		EditTask,
		ViewTask,
		RemoveAllTask,
		RefreshTaskList,
		RefreshMenu,
		AtHome
	};

	// # ON_LOOP, Make Magic Number has Significance with Intentions.
	enum ON_LOOP
	{
		CONTINOUS_ON_PROC = 1,
	};

	// # Randomizer Constraint Declarations
	enum RANDOMIZER_CONSTRAINTS : char
	{
		MAXID_LENGTH = 6,
		MODULO_VAL = 70,
	};

	// # RETURN_STATES. Used for Clarifying State
	enum RETURN_STATES : unsigned char
	{
		RETURN_NULL,		  // # Returns 0. | Indicating Nothing to Return, Literally.
		TERM_SUCCESS,		  // # Returns 1. | Indicating Termination Success.
		TERM_FAILED,		  // # Returns 2. | Indicating Termination Success But Some Operation Failed.
		EXEC_INVALID_PARAM,	  // # Returns 3. | Indicating Execution Error Due to Invalid Parameters.
		THREAD_OOS,			  // # Returns 4. | Indicating Thread Goes Out of Scope.
		FUNC_OOS,			  // # Returns 5. | Indicating Function Goes Out of Scope. | Equivalent to Returning Nothing But Return Non-Zero Instead. | Usable for Return True to run other functions.
		THREAD_NOTASK_REPEAT, // # Returns 6. | Indicating Thread Goes Out of Scope Due To No Task Is Being Processed.
		THREAD_PRC_TERM,	  // # Returns 7. | Indicating Thread Goes Out Of Scope Due and Thread is Terminated Unexpectedly. | Such as Crash from File Corruption.
	};

	// # REMINDER_TYPES, Types of Actions, Basically.
	enum REMINDER_ACTIONS : char
	{
		IgnoreReminder,
		SnoozeReminder,
		DiscardReminder,
	};
	// # REMINDER_TYPES, Types of Reminder, Basically.
	enum REMINDER_TYPES : char
	{
		CancelOperation,
		QuickRemind,
		DateBasedRemind,
	};

	// ! SET_CHOICE_PROCESS, Added Both Possibility Writes by User
	enum SET_CHOICE_PROCESS : char
	{
		T_LC = 'y',
		T_UC = 'Y',
		F_LC = 'n',
		F_UC = 'N'
	};

	// # Sleep Timer Declarations
	enum SLEEP_STATE : unsigned short
	{
		DISPLAY_WINDOW = 1600,
		OPRT_FINISHED = 1800,
		INIT_OBJECT = 1900,
		INIT_SETUP = 2200,
		ERROR_PROMPT = 2400,
		OPRT_FAILED = 2500,
		SIGNIFICANT_ERR = 3000,
		GEN_TERM = 3000,
		SYS_TERM = 3500
	};

	// # TTRM Task Data Constraint Declarations
	enum TASK_CONSTRAINTS : char
	{
		CHAR_MIN_TASKNAME = 2,
		CHAR_MIN_INCHARGE = 2,
		QUICK_MIN_TIME = 0,
		QUICK_MAX_TIME = 180,
		QUICK_INV_MAX_TIME = -45,
		DISPLAY_LIMIT = 5,
		TASK_PUSHABLE_COUNT = 512, // ! Find A Way To Use This One | Potential Deprecation?
		VECTOR_TEMP_SIZE = 4	   // * File Stream, Number of Columns To Parse
	};

	// # Time Threading Constraint Declarations
	enum THREAD_CONSTRAINTS : unsigned short
	{
		SNOOZE_TIME = 10,
		WAIT_STARTTHREAD = 1000,

	};

	// # TIME (TM) Constraint Declarations
	enum TM_STD : unsigned char
	{
		MIN_HOUR = 0,
		MIN_MIN = 0,
		MIN_DAY = 1,
		MIN_MONTH = 1,
		MAX_HOUR = 23,
		MAX_MIN = 59,
		MAX_DAY = 31,
		MAX_MONTH = 12,
		START_CTIME = 1900 // * Year Starting Point. Used To Minus or Plus To Avoid MKTime Returning -1.
	};

	// # Non Magic Variable | For Use by Constructor.
	bool __DEBUG_ENABLE, __USE_MYSQL;

	// # Try Reinterpret_Cast when needed for String Version???
	const static struct METADATA
	{
		std::wstring WLONG_NAME = L"Tasks To Remind Me C++ CLI",
					 WSHORT_NAME = L"TTRM for C++",
					 WCURR_VERSION = L"Version Initial.06042020.1955",
					 WCREATOR_NAME = L"By CodexLink",
					 WREPO_LINK = L"https://github.com/CodexLink/TaskToRemindMe_CPlusPlus";

		std::string LONG_NAME = "Tasks To Remind Me C++ CLI",
					SHORT_NAME = "TTRM for C++",
					CURR_VERSION = "Version Initial.06042020.1955",
					CREATOR_NAME = "By CodexLink",
					REPO_LINK = "https://github.com/CodexLink/TaskToRemindMe_CPlusPlus";
	} PROJECT_METADATA;

	static struct TASK_DATA
	{
		std::string TaskID = NULL_STR,				 // * Unique Task ID Generated by Gen_UniqueRID
			TaskName = NULL_STR,					 // * Task Name
			TaskInCharge = NULL_STR;				 // * Name of the Person Incharge.
		unsigned short ReminderType = INIT_BASE_NUM; // * Used To Distinguish Type of Reminder.
		time_t NotifyByTime = INIT_BASE_NUM;		 // * Used by QuickRemind Type Reminder.
		tm *TempTM = {0};							 // * Temporary Use for Localtime and Data Passing to ReminderData.
		tm ReminderData = {0};						 // * Actual Storage of the Reminders.
	} TASK_DATALIST;

	// # Side Component | Function ID Generator for Reminders, Used for Both Types of Reminders.
	std::string GenerateUID() noexcept(true);

	// # Task / Menu Displays Function Declarations
	std::string SP_DisplayTasksParser(REMINDER_TYPES IntType) noexcept(true);
	void SP_DisplayTasks(DISPLAY_OPTIONS WindowID_INT);

	std::string SP_DLT() const; // * Displays Local Time of the System
	char SP_DisplayMenu();
	void DC_ATask();  // * Adds Task To The System, Both Applies to Save State and Queue System
	void DC_DTask();  // * Deletes Task To The System, Both Applies to Save State and Queue System
	void DC_ETask();  // * Modifies Task To The System, Both Applies to Save State and Queue System
	void DC_VTask();  // * Views Task To The System, # of Reminders Limitations is Not Applied, This Checks Only On Queue System
	void DC_RQT();	  //  *Removes Queued Tasks and Removes Save State Data
	void DC_RTLFSS(); // * Refresh TaskList From Save States

	// # Utility Inlined Functions
	inline void DelayRunTimeBy(unsigned short MillSec);
	inline void BufferClear_STDIN();

public:
	// # Magic Number To Significance from Initializers to Comparison Base Value Declarations
	static constexpr char INIT_BASE_NUM = 0, // * Significance for Base Positive Number is Zero.
		START_BY_ONE = 1,					 // * Significance for Base Starting Point is One.
		NULL_CHAR = '0',					 // * Significance for CHAR Initialization at Starting Point of NULL.
		ADJUST_BY_ONE = 1,					 // * Significance for Adjusting Particular Variable by One. Decrement Or Increment, Neither Of The Two. Or By Checking Index with Offset of One.
		CONTAINS_ONE_ELEM = 1,				 // * Significance for IF 'THAT' Contains Only One Element OR Less.
		LIMIT_ARGC_COUNTER = 5;				 // * Significance for Max Number of Processing Arguments

	static constexpr char *NULL_STR = ""; // * Significance for String Initialization at Starting Point of NULL.

	// # Multithreading and Console Global Variables \ ! Potential Reconfiguration.
	unsigned short WT_RET_VALUE;
	unsigned MTID_Handler = INIT_BASE_NUM; // ! Multi-Threading ID Handler, Can Possibly Anything.
	HANDLE MultiThreadHandler = NULL;	   // * Special Variable for Checking Status of Thread, Used for WaitForSingleObject
	HANDLE ConsoleHandler = NULL;		   // * Special Variable for Handling Current Console Process To Modify View and Other Such.
	COORD ConsolePosInfo = {INIT_BASE_NUM, INIT_BASE_NUM};

	// ! File Stream Implementation
	/*
		* TempDataHandler, String Storage to StringStream
		* ConvertedHandler, Diced Data to PayloadHandler
		* DataLineHandler, Whole Data Row from TempDataHandler
		* PayloadHandler, Diced Data Storage
		* SaveStateHandler, Handler for Save State File
		* TempSaveStateHandler, Handler for Temporary File
	*/
	std::string TempDataHandler = NULL_STR, ConvertedHandler = NULL_STR, DataLineHandler = NULL_STR;
	std::vector<std::string> PayloadHandler;
	std::fstream SaveStateHandler;
	std::fstream TempSaveStateHandler;

	// ! Randomizer Required String
	const std::string AlphaNumConst = "0123456789!@#$%^&*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	const char *SaveStatePath = "TTRM_SaveState._ttrmdat";		 // Unconfirmed
	const char *FilePointState = "TTRM_SaveStatesTemp._ttrmdat"; // Unconfirmed

	// # Class Constructor Declaration
	TTRM(bool OUTPUT_DEBUG = false, bool USE_MYSQL = true) : __DEBUG_ENABLE(OUTPUT_DEBUG), __USE_MYSQL(USE_MYSQL)
	{
		std::cout << std::endl
				  << std::endl
				  << "\t" << PROJECT_METADATA.LONG_NAME << " | " << PROJECT_METADATA.CURR_VERSION << std::endl
				  << "\tCreated by " << PROJECT_METADATA.CREATOR_NAME << std::endl
				  << std::endl
				  << "\tGroup Members at CPE21FB1 Data Structure Group 5\n\t\tProject Lead: 'Janrey Licas',\n\t\tSystem Director: 'Rejay Mar Senar'";
		DelayRunTimeBy(SLEEP_STATE::INIT_OBJECT);
	}

	// # Class Destructor Declaration
	~TTRM(void)
	{
		WinToast::instance()->clear(); // ! Ensure WinToast Will Terminate Upon Program Close.
		CloseHandle(MultiThreadHandler);
	}

	// # Multi Threading Static Functions
	static unsigned __stdcall MultiThread_Wrapper(void *);
	static unsigned __stdcall MultiThread_ScanReminders(void *);

	// ! TTRM_WinToast Relative Functions. Not Declared to TTRM_WinToast due to Function Structure of the whole class.
	static void WinToast_ReminderPrompt(std::string ReadName, std::string ReadInCharge, unsigned short ReadReminderType, time_t ReadNotifyByTime, tm TMToRead) noexcept;

	// # Returns bool to check if we have properly processed everything that is passed. If failed, terminate or ignore.
	bool ParseGivenParam(unsigned short argcount, char *argcmd[]);
	unsigned short Cmpnt_Initializer();

	// ! ASCII and Console Decorators Declarations
	void SetConsoleCurPos(short SP_X, short SP_Y);
	void PrintConsoleASCII(const char *CharToIter, unsigned short IterValue);
};

/*
	* TTRM_WinToast is a base class seperated to use WinToast Class 'IWinToastHandler'
	* We seperated this for a reason. The reason why is because according to the template or the
	* same code, we have to call 'this' (TTRM_WinToast) class everytime we are gonna display some toast.
	* IF we didn't seperate this class from one another, we cannot initiate it.
*/

class TTRM_WinToast : public IWinToastHandler
{
public:
	~TTRM_WinToast(void)
	{
		WinToast::instance()->clear();
	} // ! Destroys Toast After Execution To Reduce Memory Leak / Consumption.

	// * Virtual Function Overriders. Handles Particular Thing...
	void toastActivated(void) const;
	void toastActivated(int actionIndex) const;
	void toastDismissed(WinToastDismissalReason state) const;
	void toastFailed(void) const;
};

/*
	# Task To Remind Me Core Declarations | TTRM_CoreDecl.cpp
    # File Category Type: Core Function Declaration
	# Version: Version Post.06042020.1955

	# Created by Janrey Licas | http://github.com/CodexLink
	! Licensed in GPL-3.0 | See LICENSE.md for more information.
*/