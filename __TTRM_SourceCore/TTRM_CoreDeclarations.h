/*
	* Task To Temind Me Core Declarations
    * Side Note: Technical Project Specific Essential Function Header File
    * File Category Type: Core Function Definitions, "CoreDef".
	* Version: Close Beta Stage
	* 
	* Project Lead, Janrey "CodexLink" Licas
	* Project Director, Rejay "figureness" Mar
*/

// ! Declarations Start

// ! Pragma For Declaration and Exemptions
#pragma once
#pragma warning(disable : 4996) // !_CRT_SECURE_NO_WARNINGS | Regarding 'This' Pragma. The reason of declaring this one is because of an issue about arguments that can be passed both on localtime_s and mktime. localtime_s needs a struct tm while mktime needs a struct *tm. This issue was caused on code issue where allocation happens and possible memory leak might be the result which is a bad idea.

#ifndef TechProSpEssential_TTRM_H // ! Checks if we haven't initialized this header.
#define TechProSpEssential_TTRM_H // ! Set Indication that this header is NOW Initialized.

// ! Input, Output, Strings Handler, File Handler Declarations
#include <conio.h>  // * For _getche Function, Stopper Function, System("pause") Equivalent.
#include <fstream>  // * For File Streaming In Any Given Format Readable Text.
#include <iostream> // * For STDIN, STDOUT And Other Equivalents.
#include <iomanip>  // * For String Display Decorator By SetFill and SetWidth.
#include <string>   // * For STD::STRING, Other Equivalents and STL.
#include <sstream>  // * String Handler
#include <limits>   // * Defined Constraints For Data Type Particulars.

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

// ! Task To Remind Me Macro Definitions - START
#ifndef TTRM_DEFINITIONS
#define TTRM_DEFINITIONS

// ! String Literal Project Description Defined Macro Declarations
#define PROJECT_NAME L"Tasks To Remind Me C++ CLI"
#define PROJECT_SHORTCODE L"TTRM for C++"
#define PROJECT_VER L"Close Beta Stage"
#define PROJECT_CREATOR L"Data Structure Group 5"
#define PROJECT_LINK L"https://github.com/CodexLink/TaskToRemindMe_CPlusPlus"

// ! String Literals Version
#define PROJECT_NAME_STRL "Tasks To Remind Me C++ CLI"
#define PROJECT_SHORTCODE_STRL "TTRM for C++"
#define PROJECT_VER_STRL "Close Beta Stage"
#define PROJECT_CREATOR_STRL "Data Structure Group 5"
#define PROJECT_LINK_STRL "https://github.com/CodexLink/TaskToRemindMe_CPlusPlus"

// ! Short-Term Functions, Macro Definitions
#define DelayRunTimeBy(MillSec) std::this_thread::sleep_for(std::chrono::milliseconds(MillSec))
#define ConsoleCall(ConsoleCommand) system(ConsoleCommand)
#define BufferClear_STDIN(_CharDelimiter_) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), _CharDelimiter_);
#undef max // ! Visual Studio Overriding Function To Be Undefined.

// ! Return Value with Significance Declarations
#define RETURN_NULL 0
#define TERM_SUCCESS 1
#define TERM_FAILED -1
#define TERM_INVALID_PARAM -2
#define THREAD_OOS 0			// * Significance for Thread Goes Out of Scope, Normally.
#define FUNC_OOS 0				// * Significance for Function Goes Out of Scope, Normally.
#define THREAD_NOTASK_REPEAT -1 // * Significance for Thread Goes Out Due To No Task Is Being Processed.
#define THREAD_PRC_TERM -2		// * Significance for Thread Goes Out Of Scope Due To No Task Is Being Processed.

// ! Magic Number To Significance from Initializers to Comparison Base Value Declarations
#define INIT_BASE_NUM 0 // * Significance for Base Positive Number is Zero.
#define START_BY_ONE 1  // * Significance for Base Starting Point is One.
#define NULL_STR ""		// * Significance for String Initialization at Starting Point of NULL.
#define NULL_CHAR '0'   // * Significance for CHAR Initialization at Starting Point of NULL.
#define NULL_SET \
	{            \
		0        \
	}						 // * Significance for Setting Some Structure Members to Zero.
