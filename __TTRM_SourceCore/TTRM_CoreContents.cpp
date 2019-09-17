/*
    Technical Project Specific Essential Function CPP File by Janrey "CodexLink" Licas
    File Category Type: Technical and Core Function Body Definition, "CoreFunc".
	
	Overview	 

	- Core Functions

	- Technical Functions
*/

#include "TTRM_CoreDeclares.h"

std::deque<TTRM_TaskData> TaskList;

void TTRM::ParseGivenParam(unsigned short argcount, char *argv[])
{
	unsigned int ParamIter = INIT_NULL_INT;
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

unsigned short TTRM::ComponentCheck(bool isNeededToRun) noexcept(false)
{
	long posx = INIT_NULL_INT, posy = INIT_NULL_INT;
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
		MoveWindow(console, posx, posy, ClietnScrWindow.right - ClietnScrWindow.left, (ClietnScrWindow.bottom - ClietnScrWindow.top) * (double)(1.3), TRUE);
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
				return TERM_SUCCESS;
			}
			else
			{
				return TERM_FAILED;
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

void TTRM::runSystemMenu() noexcept(false)
{
	unsigned int DisplayMenu_Input = INIT_NULL_INT;
	WinToast_ShowTaskCForToday();
	while (NOT_REQ_TERM)
	{
		WinCall_CMD("CLS");
		auto TimeStamp = std::chrono::system_clock::now();
		std::cout << std::endl
				  << "Task To Remind Me C++ in CLI version. BETA" << std::endl
				  << std::endl;
		// Create function for String To Time here.

		std::cout << "Last Time Frame From Your Local System |> " << runSystem_GetTimeLocal() << std::endl;
		std::cout << std::endl
				  << "=== Incoming Task/s for Today =========================" << std::endl;
		DisplayTasks_AtWindow(AtHome);
		std::cout << std::endl
				  << "=== Basic Tasks Functions, Function Proggression 100% ==========" << std::endl
				  << std::endl
				  << "1 |> Add a Task [Abort Option Left]" << std::endl
				  << "2 |> Delete a Task/s" << std::endl
				  << "3 |> Edit / Modify an Existing Task/s [TimeSens Not Purely Achieved]" << std::endl
				  << "4 |> View All Tasks" << std::endl
				  << std::endl
				  << "=== Advanced Tasks Functions ================================" << std::endl
				  << std::endl
				  << "5 |> Sort All Tasks By Starting Date [Currently !Implemented]" << std::endl
				  << "6 |> Remove All Tasks [Completed, Database Left]" << std::endl
				  << "7 |> Refresh All Tasks [Currently !Implemented]" << std::endl
				  << std::endl
				  << "=== Technical Options =================================" << std::endl
				  << std::endl
				  << "8 |> Program Component Status and Enablers [Currently !Implemented]" << std::endl
				  << "9 |> Minimize Program to System Tray [Currently !Implemented]" << std::endl
				  << "0 |> Terminate / Exit Program" << std::endl
				  << std::endl;
		/*
				  << "6 |> Set Auto-Start Application : Status > [" << ComponentStats_Indicator(AutoStartID) << "]" << std::endl
				  << "7 |> Set WinToast Reminder: Status > [" << ComponentStats_Indicator(WinToastID) << "]" << std::endl
				  << "8 |> Set SQL Database Status: Status > [" << ComponentStats_Indicator(SQLiteID) << "]" << std::endl
				  */

		std::cout << "[Input] Your Choice and ENTER |> ";
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
		case SortTask:
			MenuSel_SQT();
			break;
		case RemoveAllTask:
			MenuSel_RQT();
			break;
		case RefreshContainerTask:
			MenuSel_RCT();
			break;
		case ComponentStatus:
			MenuSel_CS();
			break;
		case MinimizeRunningInst:
			MenuSel_MRI();
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

void TTRM::DisplayTasks_AtWindow(DISPLAY_OPTIONS WindowID_INT) noexcept
{
	unsigned short TaskNum = INIT_BY_LITERAL_ONE, TASK_LIMIT_ITER = INIT_NULL_INT;
	bool isAtHome = false;
	if (!TaskList.size())
	{
		std::cerr << std::endl
				  << "There are no task/s in queue! Please add one." << std::endl;
		return;
	}
	else
	{
		std::cout << std::endl
				  << "There are " << TaskList.size() << (TaskList.size() <= BY_ONE_OR_LESS ? " task" : " tasks");
		switch (WindowID_INT)
		{
		case DeleteTask:
			std::cout << " available to delete!" << std::endl
					  << std::endl;
			break;
		case EditTask:
			std::cout << " available to edit!" << std::endl
					  << std::endl;
			break;
		case ViewTask:
			std::cout << " in total at queue system!" << std::endl
					  << std::endl;
			break;
		case SortTask:
			std::cout << " sorted from the system!" << std::endl;
			break;

		case RemoveAllTask:
			std::cout << " removed from the system!" << std::endl;
			break;

		case RefreshContainerTask:
			std::cout << " loaded and sorted to the system!" << std::endl;
			break;

		case AtHome:
			isAtHome = true;
			std::cout << " for today~!" << std::endl
					  << std::endl;
			break;
		default:
			std::cerr << "... ???" << std::endl;
		}

		for (auto IterTasks : TaskList)
		{
			if (isAtHome && TaskNum > TASK_LIMIT_SIZE)
			{
				std::cout << std::endl
						  << "And there are other " << (TaskList.size() + POS_OFFSET_BY_ONE) - TaskNum << (((TaskList.size() + POS_OFFSET_BY_ONE) - TaskNum) == BY_ONE_OR_LESS ? " task" : " tasks") << " available!" << std::endl;
				break;
			}
			else
			{
				std::cout << TaskNum << "|> " << IterTasks.TaskName
						  << "\t" << IterTasks.TaskInCharge
						  << "\t" << (!IterTasks.ReminderType ? "Continous" : "Time-Based")
						  << "\t" << IterTasks.DateStartTime.tm_year << "-" << IterTasks.DateStartTime.tm_mon << "-" << IterTasks.DateStartTime.tm_mday
						  << "\t" << IterTasks.DateEndTime.tm_year << "-" << IterTasks.DateEndTime.tm_mon << "-" << IterTasks.DateEndTime.tm_mday
						  << "\t" << IterTasks.TimeTrigger.tm_hour << ":" << IterTasks.TimeTrigger.tm_min
						  << "\t" << IterTasks.NotifierOffset
						  << std::endl;
				TaskNum++;
			}
		}
		return;
	}
}

std::string TTRM::runSystem_GetTimeLocal() const noexcept
{
	tm TimeStorage;
	time_t TimeStamp = time(NULL);
	std::stringstream StrTime;
	localtime_s(&TimeStorage, &TimeStamp);
	StrTime << TimeStorage.tm_mon + POS_OFFSET_BY_ONE << "-" << TimeStorage.tm_mday << "-" << TimeStorage.tm_year + START_CTIME << " | " << TimeStorage.tm_hour << ":" << TimeStorage.tm_min << ":" << TimeStorage.tm_sec;
	return StrTime.str();
}
void TTRM::WinToast_RemindTask() noexcept
{
	//std::string TemplateToReturn;
	std::stringstream TaskListSize;
	//TaskListSize << "Hello There! There are" << TaskList.size() << ((TaskList.size() <= //BY_ONE_OR_LESS) ? "task" : "tasks") << " for today.";
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
	std::wstring WelcomeSecondPT = (TaskList.size() <= BY_ONE_OR_LESS) ? L" task" : L"tasks";
	std::wstring WelcomeThirdPT = L" for today.";
	TaskCountShow.setTextField(PROJECT_NAME, WinToastTemplate::FirstLine);
	TaskCountShow.setTextField(WelcomeFirstPT + TaskCount + WelcomeSecondPT + WelcomeThirdPT, WinToastTemplate::SecondLine);
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
	while (PROCESS_AWAIT_CMPLT)
	{
		TTRM_TaskData NewTask; // Create Object To Pass On...
		tm TimeContainer;
		time_t TimeStampData = time(NULL);
		localtime_s(&TimeContainer, &TimeStampData);
		WinCall_CMD("CLS");
		std::cout << "[Required] Name of the Task |> ", std::getline(std::cin, NewTask.TaskName);
		if (NewTask.TaskName.length() < MIN_CHAR_TASKNAME || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> TaskName Character Is Not Enough. Press Enter Key To Try Again." << std::endl;
			CinBuffer_ClearOptpt('\n');
			continue;
		}
		std::cout << "[Required] Name of Person In Charge |> ", std::getline(std::cin, NewTask.TaskInCharge);
		if (NewTask.TaskInCharge.length() < MIN_CHAR_INCHARGE || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> Task In Charge Character Is Not Enough. Press Enter Key To Try Again." << std::endl;
			CinBuffer_ClearOptpt('\n');
			continue;
		}
		std::cout << "[Required, 1 = Quick, 2 = Time-Based] Type of Reminder |> ", std::cin >> NewTask.ReminderType;
		if (NewTask.ReminderType < RemindContinous || NewTask.ReminderType > RemindTimeBased || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> Reminder Type Input is Invalid. Press Any Key To Try Again." << std::endl;
			CinBuffer_ClearOptpt('\n');
			_getche();
			continue;
		}
		std::cout << "[Req, Seperate by Space | YYYY MM DD] Task Start Point |> ", std::cin >> NewTask.DateStartTime.tm_year >> NewTask.DateStartTime.tm_mon >> NewTask.DateStartTime.tm_mday;
		if (NewTask.DateStartTime.tm_year < (TimeContainer.tm_year + START_CTIME) || (NewTask.DateStartTime.tm_mon < MIN_TIME_MONTH || NewTask.DateStartTime.tm_mon > MAX_TIME_MONTH || NewTask.DateStartTime.tm_mon < TimeContainer.tm_mon) || (NewTask.DateStartTime.tm_mday < MIN_TIME_DAY || NewTask.DateStartTime.tm_mday > MAX_TIME_DAY || NewTask.DateStartTime.tm_mday < TimeContainer.tm_mday) || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> Start Date Parameters is either invalid, less or exceed from expected value. Press Any Key To Try Again." << std::endl;
			CinBuffer_ClearOptpt('\n');
			_getche();
			continue;
		}
		std::cout << "[Req, Seperate by Space | YYYY MM DD] Task End Point |> ", std::cin >> NewTask.DateEndTime.tm_year >> NewTask.DateEndTime.tm_mon >> NewTask.DateEndTime.tm_mday;
		if (NewTask.DateEndTime.tm_year < NewTask.DateStartTime.tm_year || (NewTask.DateEndTime.tm_mon < MIN_TIME_MONTH || NewTask.DateEndTime.tm_mon > MAX_TIME_MONTH || NewTask.DateEndTime.tm_mon < NewTask.DateStartTime.tm_mon) || (NewTask.DateEndTime.tm_mday < MIN_TIME_DAY || NewTask.DateEndTime.tm_mday > MAX_TIME_DAY || NewTask.DateEndTime.tm_mday < NewTask.DateStartTime.tm_mday) || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> End Date Parameters is either invalid, less or exceed from expected value. Press Any Key To Try Again." << std::endl;
			CinBuffer_ClearOptpt('\n');
			_getche();
			continue;
		}
		std::cout << "[Req, Seperate by Space | 00 00-23 59] Time To Remind You |> ", std::cin >> NewTask.TimeTrigger.tm_hour >> NewTask.TimeTrigger.tm_min;
		if ((NewTask.TimeTrigger.tm_hour < MIN_TIME_HOUR || NewTask.TimeTrigger.tm_hour > MAX_TIME_HOUR) || (NewTask.TimeTrigger.tm_min < MIN_TIME_MIN || NewTask.TimeTrigger.tm_min > MAX_TIME_MIN) || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> Time Input is Invalid. Keep in mind that I need 24 hour format. Press Any Key To Try Again." << std::endl;
			CinBuffer_ClearOptpt('\n');
			_getche();
			continue;
		}
		std::cout << "[Opt, 0-180] Notification EarlyTime, By Minutes |> ", std::cin >> NewTask.NotifierOffset;
		if (NewTask.NotifierOffset < MIN_EARLYTIME || NewTask.NotifierOffset > MAX_EARLYTIME || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> Early Time Input is Invalid. Press Enter Key To Try Again." << std::endl;
			CinBuffer_ClearOptpt('\n');
			_getche();
			continue;
		}
		try
		{
			TaskList.push_back(NewTask);
			std::cout << std::endl
					  << "[PROCESS] |> Task '" << NewTask.TaskName << "' has been successfully added to the queue!";
			delay_time(SLEEP_OPRT_FINISHED);
			break;
		}
		catch (std::exception &ErrMessage)
		{
			std::cerr << std::endl
					  << ErrMessage.what() << std::endl;
			delay_time(SLEEP_SIGNIFICANT_ERR);
			continue;
		}
		catch (...)
		{
			std::cerr << "[PROCESS] Unknown Error..." << std::endl;
			delay_time(SLEEP_SIGNIFICANT_ERR);
			continue;
		}
	}
	return;
}
void TTRM::MenuSel_DTask() noexcept
{
	while (PROCESS_AWAIT_CMPLT)
	{
		size_t TaskSize = TaskList.size();
		WinCall_CMD("CLS");
		if (TaskSize)
		{
			std::cout << std::endl
					  << "=== Task List Available ===============================" << std::endl;
			DisplayTasks_AtWindow(DeleteTask);
			std::cout << std::endl
					  << "Please Select A Task To Delete..." << std::endl;
			std::cout << "[Input] Task # or '0' To Go Back Menu |> ", std::cin >> handleInputInt;
			if (std::cin.fail())
			{
				std::cin.clear();
				CinBuffer_ClearOptpt('\n');
				std::cerr << "[Input Error] -> Value Received is Invalid. Please try again." << std::endl;
				delay_time(SLEEP_ERROR_PROMPT);
				continue;
			}
			else
			{
				if (handleInputInt)
				{
					if (handleInputInt <= TaskSize)
					{
						std::cout << std::endl
								  << "Are you sure you want to delete this task: '" << TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskName << "'?" << std::endl
								  << std::endl
								  << "[Input, Y or N] |> ",
							std::cin >> handleInputChar;
						if (std::cin.fail())
						{
							std::cin.clear();
							CinBuffer_ClearOptpt('\n');
							std::cerr << "[Input Error] -> Value Received is Invalid. Please try again." << std::endl;
						}
						else
						{
							switch (handleInputChar)
							{
							case CONFIRMED_TRUE_LOWER:
							case CONFIRMED_TRUE_UPPER:
								std::cout << "[Confirmation, Success] |> Task '" << TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskName << "' deleted." << std::endl;
								TaskList.erase(TaskList.begin() + (handleInputInt - POS_OFFSET_BY_ONE));
								delay_time(SLEEP_OPRT_FINISHED);
								continue;

							case CONFIRMED_FALSE_LOWER:
							case CONFIRMED_FALSE_UPPER:
								std::cout << "[Confirmation, Success] |> Task Modification Cancelled." << std::endl;
								delay_time(SLEEP_OPRT_FINISHED);
								continue;

							default:
								std::cout << "[Confirmation, Error] |> User Input Invalid." << std::endl;
								std::cin.clear();
								CinBuffer_ClearOptpt('\n');
								delay_time(SLEEP_OPRT_FAILED);
								continue;
							}
						}
					}
					else
					{
						std::cerr << "[Input Error] -> User Requested To Delete Tasks Non-Existent or Out of Range..." << std::endl;
						delay_time(SLEEP_ERROR_PROMPT);
						continue;
					}
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			std::cerr << "[View Info] > Task Queue is currently empty! Please add some task/s." << std::endl;
			delay_time(SLEEP_OPRT_FINISHED);
			break;
		}
	}
	return;
}
void TTRM::MenuSel_ETask() noexcept(false)
{
	while (PROCESS_AWAIT_CMPLT)
	{
		TTRM_TaskData NewModifiedTask; // Create Object To Pass On...
		tm TimeContainer;
		time_t TimeStampData = time(NULL);
		localtime_s(&TimeContainer, &TimeStampData);
		size_t TaskSize = TaskList.size();
		WinCall_CMD("CLS");
		if (TaskSize)
		{
			std::cout << std::endl
					  << "=== Task Lists ===========================================" << std::endl;
			DisplayTasks_AtWindow(EditTask);
			std::cout << std::endl
					  << "[Input] Please Select A Task # or '0' To Go Back Menu |> ",
				std::cin >> handleInputInt;
			if (std::cin.fail())
			{
				std::cin.clear();
				CinBuffer_ClearOptpt('\n');
				std::cerr << "[Input Error] -> Input Invalid. Please try again." << std::endl;
				delay_time(SLEEP_ERROR_PROMPT);
				continue;
			}
			else
			{
				if (handleInputInt)
				{
					if (handleInputInt <= TaskSize)
					{
						std::cout << "[WARNING] |> Are you sure you want to edit this task: '" << TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskName << "'?" << std::endl
								  << "[INPUT  ] | ['Y'es or 'N'o] |> ",
							std::cin >> handleInputChar;
						if (std::cin.fail())
						{
							std::cerr << "[Input Error] -> Value Received is Invalid. Please try again." << std::endl;
							std::cin.clear();
							CinBuffer_ClearOptpt('\n');
						}
						else
						{
							switch (handleInputChar)
							{
							case CONFIRMED_TRUE_LOWER:
							case CONFIRMED_TRUE_UPPER:
								CinBuffer_ClearOptpt('\n');
								std::cout << "[Required] Name of the Task, Put '0' To Retain Changes |> ", std::getline(std::cin, NewModifiedTask.TaskName);
								if (NewModifiedTask.TaskName != "0")
								{
									if (NewModifiedTask.TaskName.length() <= MIN_CHAR_TASKNAME || std::cin.fail())
									{
										std::cin.clear();
										std::cerr << "[INPUT ERR] |> TaskName Character Is Not Enough. Press Enter Key To Try Again." << std::endl;
										CinBuffer_ClearOptpt('\n');
										continue;
									}
								}
								std::cout << "[Required] Name of Person In Charge, Put '0' To Retain Changes |> ", std::getline(std::cin, NewModifiedTask.TaskInCharge);
								if (NewModifiedTask.TaskInCharge != "0")
								{
									if (NewModifiedTask.TaskInCharge.length() < MIN_CHAR_INCHARGE || std::cin.fail())
									{
										std::cin.clear();
										std::cerr << "[INPUT ERR] |> Task In Charge Character Is Not Enough. Press Enter Key To Try Again." << std::endl;
										CinBuffer_ClearOptpt('\n');
										continue;
									}
								}
								std::cout << "[Required, 1 = Continous, 2 = Time-Based] Type of Reminder, Put 0 To Retain Changes |> ", std::cin >> NewModifiedTask.ReminderType;
								if (NewModifiedTask.ReminderType)
								{
									if (NewModifiedTask.ReminderType < RemindContinous || NewModifiedTask.ReminderType > RemindTimeBased || std::cin.fail())
									{
										std::cin.clear();
										std::cerr << "[INPUT ERR] |> Reminder Type Input is Invalid. Press Any Key To Try Again." << std::endl;
										CinBuffer_ClearOptpt('\n');
										_getche();
										continue;
									}
								}
								std::cout << "[Req, Seperate by Space | YYYY MM DD] Task Start Point, Put 0000 00 00 To Retain Changes |> ", std::cin >> NewModifiedTask.DateStartTime.tm_year >> NewModifiedTask.DateStartTime.tm_mon >> NewModifiedTask.DateStartTime.tm_mday;
								if ((NewModifiedTask.DateStartTime.tm_year != 0 && NewModifiedTask.DateStartTime.tm_mon != 0 && NewModifiedTask.DateStartTime.tm_mday != 0))
								{
									if (NewModifiedTask.DateStartTime.tm_year < (TimeContainer.tm_year + START_CTIME) || (NewModifiedTask.DateStartTime.tm_mon < MIN_TIME_MONTH || NewModifiedTask.DateStartTime.tm_mon > MAX_TIME_MONTH || NewModifiedTask.DateStartTime.tm_mon < TimeContainer.tm_mon) || (NewModifiedTask.DateStartTime.tm_mday < MIN_TIME_DAY || NewModifiedTask.DateStartTime.tm_mday > MAX_TIME_DAY || NewModifiedTask.DateStartTime.tm_mday < TimeContainer.tm_mday) || std::cin.fail())
									{
										std::cin.clear();
										std::cerr << "[INPUT ERR] |> Start Date Parameters is either invalid, less or exceed from expected value. Press Any Key To Try Again." << std::endl;
										CinBuffer_ClearOptpt('\n');
										_getche();
										continue;
									}
								}
								std::cout << "[Req, Seperate by Space | YYYY MM DD] Task End Point, Put 0000 00 00 To Retain Changes |> ", std::cin >> NewModifiedTask.DateEndTime.tm_year >> NewModifiedTask.DateEndTime.tm_mon >> NewModifiedTask.DateEndTime.tm_mday;
								if ((NewModifiedTask.DateEndTime.tm_year != 0 && NewModifiedTask.DateEndTime.tm_mon != 0 && NewModifiedTask.DateEndTime.tm_mday != 0))
								{
									if (NewModifiedTask.DateEndTime.tm_year < NewModifiedTask.DateStartTime.tm_year || (NewModifiedTask.DateEndTime.tm_mon < MIN_TIME_MONTH || NewModifiedTask.DateEndTime.tm_mon > MAX_TIME_MONTH || NewModifiedTask.DateEndTime.tm_mon < NewModifiedTask.DateStartTime.tm_mon) || (NewModifiedTask.DateEndTime.tm_mday < MIN_TIME_DAY || NewModifiedTask.DateEndTime.tm_mday > MAX_TIME_DAY || NewModifiedTask.DateEndTime.tm_mday < NewModifiedTask.DateStartTime.tm_mday) || std::cin.fail())
									{
										std::cin.clear();
										std::cerr << "[INPUT ERR] |> End Date Parameters is either invalid, less or exceed from expected value. Press Any Key To Try Again." << std::endl;
										CinBuffer_ClearOptpt('\n');
										_getche();
										continue;
									}
								}
								std::cout << "[Req, Seperate by Space | 00 00-23 59] Time To Remind You, Put The Same Time To Retain Changes |> ", std::cin >> NewModifiedTask.TimeTrigger.tm_hour >> NewModifiedTask.TimeTrigger.tm_min;
								if ((NewModifiedTask.TimeTrigger.tm_hour < MIN_TIME_HOUR || NewModifiedTask.TimeTrigger.tm_hour > MAX_TIME_HOUR) || (NewModifiedTask.TimeTrigger.tm_min < MIN_TIME_MIN || NewModifiedTask.TimeTrigger.tm_min > MAX_TIME_MIN) || std::cin.fail())
								{
									std::cin.clear();
									std::cerr << "[INPUT ERR] |> Time Input is Invalid. Keep in mind that I need 24 hour format. Press Any Key To Try Again." << std::endl;
									CinBuffer_ClearOptpt('\n');
									_getche();
									continue;
								}
								std::cout << "[Opt, 0-180] Notification EarlyTime, By Minutes, Put 0 To Retain Changes |> ", std::cin >> NewModifiedTask.NotifierOffset;
								if (NewModifiedTask.NotifierOffset)
								{
									if (NewModifiedTask.NotifierOffset < MIN_EARLYTIME || NewModifiedTask.NotifierOffset > MAX_EARLYTIME || std::cin.fail())
									{
										std::cin.clear();
										std::cerr << "[INPUT ERR] |> Early Time Input is Invalid. Press Enter Key To Try Again." << std::endl;
										CinBuffer_ClearOptpt('\n');
										_getche();
										continue;
									}
								}
								try
								{
									(NewModifiedTask.TaskName != "0") ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskName.assign(NewModifiedTask.TaskName) : DO_NOTHING;
									(NewModifiedTask.TaskInCharge != "0") ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskInCharge.assign(NewModifiedTask.TaskInCharge) : DO_NOTHING;
									(NewModifiedTask.ReminderType) ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderType = NewModifiedTask.ReminderType : DO_NOTHING;
									(NewModifiedTask.DateStartTime.tm_year != 0) ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).DateStartTime.tm_year = NewModifiedTask.DateStartTime.tm_year : DO_NOTHING;
									(NewModifiedTask.DateStartTime.tm_mon != 0) ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).DateStartTime.tm_mon = NewModifiedTask.DateStartTime.tm_mon : DO_NOTHING;
									(NewModifiedTask.DateStartTime.tm_mday != 0) ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).DateStartTime.tm_mday = NewModifiedTask.DateStartTime.tm_mday : DO_NOTHING;
									(NewModifiedTask.DateEndTime.tm_year != 0) ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).DateEndTime.tm_year = NewModifiedTask.DateEndTime.tm_year : DO_NOTHING;
									(NewModifiedTask.DateEndTime.tm_year != 0) ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).DateEndTime.tm_mon = NewModifiedTask.DateEndTime.tm_mon : DO_NOTHING;
									(NewModifiedTask.DateEndTime.tm_year != 0) ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).DateEndTime.tm_mday = NewModifiedTask.DateEndTime.tm_mday : DO_NOTHING;
									TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TimeTrigger.tm_hour = NewModifiedTask.TimeTrigger.tm_hour;
									TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TimeTrigger.tm_min = NewModifiedTask.TimeTrigger.tm_min;
									(NewModifiedTask.NotifierOffset) ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).NotifierOffset = NewModifiedTask.NotifierOffset: DO_NOTHING;

									std::cout << "[Confirmation, Success] |> Task Changes @ '" << TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskName << "' is now applied." << std::endl;
									delay_time(SLEEP_OPRT_FINISHED);
									continue;
								}
								catch (...)
								{
									std::cout << std::endl
											  << "[PROCESS] Unknown error has occured..." << std::endl;
									delay_time(SLEEP_SIGNIFICANT_ERR);
									continue;
								}
							case CONFIRMED_FALSE_LOWER:
							case CONFIRMED_FALSE_UPPER:
								std::cout << "[Confirmation, Success] |> Task Deletion Cancelled." << std::endl;
								delay_time(SLEEP_OPRT_FINISHED);
								continue;

							default:
								std::cout << "[Confirmation, Error] |> User Input Invalid." << std::endl;
								std::cin.clear();
								CinBuffer_ClearOptpt('\n');
								delay_time(SLEEP_OPRT_FAILED);
								continue;
							}
						}
					}
					else
					{
						std::cerr << "[Input Error] -> User Requested To Delete Tasks Non-Existent or Out of Range..." << std::endl;
						delay_time(SLEEP_ERROR_PROMPT);
						continue;
					}
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			std::cerr << "[View Info] > Task Queue is currently empty! Please add some task/s." << std::endl;
			delay_time(SLEEP_OPRT_FINISHED);
			break;
		}
	}
	return;
}
void TTRM::MenuSel_VTask() noexcept(false)
{
	while (PROCESS_AWAIT_CMPLT)
	{
		WinCall_CMD("CLS");
		//std::cout << std::endl
		//		  << "Here are the tasks currently in line with the system..." << std::endl;
		DisplayTasks_AtWindow(ViewTask);
		std::cout << "Press any key to go back." << std::endl;
		_getche();
		break;
	}
	return;
}

void TTRM::MenuSel_SQT() noexcept(false)
{
	;
}
void TTRM::MenuSel_RQT() noexcept(false)
{
	if (TaskList.size())
	{
		std::cout << std::endl
				  << "[WARNING] |> Are you sure you want delete tasks in queue?" << std::endl
				  << "[WARNING] |> All task can be restored if the database still contains all data." << std::endl
				  << "[INPUT  ] | ['Y'es or 'N'o] |> ",
			std::cin >> handleInputChar;
		switch (handleInputChar)
		{
		case CONFIRMED_TRUE_LOWER:
		case CONFIRMED_TRUE_UPPER:
			TaskList.clear();
			std::cout << "[PROCESS] |> All Task from Queue Removed!" << std::endl;
			delay_time(SLEEP_OPRT_FINISHED);
			break;
		case CONFIRMED_FALSE_LOWER:
		case CONFIRMED_FALSE_UPPER:
			std::cout << "[PROCESS] |> All Task Deletion Operation Cancelled." << std::endl;
			delay_time(SLEEP_OPRT_FINISHED);
			break;
		default:
			std::cin.clear();
			CinBuffer_ClearOptpt('\n');
			std::cout << "[ERROR  ] |> Invalid Input. All Task Deletion Operation Cancelled." << std::endl;
			delay_time(SLEEP_OPRT_FINISHED);
			break;
		}
		return;
	}
	else
	{
		std::cerr << std::endl
				  << "[INFORM ] Your Task List is empty! Please add one." << std::endl;
		delay_time(SLEEP_OPRT_FINISHED);
		return;
	}
}

void TTRM::MenuSel_RCT() noexcept(false)
{
	;
}
void TTRM::MenuSel_CS() const noexcept(false)
{
	;
}
void TTRM::MenuSel_MRI() const noexcept(false)
{
	;
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