/*
	* Task To Temind Me Core Declarations
    * Side Note: Technical Project Specific Essential Function Header File
    * File Category Type: Core Function Definitions, "CoreDef".
	* Version: Close Beta Stage
	* 
	* Project Lead, Janrey "CodexLink" Licas
	* Project Lead, Rejay "figureness" Mar
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
#define PROJECT_VER L"Close Beta Stage"
#define PROJECT_CREATOR L"Data Structure Group 5"

// ! Short-Term Functions, Macro Definitions
#define DelayRunTimeBy(millsec) std::this_thread::sleep_for(std::chrono::milliseconds(millsec))
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
#define INIT_BASE_NUM 0		 // * Significance for Base Positive Number is Zero.
#define START_BY_ONE 1		 // * Significance for Base Starting Point is One.
#define NULL_STR ""			 // * Significance for String Initialization at Starting Point of NULL.
#define NULL_CHAR ''			 // * Significance for CHAR Initialization at Starting Point of NULL.
#define NULL_SET {0} 		 // * Significance for Setting Some Structure Members to Zero.
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
	enum REMINDER_TYPES : unsigned int
	{
		CancelOperation,
		QuickRemind,
		DateBasedRemind,
	};
	enum SET_CHOICE_PROCESS : char
	{
		CONFIRMED_TRUE_LOWER = 'y',
		CONFIRMED_TRUE_UPPER = 'Y',
		CONFIRMED_FALSE_LOWER = 'n',
		CONFIRMED_FALSE_UPPER = 'N'
	};

	enum DISPLAY_OPTIONS
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

	TTRM(void)
	{
		std::cout << PROJECT_NAME << " | " << PROJECT_VER << std::endl
				  << "Created by " << PROJECT_CREATOR << std::endl
				  << std::endl
				  << "Group Members\n\t\tProject Lead: 'Janrey Licas',\n\t\tSystem Director: 'Rejay Mar'\n"
				  << std::endl
				  << std::endl;
		DelayRunTimeBy(SLEEP_INIT_OBJECT);
	}

	~TTRM(void)
	{
		std::cout << std::endl
				  << "Termination |> Closing Objects and Threads." << std::endl;
		std::cout << "Termination |> Multi-Thread Function Closed." << std::endl;
		CloseHandle(MultiThreadHandler);
		std::cout << "Termination |> Program Terminates in 2 Seconds. Goodbye.";
		DelayRunTimeBy(SLEEP_INIT_OBJECT);
		exit(FUNC_OOS);
	}

	// TTRM's CoreFunc Functions
	std::string ReminderID_Generate() noexcept;
	void ParseGivenParam(unsigned short argcount, char *argcmd[]);
	unsigned static __stdcall MultiThread_Wrapper(void *);
	unsigned static __stdcall MultiThread_ScanReminders(void *);

	unsigned short ComponentCheck(bool isNeededToRun) noexcept(false);
	void runSystemMenu() noexcept(false);
	std::string DisplayItem_ParseType(REMINDER_TYPES IntType) noexcept;
	void DisplayTasks_AtWindow(DISPLAY_OPTIONS WindowID_INT) noexcept;

	// TTRM_WinToast Relative Functions. Not Decalred to TTRM_WinToast due to Function Structure of the whole class.
	void WinToast_ShowTaskCForToday() noexcept;
	static void WinToast_ReminderPrompt(std::string ReadName, std::string ReadInCharge, unsigned short ReadReminderType, signed ReadNotifyByTime, tm TMToRead) noexcept;

	std::string runSystem_GetTimeLocal() const noexcept;
	void MenuSel_ATask() noexcept(false);
	void MenuSel_DTask() noexcept;
	void MenuSel_ETask() noexcept(false);
	void MenuSel_VTask() noexcept(false);
	void MenuSel_RQT() noexcept(false);	//  RemoveQueuedTask
	void MenuSel_RTLFSS() noexcept(false); //  RefreshTaskListFromSaveStates
	// These variables will be globally use by functions to reduce variable initialization by candidating only few ones from the class state.
	unsigned short TASK_LIMIT_SIZE = TASK_DISPLAY_LIMIT; // By Default, 5.
	char handleInputChar = NULL_CHAR;
	unsigned short handleInputInt = INIT_BASE_NUM;
	unsigned short IterHandler_UnSh = INIT_BASE_NUM;
	unsigned int IterHandler_UnIn = INIT_BASE_NUM;
	signed int IterHandler_SiIn = INIT_BASE_NUM;
	signed short IterHandler_SiSh = INIT_BASE_NUM;

	//static unsigned short WinToast_ReturnTrigger;

	time_t EpochHandler = INIT_BASE_NUM;
	unsigned MultiThreadID = INIT_BASE_NUM; // For Multi-Threading HandleID...

	// For File Stream Implementation
	std::string TempDataHandler, ConvertedHandler, DataLineHandler;
	std::vector<std::string> PayloadHandler;
	//std::stringstream RowHandler; ./ Went to Local Scope Declaration.
	std::fstream SaveStateHandler;
	std::fstream TempSaveStateHandler;
	const std::string AlphaNumConst = "0123456789!@#$%^&*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	HANDLE MultiThreadHandler;

protected:
	// ! Const Char* Because of Rename Function Required Data Type. STDIO.h Cause
	const char *SaveStatePath = "TTRM_SaveState._ttrmdat";		 // Unconfirmed
	const char *FilePointState = "TTRM_SaveStatesTemp._ttrmdat"; // Unconfirmed
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
	~TTRM_WinToast(void)
	{ WinToast::instance()->clear(); }

	// * Overriders. Not Doing That Much But Handles Something...
	void toastActivated() const;
	void toastActivated(int actionIndex) const;
	void toastDismissed(WinToastDismissalReason state) const;
	void toastFailed() const;
};

/*
 TTRM_TaskData is an important base class that utilizes System-Proposed Functions specificially used for scheduler. This means that all functions residing
 in this class is basically related to the Proposed System that we wanted to make. This base class was not on a confirmed status. Please be advised.
*/
class TTRM_TaskData
{

public:
	std::string TaskID = NULL_STR;
	std::string TaskName = NULL_STR;
	std::string TaskInCharge = NULL_STR;
	unsigned short ReminderType = INIT_BASE_NUM;
	signed short NotifyByTime = INIT_BASE_NUM;
	tm *TempTM = NULL_SET;
	tm ReminderData = NULL_SET;
};
#endif