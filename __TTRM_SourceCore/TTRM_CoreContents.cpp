/*
    Technical Project Specific Essential Function CPP File by Janrey "CodexLink" Licas
    File Category Type: Technical and Core Function Body Definition, "CoreFunc".
	
	Overview

	- Core Functions

	- Technical Functions
*/

#include "TTRM_CoreDeclares.h"

std::deque<TTRM_TaskData *> TaskList;

void TTRM::ParseGivenParam(unsigned short argcount, char *argv[])
{
	unsigned int ParamIter = INIT_NULL;
	std::cout << "Task To Remind Me C++ in CLI version. BETA" << std::endl
			  << std::endl;
	std::cout << "Created by Data Structure Group 5, Group Members {\n Header Core Developer: 'Janrey Licas',\n AppFlow Director: 'Rejay Mar'\n};" << std::endl
			  << std::endl;
	std::cout << "[Perform Parameter Given] |> Counted Parameter: " << argcount << std::endl;
	while (!strcmp(argv[ParamIter], "") && ParamIter != LIMIT_ARGC_COUNTER)
	{
		// Create more features here. Use switch for Selection of Data here.
		std::cout << " Parameter Index " << ParamIter << " |> Parameter Value -> " << argv[ParamIter] << std::endl;
	}
}

bool TTRM::ComponentCheck(bool isNeededToRun) noexcept(false)
{
	long posx = INIT_NULL, posy = INIT_NULL;
	try
	{
		HWND console = GetConsoleWindow(); //, hwnd = GetConsoleWindow();
		RECT ConsoleWindow, ClietnScrWindow;
		HMENU hmenu = GetSystemMenu(console, FALSE);
		SetConsoleTitle("Task To Remind Me | C++ | Early BETA // github.com/CodexLink");
		GetClientRect(console, &ConsoleWindow);
		GetWindowRect(console, &ClietnScrWindow);
		posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (ClietnScrWindow.right - ClietnScrWindow.left) / 2,
		posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (ClietnScrWindow.bottom - ClietnScrWindow.top) / 2,
		MoveWindow(console, posx, posy, ClietnScrWindow.right - ClietnScrWindow.left, ClietnScrWindow.bottom - ClietnScrWindow.top, TRUE);
		//MoveWindow(console, ConsoleMainApp.left, ConsoleMainApp.top, 1000, 500, TRUE);

		EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
		std::cout << "Component Checking Point | Before Program Initialization" << std::endl
				  << "WinToast Library |> Checking Compatibility...";
		if (WinToast::isCompatible())
		{
			std::cout << std::endl
					  << "WinToast Library |> Compatible. Setting Up Parameters..." << std::endl;
			WinToast::instance()->setAppName(L"Task To Remind Me C++ CLI");
			WinToast::instance()->setAppUserModelId(WinToast::configureAUMI(L"Data Struct Group 5", L"Task To Remind Me", L"TTRM C++", L"Early Beta Stage"));
			std::cout << "WinToast Library |> Application Name Loaded." << std::endl;

			WinToastTemplate WinToastInit_Welcome(WinToastTemplate::Text02);
			WinToastInit_Welcome.setTextField(PROJECT_NAME, WinToastTemplate::FirstLine);
			WinToastInit_Welcome.setTextField(L"Hello There! Program Initialized.", WinToastTemplate::SecondLine);
			WinToastInit_Welcome.setAudioPath(WinToastTemplate::Reminder);
			std::cout << "WinToast Library |> Application Profile, Header and App Name Loaded." << std::endl;

			if (WinToast::instance()->initialize())
			{
				std::cout << "WinToast Library |> Initialized." << std::endl;
				if (!WinToast::instance()->showToast(WinToastInit_Welcome, new TTRM_WinToast))
				{
					std::cerr << "WinToast Library |> Error. Could Not Launch Toast Notification!" << std::endl;
					Sleep(SLEEP_SIGNIFICANT_ERR);
				}
				else
				{
					delay_time(SLEEP_OPRT_FINISHED);
				}
			}
			else
			{
				std::cerr << "WinToast Library |> Error. Cannot Initialize WinToast, Notification Disabled." << std::endl;
				delay_time(SLEEP_ERROR_PROMPT);
			}
			if (isNeededToRun)
			{
				return (bool)(TERM_SUCCESS);
			}
			else
			{
				return (bool)(TERM_FAILED);
			}
		}
	}
	catch (const std::runtime_error &ErrMsg)
	{
		std::cerr << "Runtime Error |> " << ErrMsg.what() << std::endl;
	}
	catch (const std::exception &ErrMsg)
	{
		std::cerr << "Exception |> " << ErrMsg.what() << std::endl;
	}
}