#define ADJUST_BY_ONE 1		 // * Significance for Adjusting Particular Variable by One. Decrement Or Increment, Neither Of The Two. Or By Checking Index with Offset of One.
#define CONTAINS_ONE_ELEM 1  // * Significance for IF 'THAT' Contains Only One Element OR Less.
#define CONTINOUS_RNN_PROC 1 // * Significance for Continous Running Process.
#define THREAD_AWAIT_CMPLT 1 // * Significance for Waiting Threading To Finish.
#define FUNC_AWAIT_CMPLT 1   // * Significance for Waiting Function To Finish.
#define LIMIT_ARGC_COUNTER 5 // * Significance for Max Number of Processing Arguments

// ! Sleep Timer Declarations
#define SLEEP_INIT_SETUP 2200
#define SLEEP_DISPLAY_WINDOW 1600
#define SLEEP_INIT_OBJECT 1900
#define SLEEP_TERM 3000
#define SLEEP_ERROR_PROMPT 2400
#define SLEEP_SIGNIFICANT_ERR 3000
#define SLEEP_OPRT_FAILED 2500
#define SLEEP_OPRT_FINISHED 1800

// ! TIME (TM) Constraint Declarations
#define MIN_TIME_MONTH 1
#define MAX_TIME_MONTH 12
#define MIN_TIME_DAY 1
#define MAX_TIME_DAY 31
#define MIN_TIME_HOUR 0
#define MAX_TIME_HOUR 23
#define MIN_TIME_MIN 0
#define MAX_TIME_MIN 59
#define START_CTIME 1900 // * Year Starting Point. Used To Minus or Plus To Avoid MKTime Returning -1.

// ! TTRM Task Data Constraint Declarations
#define CHAR_MIN_TASKNAME 2
#define CHAR_MIN_INCHARGE 2
#define QUICKR_MIN_TIME 0
#define QUICKR_MAX_TIME 180
#define QUICKR_INV_MAX_TIME -45
#define TASK_DISPLAY_LIMIT 5

// ! Time Threading Constraint Declarations
#define SNOOZE_TIME 10
#define WAIT_STARTTHREAD 1000

// ! Randomizer Constraint Declarations
#define RAND_MAXID_LENGTH 6
#define RAND_MODULO_VAL 70
#endif

// ! Task To Remind Me Macro Definitions - END

class TTRM
{
public:
	// ! REMINDER_TYPES, Types of Reminder, Basically.
	enum REMINDER_TYPES : unsigned
	{
		CancelOperation,
		QuickRemind,
		DateBasedRemind,
	};

	// ! SET_CHOICE_PROCESS, Added Both Possibility Writes by User
	enum SET_CHOICE_PROCESS : char
	{
		CONFIRMED_TRUE_LOWER = 'y',
		CONFIRMED_TRUE_UPPER = 'Y',
		CONFIRMED_FALSE_LOWER = 'n',
		CONFIRMED_FALSE_UPPER = 'N'
	};

	// ! DISPLAY_OPTIONS, Used for Switch-Case Situations.
	enum DISPLAY_OPTIONS : unsigned
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

	// ! Class Initializer Declaration
	TTRM(void)
	{
		std::cout << PROJECT_NAME_STRL << " | " << PROJECT_VER_STRL << std::endl
				  << "Created by " << PROJECT_CREATOR_STRL << std::endl
				  << std::endl
				  << "Group Members\n\tProject Lead: 'Janrey Licas',\n\tSystem Director: 'Rejay Mar'\n"
				  << std::endl
				  << std::endl;
		DelayRunTimeBy(SLEEP_INIT_OBJECT);
	}

	// ! Class Destructor Declaration
	~TTRM(void)
	{
		std::cout << std::endl
				  << "Termination |> Closing Objects and Threads..." << std::endl;
		std::cout << "Termination |> Multi-Thread Function Closed." << std::endl;
		CloseHandle(MultiThreadHandler);
		std::cout << "Termination |> Program Terminated. Window Closing... Goodbye.";
		DelayRunTimeBy(SLEEP_INIT_OBJECT);
		exit(FUNC_OOS);
	}

	// ! Multi Threading Static Functions
	unsigned static __stdcall MultiThread_Wrapper(void *);
	unsigned static __stdcall MultiThread_ScanReminders(void *);

	// ! Function Prototype Declarations - START

	// ! TTRM's Initializer Function Declarations
	void ParseGivenParam(unsigned short argcount, char *argcmd[]);
	unsigned short Cmpnt_Initializer() noexcept(false);

