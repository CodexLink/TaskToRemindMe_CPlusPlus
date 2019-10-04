/*
    Technical Project Specific Essential Function Header File by Janrey "CodexLink" Licas
    File Category Type: Core Function Definitions, "CoreDef".
*/

/*

Things To Know #1 - ENUMs,
	A Group or contains that specific values that classifies specialized for returning
	reference values. For example, we need a group of reference values for returning error codes.
	Hence, this example is refernced to our first ENUM called TERM_RET_ERROR
*/
#pragma once
#ifndef TechProSpEssential_TTRM_H
#define TechProSpEssential_TTRM_H // We define this marker for indication of "already initialized"

#include <iostream>
#include <conio.h>
#include <string>
#include <deque>
#include <vector>
#include <windows.h> // For Win32 API, We manipulate our console here.
#include <process.h>
#include "WinToastLib/wintoastlib.h"
#include <chrono>
#include <thread>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>

// #define Function-Like Declaration and Constant Uncategorized Definitions
#define PROJECT_NAME L"Quick Task To Me C++ CLI | DS Group 5"
#define PROJECT_VER L"Early Testing Case"
#define delay_time(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))
#define WinCall_CMD(x) system(x);
#define CinBuffer_ClearOptpt(__CharIgnore_Start) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), __CharIgnore_Start);
using namespace WinToastLib;

#undef max // Visual Studio Overriding Function To Be Undefined.

// ! Regarding 'This' Pragma. The reason of declaring this one is because of an issue about arguments that can be passed both on localtime_s and mktime. localtime_s needs a struct tm while mktime needs a struct *tm. This issue was caused on code issue where allocation happens and possible memory leak might be the result which is a bad idea.

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

// TERM_RET_ERROR - An ENUM that contains Termination Return Error. Useful for Deconstructor Error Display
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
#define ZERO_CMPR_BASE 0
#define DO_NOTHING 0

// Superposition Method, Parameters used for when we want to run this function content or not. Used for Selected Technical  Functions only.
#define IGNORE_PROCESS 0
#define RUN_PROCESS 1
#define NOT_REQ_TERM 1
#define NO_ERR_AT_SCAN 1
#define NO_TASK_REPEAT_PRC 0
#define EOS_FUNC 1
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
#define MIN_TIME_HOUR 0
#define MAX_TIME_HOUR 23
#define MIN_TIME_MIN 0
#define MAX_TIME_MIN 59
#define MIN_TIMELEFT 0
#define MAX_TIMELEFT 180

#define TASK_DISPLAY_LIMIT 5
#define TASK_DISPLAY_CRUD 10
#define MAX_TASK_ATTACHABLE 50
#define MAX_SCAN_REMINDERS 10
#define START_CTIME 1900
#define WAIT_STARTTHREAD 1000
#endif

/*
    TTRM is base class that initializes...
*/
class TTRM
{
	/*
		This class class contain variables, objects structors and functions.
		So here's na overview.
		- Constructors
		- Variables
		- Structs
		- Enums
		- Functions
	*/
public:
	enum TERM_RET_ERROR : unsigned short
	{
		TERM_SUCCESS,
		TERM_FAILED,
		TERM_INVALID_PARAM
	};

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
		RemoveAllTask,
		RefreshTaskList,
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

	TTRM(void)
	{
		std::cout << "Quick Tasks To Remind Me C++ CLI, Version 09/28/2019-2026" << std::endl
				  << std::endl
				  << "Created by Data Structure Group 5, Group Members {\nProject Leader and Program Developer: 'Janrey Licas',\n AppFlow Director: 'Rejay Mar'\n};" << std::endl
				  << std::endl;
		delay_time(SLEEP_INIT_OBJECT);
	}

	~TTRM(void)
	{
		std::cout << std::endl
				  << "Termination |> Closing Objects and Threads." << std::endl;
		std::cout << "Termination |> Multi-Thread Function Closed." << std::endl;
		CloseHandle(MultiThreadHandler);
		std::cout << "Termination |> Program Terminates in 2 Seconds. Goodbye.";
		delay_time(SLEEP_INIT_OBJECT);
		exit(USER_OUTOFSCOPE_TERM_SUCCESS);
	}

	// TTRM's CoreFunc Functions
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
	void MenuSel_RQT() noexcept(false); //  RemoveQueuedTask
	void MenuSel_RTLFSS() noexcept(false); //  RefreshTaskListFromSaveStates
	// These variables will be globally use by functions to reduce variable initialization by candidating only few ones from the class state.
	unsigned short TASK_LIMIT_SIZE = TASK_DISPLAY_LIMIT; // By Default, 5.
	char handleInputChar = INIT_NULL_CHAR;
	unsigned short handleInputInt = INIT_NULL_INT;
	unsigned short IterHandler_UnSh = INIT_NULL_INT;
	unsigned int IterHandler_UnIn = INIT_NULL_INT;
	signed int IterHandler_SiIn = INIT_NULL_INT;
	signed short IterHandler_SiSh = INIT_NULL_INT;

	time_t EpochHandler = INIT_NULL_INT;
	unsigned MultiThreadID = INIT_NULL_INT; // For Multi-Threading HandleID...

	// For File Stream Implementation
	std::string TempDataHandler, ConvertedHandler, DataLineHandler;
	std::vector<std::string> PayloadHandler;
	//std::stringstream RowHandler; ./ Went to Local Scope Declaration.
	std::fstream SaveStateHandler;
	std::fstream TempSaveStateHandler;
	HANDLE MultiThreadHandler;

protected:
// ! Const Char* Because of Rename Function Required Data Type. STDIO.h Cause
	const char* SaveStatePath = "TTRM_SaveState._ttrmdat"; // Unconfirmed
	const char* FilePointState = "TTRM_SaveStatesTemp._ttrmdat"; // Unconfirmed
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
	void toastActivated() const;
	void toastActivated(int actionIndex) const;
	void toastDismissed(WinToastDismissalReason state) const;
	void toastFailed() const;


	// ! We hold task index and pass it TaskList since TaskList which is a deque variable is declared as Local in this part of file.
	unsigned TaskIndex = INIT_NULL_INT;
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
	signed short NotifyByTime = INIT_NULL_INT;
	tm *TempTM = {0};
	tm ReminderData = {0};
};
#endif