void TTRM::runSystemMenu() noexcept
{
	signed int DisplayMenu_Input = INIT_NULL;
	WinToast_ShowTaskCForToday();
	while (NOT_REQ_TERM)
	{
		WinAPI_CMDCall("CLS");
		std::cout << std::endl
				  << "Task To Remind Me C++ in CLI version. BETA" << std::endl
				  << std::endl;
		std::cout << "Time From Your Local System [Last Updated] |> " << std::endl;

		std::cout << std::endl
				  << "=== Incoming Task/s for Today =========================" << std::endl;
		runDisplayTasks_AtHome();
		std::cout << std::endl
				  << "=== Task Function Menu ================================" << std::endl
				  << std::endl
				  << "1 |> Add a Task" << std::endl
				  << "2 |> Delete an Existing Task/s" << std::endl
				  << "3 |> Edit / Modify an Existing Task/s" << std::endl
				  << "4 |> View All Tasks" << std::endl
				  << std::endl
				  << "=== Technical Function Menu ===========================" << std::endl
				  << std::endl
				  << "5 |> Manually Refresh All Tasks Queue from Database (Hard Reset)" << std::endl
				  << "6 |> Set Auto-Start Application : Status > [" << ComponentStats_Indicator(AutoStartID) << "]" << std::endl
				  << "7 |> Set WinToast Reminder: Status > [" << ComponentStats_Indicator(WinToastID) << "]" << std::endl
				  << "8 |> Set SQL Database Status: Status > [" << ComponentStats_Indicator(SQLiteID) << "]" << std::endl
				  << "0 |> Terminate / Exit Program" << std::endl
				  << std::endl;

		std::cout << "[Input] Your Choice then PRESS ENTER |> ";
		std::cin >> DisplayMenu_Input;
		CinBuffer_ClearOptpt('\n');
		if (std::cin.fail())
		{
			std::cin.clear();
			CinBuffer_ClearOptpt('\n');
			std::cout << "[ERROR] User Input Error -> Input Is Non-Existing or Non-Integer." << std::endl;
			delay_time(SLEEP_ERROR_PROMPT);
			continue;
		}
		// Stack the function.
		// Return to 'this' function so that we can go back to this function easily.
		switch (DisplayMenu_Input)
		{
		case AddTask:
			MenuSel_ATask();
			break;
		case DeleteTask:
			MenuSel_DTask();
			break;
		case EditTask:
			MenuSel_ETask();
			break;
		case ViewTask:
			MenuSel_VTask();
			break;
		case ManualDatabaseRefresh:
			MenuSel_DBRefresh();
			break;
		case AutoStartup:
			MenuSel_AutoStart();
			break;
		case WinToastIntegration:
			MenuSel_WTI();
			break;
		case SQLDb_CheckState:
			MenuSel_WTI();
			break;
		case Termination:
			break;
		default:
			std::cout << std::endl
					  << "[ERROR] User Inputted Not Included in the List!" << std::endl;
			delay_time(SLEEP_ERROR_PROMPT);
			break;
		}
		if (!DisplayMenu_Input)
			break;
	}
	return;
}

void TTRM::runDisplayTasks_AtHome() noexcept
{
	unsigned short TaskNum = INIT_BY_LITERAL_ONE;
	if (!TaskList.size())
	{
		std::cerr << std::endl
				  << "There are not tasks for today~! Add one." << std::endl;
		return;
	}
	else
	{
		std::deque<unsigned short>::iterator IterTasks;
		std::cout << std::endl
				  << "There are " << TaskList.size() << (TaskList.size() <= INDIVIDUAL_OR_LESS ? " task" : " tasks") << " for today~!" << std::endl << std::endl;
		for (auto IterTasks : TaskList)
		{
			std::cout << TaskNum << "|> " << IterTasks->TaskName << "\t" << IterTasks->DateStartTime << "\t" << std::endl;
			TaskNum++;
		}
		return;
	}
}

void TTRM::WinToast_RemindTask() noexcept
{
	//std::string TemplateToReturn;
	std::stringstream TaskListSize;
	//TaskListSize << "Hello There! There are" << TaskList.size() << ((TaskList.size() <= //INDIVIDUAL_OR_LESS) ? "task" : "tasks") << " for today.";
	//TemplateToReturn.append(TaskListSize.str());
	//return TemplateToReturn;
	TaskListSize << TaskList.size();
	//std::wcout << TaskListSize.str();
}