	// ! Task / Menu Displays Function Declarations
	void SP_DisplayTasks(DISPLAY_OPTIONS WindowID_INT) noexcept(false);
	std::string SP_DisplayTasksParser(REMINDER_TYPES IntType) noexcept(true);
	void SP_DisplayMenu() noexcept(false);
	std::string SP_DLT() const noexcept(false); // * Displays Local Time of the System
	void DC_ATask() noexcept(false);			// * Adds Task To The System, Both Applies to Save State and Queue System
	void DC_DTask() noexcept(false);			// * Deletes Task To The System, Both Applies to Save State and Queue System
	void DC_ETask() noexcept(false);			// * Modifies Task To The System, Both Applies to Save State and Queue System
	void DC_VTask() noexcept(false);			// * Views Task To The System, # of Reminders Limitations is Not Applied, This Checks Only On Queue System
	void DC_RQT() noexcept(false);				//  *Removes Queued Tasks and Removes Save State Data
	void DC_RTLFSS() noexcept(false);			// * Refresh TaskList From Save States

	// ! Function Prototype Declarations - START

	// ! Side Component >> Function ID Generator for Reminders, Used for Both Types of Reminders.
	std::string Gen_UniqueRID() noexcept(true);

	// ! TTRM_WinToast Relative Functions. Not Decalred to TTRM_WinToast due to Function Structure of the whole class.
	static void WinToast_ReminderPrompt(std::string ReadName, std::string ReadInCharge, unsigned short ReadReminderType, signed ReadNotifyByTime, tm TMToRead) noexcept;

	// ! Class Member Global-Like Variables. Used for Minimal Initialization on Some Functions.

	// ! Input Handlers
	char InputHandler_Char = NULL_CHAR;
	unsigned short InputHandler_Int = INIT_BASE_NUM;

	// ! Iterator Handlers
	unsigned short IterHandler_UnShort = INIT_BASE_NUM;
	unsigned short TaskNumHandler = START_BY_ONE;
	unsigned int IterHandler_UnInt = INIT_BASE_NUM;
	size_t TaskHandlerSize = INIT_BASE_NUM;
	

	// ! Various Important Handler >> Localtime and Multi-Threading
	time_t EpochHandler = INIT_BASE_NUM;   // ! LocalTime Handler.
	unsigned MTID_Handler = INIT_BASE_NUM; // ! Multi-Threading ID Handler, Can Possibly Anything.
	HANDLE MultiThreadHandler;			   // * Special Variable for Checking Status of Thread, Used for WaitForSingleObject

	// ! File Stream Implementation
	/* 
		* TempDataHandler, String Storage to StringStream
		* ConvertedHandler, Diced Data to PayloadHandler
		* DataLineHandler, Whole Data Row from TempDataHandler
		* PayloadHandler, Diced Data Storage
		* SaveStateHandler, Handler for Save State File
		* TempSaveStateHandler, Handler for Temporary File
	*/
	std::string TempDataHandler, ConvertedHandler, DataLineHandler;
	std::vector<std::string> PayloadHandler;
	std::fstream SaveStateHandler;
	std::fstream TempSaveStateHandler;

	// ! Randomizer Required String
	const std::string AlphaNumConst = "0123456789!@#$%^&*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

protected:
	// ! Const Char* Because of Rename Function Required Data Type. STDIO.h Cause
	const char *SaveStatePath = "TTRM_SaveState._ttrmdat";		 // Unconfirmed
	const char *FilePointState = "TTRM_SaveStatesTemp._ttrmdat"; // Unconfirmed
};

/*
	* TTRM_WinToast is a base class specifically seperated to use WinToast Class 'IWinToastHandler'
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
	} // ! Destroys Toast After To Reduce Memory Consumption.

	// * Function Overriders. Not Doing That Much But Handles Something...
	void toastActivated() const;
	void toastActivated(int actionIndex) const;
	void toastDismissed(WinToastDismissalReason state) const;
	void toastFailed() const;
};

/*
  ! TTRM_TaskData Class is an important base class that utilizes as an object for storing reminders.
  ! It can have two types of reminders which still use the same variables for time storage. It does not
  ! have any functions, nor initializers or destructors.
*/
class TTRM_TaskData
{
public:
	std::string TaskID = NULL_STR;				 // * Unique Task ID Generated by Gen_UniqueRID
	std::string TaskName = NULL_STR;			 // * Task Name
	std::string TaskInCharge = NULL_STR;		 // * Name of the Person Incharge.
	unsigned short ReminderType = INIT_BASE_NUM; // * Used To Distinguish Type of Reminder.
	signed short NotifyByTime = INIT_BASE_NUM;   // * Used by QuickRemind Type Reminder.
	tm *TempTM = NULL_SET;						 // * Temporary Use for Localtime and Data Passing to ReminderData.
	tm ReminderData = NULL_SET;					 // * Actual Storage of the Reminders.
};
#endif