void TTRM::WinToast_ShowTaskCForToday() noexcept
{
	WinToast::instance()->clear(); // Clears First Toast. Overwritten by 'this' template.
	WinToastTemplate TaskCountShow(WinToastTemplate::Text02);
	std::wstring TaskCount = std::to_wstring(TaskList.size());
	std::wstring WelcomeFirstPT = L"Hello User, You have ";
	std::wstring WelcomeSecondPT = (TaskList.size() <= INDIVIDUAL_OR_LESS) ? L" task" :  L"tasks";
	std::wstring WelcomeThirdPT = L" for today.";
	TaskCountShow.setTextField(PROJECT_NAME, WinToastTemplate::FirstLine);
	TaskCountShow.setTextField(WelcomeFirstPT + TaskCount + WelcomeSecondPT + WelcomeThirdPT,WinToastTemplate::SecondLine);
	// We dont check anything, since we have done it in the first place.
	WinToast::instance()->showToast(TaskCountShow, new TTRM_WinToast);
	return;
}
void TTRM::WinToast_ShowReminder() noexcept
{
	//WinToastTemplate ShowReminder()
	return;
}
std::string TTRM::ComponentStats_Indicator(ComponentID CompToCheck) noexcept
{
	switch (CompToCheck)
	{
	case WinToastID:
		if (WinToast::instance()->initialize())
		{
			return "Initialized, Working.";
		}
		else
		{
			return "Not Working At This Point.";
		}
	case AutoStartID:
		return "Currently !Implemented";
	case SQLiteID:
		return "Currently !Implemented";
	default:
		return "Unknown";
	}
}

void TTRM::MenuSel_ATask() noexcept(false)
{
	TTRM_TaskData *NewTask = new TTRM_TaskData;
	while (PROCESS_AWAIT_CMPLT)
	{

		// Add Design here
		WinAPI_CMDCall("CLS");
		std::cout << "[Required] Task Name |> ", std::getline(std::cin, NewTask->TaskName);
		std::cout << "[Required, Format | YYYY-MM-DD] Date Starting Point |> ", std::getline(std::cin, NewTask->DateStartTime);
		std::cout << "[Required, Date Ending Point] Format > YYYY-MM-DD |> ", std::getline(std::cin, NewTask->DateEndTime);
		std::cout << "[Optional] NotifierInterval, By Minutes |> ", std::cin >> NewTask->NotifierInterval;
		if (std::cin.fail())
		{
			std::cin.clear();
			CinBuffer_ClearOptpt('\n');
			std::cerr << "[Input Error] -> One of parameters has its input invalid. Please try again." << std::endl;
			delay_time(SLEEP_ERROR_PROMPT);
			continue;
		}
		else
		{
			//Pushing Area
			try
			{
				TaskList.push_back(NewTask);
				break;
			}
			catch (std::exception &ErrMessage)
			{
				std::cerr << ErrMessage.what() << std::endl;
				delay_time(SLEEP_SIGNIFICANT_ERR);
				break;
			}
		}
	}
	return;
}
void TTRM::MenuSel_DTask() noexcept(false)
{
	WinAPI_CMDCall("CLS");
	std::cout << "2" << std::endl;
}
void TTRM::MenuSel_ETask() noexcept(false)
{
	WinAPI_CMDCall("CLS");
	std::cout << "3" << std::endl;
}
void TTRM::MenuSel_VTask() noexcept(false)
{
	WinAPI_CMDCall("CLS");
	std::cout << "4" << std::endl;
}
void TTRM::MenuSel_DBRefresh() noexcept
{
	WinAPI_CMDCall("CLS");
	std::cout << "5" << std::endl;
}
void TTRM::MenuSel_ReqTasks() noexcept
{
	WinAPI_CMDCall("CLS");
	std::cout << "6" << std::endl;
}
void TTRM::MenuSel_AutoStart(void) const noexcept
{
	WinAPI_CMDCall("CLS");
	std::cout << "7" << std::endl;
}
void TTRM::MenuSel_WTI(void) const noexcept
{
	WinAPI_CMDCall("CLS");
	std::cout << "8" << std::endl;
}

// CORE FUNCTION CONTENT DECLARATION - END POINT

//----------------------------------------------------------------------------

// TECHNICAL FUNCTION CONTENT DECLARATION - STARTING POINT

/*
    Technical Project Specific Essential Function CPP File by Janrey "CodexLink" Licas
    File Category Type: Core Function Body Definition, "CoreFunc".
	Note that this CPP file will only contain external library functions.
*/

//	SQLite Library Function Declaration - START
void TTRM::SQLite_Initialize() const noexcept(false)
{
	return;
}
void TTRM::SQLite_CheckDatabase() const noexcept(false)
{
	return;
}
void TTRM::SQLite_ReloadQueue() const noexcept(false)
{
	return;
}
void TTRM::SQLite_CRUD_Data(SQLite_QueryType ExecutionQueryType) const noexcept(false)
{
	return;
}
//	SQLite Library Function Declaration - END

// TECHNICAL FUNCTION CONTENT DECLARATION - END POINT


//----------------------------------------------------------------------------

// WinToast FUNCTION CONTENT DECLARATION - STARTING POINT


// WinToast FUNCTION CONTENT DECLARATION - END POINT