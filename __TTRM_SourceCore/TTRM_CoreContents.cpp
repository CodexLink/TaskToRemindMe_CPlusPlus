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
	std::cout << "Quick Tasks To Remind Me C++ in CLI version. BETA" << std::endl
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
		SetConsoleTitle("Quick Tasks To Remind Me | C++ | Early BETA // github.com/CodexLink");
		GetClientRect(console, &ConsoleWindow);
		GetWindowRect(console, &ClietnScrWindow);
		posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (ClietnScrWindow.right - ClietnScrWindow.left) / 2,
		posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (ClietnScrWindow.bottom - ClietnScrWindow.top) / 2,
		MoveWindow(console, posx, posy, ClietnScrWindow.right - ClietnScrWindow.left, (ClietnScrWindow.bottom - ClietnScrWindow.top) * 1.3, TRUE);
		//MoveWindow(console, ConsoleMainApp.left, ConsoleMainApp.top, 1000, 500, TRUE);

		EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
		std::cout << "Component Checking Point | Before Program Initialization" << std::endl << std::endl
				  << "WinToast Library |> Checking Compatibility...";
		if (WinToast::isCompatible())
		{
			std::cout << std::endl
					  << "WinToast Library |> Compatible. Setting Up Parameters..." << std::endl;
			WinToast::instance()->setAppName(L"Quick Tasks To Remind Me C++ CLI");
			WinToast::instance()->setAppUserModelId(WinToast::configureAUMI(L"Data Struct Group 5", L"Quick Tasks To Remind Me", L"QTRM C++", L"Early Beta Stage"));
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
		std::cout << std::endl
				  << "Quick Tasks To Remind Me C++ in CLI version. BETA" << std::endl
				  << std::endl;
		// Create function for String To Time here.

		std::cout << "Last Time Frame From Your Local System |> " << runSystem_GetTimeLocal() << std::endl;
		std::cout << std::endl
				  << "=== List of Task/s, Sorted by Date Time ================" << std::endl;
		DisplayTasks_AtWindow(AtHome);
		std::cout << std::endl
				  << "=== Basic Tasks Functions ======================================" << std::endl
				  << std::endl
				  << "1 |> Add a Task" << std::endl
				  << "2 |> Delete a Task/s" << std::endl
				  << "3 |> Edit / Modify an Existing Task/s" << std::endl
				  << "4 |> View All Tasks" << std::endl
				  << "5 |> Sort All Tasks By Starting Date" << std::endl
				  << "6 |> Remove All Tasks" << std::endl
				  << std::endl
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

std::string TTRM::DisplayItem_ParseType(REMINDER_TYPES IntType) noexcept
{
	switch (IntType)
	{
	case CancelOperation:
		return "ERROR";
		break;
	case QuickRemind:
		return "Quick Reminder";
		break;
	case DateBasedRemind:
		return "Date Based Reminder";
		break;
	default:
		return "ERROR";
	}
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

		case AtHome:
			isAtHome = true;
			std::cout << " for today~!" << std::endl
					  << std::endl;
			break;
		default:
			std::cerr << "... ???" << std::endl;
		}
		// ! This function is degrading grade of code quality due to completixty. Try to do some method to reduce this.
		// TODO: Normalize This Function.
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
				std::cout << "Task #" << TaskNum << " | ";

				switch (IterTasks.ReminderType)
				{
				case QuickRemind:
					// ! Done
					std::cout << DisplayItem_ParseType((TTRM::REMINDER_TYPES)IterTasks.ReminderType) << " |> " << IterTasks.TaskName << " | In Charge: " << IterTasks.TaskInCharge << ", Trigger Time at " << std::setfill('0') << std::setw(2) << IterTasks.RemindTime.tm_hour << ":" << std::setfill('0') << std::setw(2) << IterTasks.RemindTime.tm_min << std::endl;
					break;

				case DateBasedRemind:
					// ! Done
					std::cout << DisplayItem_ParseType((TTRM::REMINDER_TYPES)IterTasks.ReminderType) << " |> " << IterTasks.TaskName << " | In Charge |> " << IterTasks.TaskInCharge << ", Date and Time Trigger |> " << std::setfill('0') << std::setw(2) << IterTasks.TargetDateTime.tm_mon << "/" << std::setfill('0') << std::setw(2) << IterTasks.TargetDateTime.tm_mday << "/" << std::setfill('0') << std::setw(2) << IterTasks.TargetDateTime.tm_year << ", " << std::setfill('0') << std::setw(2) << IterTasks.TargetDateTime.tm_hour << ":" << std::setfill('0') << std::setw(2) << IterTasks.TargetDateTime.tm_sec << std::endl;
					break;

				default:
					break;
				}
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
	StrTime << TimeStorage.tm_mon + POS_OFFSET_BY_ONE << "/" << std::setfill('0') << std::setw(2) << TimeStorage.tm_mday << "/" << std::setfill('0') << std::setw(2) << (TimeStorage.tm_year + START_CTIME) << " | " << std::setfill('0') << std::setw(2) << TimeStorage.tm_hour << ":" << std::setfill('0') << std::setw(2) << TimeStorage.tm_min << ":" << std::setfill('0') << std::setw(2) << TimeStorage.tm_sec;
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
	//std::wstring TaskCount = std::to_wstring(TaskList.size());
	std::wstring WelcomeFirstPT = L"Hello User, Welcome To Quick Task Remind Me System~!";
	//std::wstring WelcomeSecondPT = (TaskList.size() <= BY_ONE_OR_LESS) ? L" task" : L"tasks";
	//std::wstring WelcomeThirdPT = L" for today.";
	TaskCountShow.setTextField(PROJECT_NAME, WinToastTemplate::FirstLine);
	TaskCountShow.setTextField(WelcomeFirstPT /*+ TaskCount + WelcomeSecondPT + WelcomeThirdPT*/, WinToastTemplate::SecondLine);
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
	time_t CompareUserDate = INIT_NULL_INT, CompareStoredDate = INIT_NULL_INT;
	short int ObjIterateNum = INIT_NULL_INT;
	double diffDateHandler = INIT_NULL_INT;
	while (PROCESS_AWAIT_CMPLT)
	{
		TTRM_TaskData NewTask; // Create Object To Pass On...
		time_t CurrentDateTime = time(NULL);
		tm *CurrentTContainer = localtime(&CurrentDateTime);
		WinCall_CMD("CLS");

		std::cout << "[Required] Name of the Task, Input --CANCEL to Quit Insertion. |> ", std::getline(std::cin, NewTask.TaskName);

		if (NewTask.TaskName.length() < MIN_CHAR_TASKNAME || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> TaskName Character Is Not Enough. Press Enter Key To Try Again." << std::endl;
			CinBuffer_ClearOptpt('\n');
			continue;
		}
		else if (NewTask.TaskName == "--CANCEL")
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> New Task Insertion Operation is Cancelled by User..." << std::endl;
			delay_time(SLEEP_OPRT_FINISHED);
			return;
		}

		std::cout << "[Required] Name of Person In Charge, Input --CANCEL to Quit Insertion. |> ", std::getline(std::cin, NewTask.TaskInCharge);

		if (NewTask.TaskInCharge.length() < MIN_CHAR_INCHARGE || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> Task In Charge Character Is Not Enough. Press Enter Key To Try Again." << std::endl;
			CinBuffer_ClearOptpt('\n');
			continue;
		}
		else if (NewTask.TaskInCharge == "--CANCEL")
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> New Task Insertion Operation is Cancelled by User..." << std::endl;
			delay_time(SLEEP_OPRT_FINISHED);
			return;
		}

		std::cout << "[Req, 0 = To Cancel, 1 = Quick Remind, 2 = Date-Based]"
				  << " |> Type of Reminder |> ",
			std::cin >> NewTask.ReminderType;

		if (NewTask.ReminderType < CancelOperation || NewTask.ReminderType > DateBasedRemind || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> Reminder Type Input is Invalid. Press Any Key To Try Again." << std::endl;
			CinBuffer_ClearOptpt('\n');
			_getche();
			continue;
		}
		else
		{
			switch (NewTask.ReminderType)
			{
			case CancelOperation:
				std::cerr << "[INPUT ERR] |> New Task Insertion Operation is Cancelled by User..." << std::endl;
				delay_time(SLEEP_OPRT_FINISHED);
				return;

			case QuickRemind:
				std::cout << "[Required, Min: 1, Max: 180] Minutes Left To Remind You |> ", std::cin >> NewTask.NotifyByTime;
				// TODO: Convert to time_t by mktime and return back to date time/. Done. Test Left.
				if (NewTask.NotifyByTime <= MIN_TIMELEFT || NewTask.NotifyByTime > MAX_TIMELEFT)
				{
					std::cerr << "[INPUT ERR] |> Time Entered is invalid. Please try again by pressing any key to restart." << std::endl;
					CinBuffer_ClearOptpt('\n');
					_getche();
					continue;
				}
				else
				{
					// * Test Done. Success.
					CurrentDateTime = time(0) + (60 * NewTask.NotifyByTime);
					NewTask.TempTM = localtime(&CurrentDateTime);
					NewTask.TempTM->tm_year += 1900;
					NewTask.TempTM->tm_mon += 1;
					NewTask.RemindTime = *NewTask.TempTM;
					break;
				}

			case DateBasedRemind:
				CurrentDateTime = time(NULL);
				CurrentTContainer = localtime(&CurrentDateTime), CurrentTContainer->tm_year += 1900, CurrentTContainer->tm_mon += 1;

				std::cout << "[Req, Seperate by Space | YYYY MM DD] Target Date of Reminding |> ", std::cin >> NewTask.TargetDateTime.tm_year >> NewTask.TargetDateTime.tm_mon >> NewTask.TargetDateTime.tm_mday;

				if (NewTask.TargetDateTime.tm_year < CurrentTContainer->tm_year)
				{
					std::cin.clear();
					std::cerr << "[INPUT ERR] |> Target Year Parameter is either invalid or less from current date. Press Any Key To Try Again." << std::endl;
					CinBuffer_ClearOptpt('\n');
					_getche();
					continue;
				}
				else
				{
					if (NewTask.TargetDateTime.tm_mon < MIN_TIME_MONTH || NewTask.TargetDateTime.tm_mon > MAX_TIME_MONTH || NewTask.TargetDateTime.tm_mon < CurrentTContainer->tm_mon || std::cin.fail())
					{
						std::cin.clear();
						std::cerr << "[INPUT ERR] |> Target Month Parameter is either invalid or less from current date. Press Any Key To Try Again." << std::endl;
						CinBuffer_ClearOptpt('\n');
						_getche();
						continue;
					}
					else
					{
						if (NewTask.TargetDateTime.tm_mday < MIN_TIME_DAY || NewTask.TargetDateTime.tm_mday > MAX_TIME_DAY || (NewTask.TargetDateTime.tm_year == CurrentTContainer->tm_year && NewTask.TargetDateTime.tm_mon == CurrentTContainer->tm_mon && (NewTask.TargetDateTime.tm_mday < CurrentTContainer->tm_mday)) || std::cin.fail())
						{
							// ! If same month, check day.
							std::cin.clear();
							std::cerr << "[INPUT ERR] |> Target Day Parameter is either invalid or less from current date. Press Any Key To TryAgain." << std::endl;
							CinBuffer_ClearOptpt('\n');
							_getche();
							continue;
						}
					}
					std::cout << "[Req, Seperate by Space | 00:00 - 23:59] Time To Remind You |> ", std::cin >> NewTask.TargetDateTime.tm_hour >> NewTask.TargetDateTime.tm_min;

					// ! Add Some Today To Today Sens Time. Currently WORK ON PROGRESS.
					if ((NewTask.TargetDateTime.tm_hour > MIN_TIME_HOUR || NewTask.TargetDateTime.tm_hour <= MAX_TIME_HOUR) || (NewTask.TargetDateTime.tm_min >= MIN_TIME_MIN || NewTask.TargetDateTime.tm_min <= MAX_TIME_MIN) || !std::cin.fail())
					{

						// ! Prerequisite Condition, we can only get to this point if and only the datetime is exactly the same as the user added. Means 09/24/2019 == 09/24/2019. If we intend to have same date but different year then we go to else statement.

						if (NewTask.TargetDateTime.tm_year == CurrentTContainer->tm_year && (NewTask.TargetDateTime.tm_mon == CurrentTContainer->tm_mon && NewTask.TargetDateTime.tm_mday == CurrentTContainer->tm_mday))
						{

							// ! Prerequisite Condition, if the datetime is exactly the same as the user added. Means 09/24/2019 == 09/24/2019. We check if the latest time is added by the user greater or less than.
							// * Exactly done conditioning.

							if (NewTask.TargetDateTime.tm_hour >= CurrentTContainer->tm_hour)
							{
								if (NewTask.TargetDateTime.tm_min < CurrentTContainer->tm_min)
								{
									std::cerr << "[INPUT ERR] |> Time Minute is Less Than the Expected Day. Please Try Again." << std::endl;
									CinBuffer_ClearOptpt('\n');
									_getche();
									continue;
								}
								else
								{
									break;
								}
							}
							else
							{
								std::cerr << "[INPUT ERR] |> Time Hour is Lesser Than Expected Hour. Please Try Again." << std::endl;
								CinBuffer_ClearOptpt('\n');
								_getche();
								continue;
							}
						}
						else
						{
							// ! We proceed as there will be no conflict at timing.
							break;
						}
					}
					else
					{
						std::cin.clear();
						std::cerr << "[INPUT ERR] |> Time Input is Invalid. Keep in mind that I need 24 hour format. Press Any Key To Try Again." << std::endl;
						CinBuffer_ClearOptpt('\n');
						_getche();
						continue;
					}
					break;
				}
			default:
				std::cout << "Error" << std::endl;
				system("pause");
				continue;
			}

			try
			{
				if (!TaskList.size())
				{
					TaskList.push_front(NewTask);
				}
				else
				{
					TaskList.push_back(NewTask);
				}
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
		time_t CurrentDateTime = time(NULL);
		tm *CurrentTContainer = localtime(&CurrentDateTime);
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
								std::cout << "[Required, 1 = Quick Remind, 2 = Date-Based] Type of Reminder, Put 0 To Retain Changes |> ", std::cin >> NewModifiedTask.ReminderType;
								if (NewModifiedTask.ReminderType)
								{
									if (NewModifiedTask.ReminderType < QuickRemind || NewModifiedTask.ReminderType > DateBasedRemind || std::cin.fail())
									{
										std::cin.clear();
										std::cerr << "[INPUT ERR] |> Reminder Type Input is Invalid. Press Any Key To Try Again." << std::endl;
										CinBuffer_ClearOptpt('\n');
										_getche();
										continue;
									}
								}

								switch (NewModifiedTask.ReminderType)
								{
								case QuickRemind:
									std::cout << "[Required, Min: -180, Max: 180, 0 To Retain] Minutes Left To Remind You |> ", std::cin >> NewModifiedTask.NotifyByTime;
									// TODO: Convert to time_t by mktime and return back to date time/. Done. Test Left.
									if (NewModifiedTask.NotifyByTime < -180 || NewModifiedTask.NotifyByTime > MAX_TIMELEFT)
									{
										std::cerr << "[INPUT ERR] |> Time Entered is invalid. Please try again by pressing any key to restart." << std::endl;
										CinBuffer_ClearOptpt('\n');
										_getche();
										continue;
									}
									else
									{
										if (NewModifiedTask.NotifyByTime)
										{
											// * Test Done. Success.
											CurrentDateTime = time(0) + (60 * NewModifiedTask.NotifyByTime);
											NewModifiedTask.TempTM = localtime(&CurrentDateTime);
											NewModifiedTask.TempTM->tm_year += 1900;
											NewModifiedTask.TempTM->tm_mon += 1;
											//NewModifiedTask.RemindTime = *NewModifiedTask.TempTM;
											break;
										}
									}
								case DateBasedRemind:
									CurrentDateTime = time(NULL);
									CurrentTContainer = localtime(&CurrentDateTime), CurrentTContainer->tm_year += 1900, CurrentTContainer->tm_mon += 1;

									std::cout << "[Req, Seperate by Space | YYYY MM DD] Target Date of Reminding, Type 0 For Each To Retain |> ", std::cin >> NewModifiedTask.TargetDateTime.tm_year >> NewModifiedTask.TargetDateTime.tm_mon >> NewModifiedTask.TargetDateTime.tm_mday;

									if (NewModifiedTask.TargetDateTime.tm_year < TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_year)
									{
										std::cin.clear();
										std::cerr << "[INPUT ERR] |> Target Year Parameter is either invalid or less from current date. Press Any Key To Try Again." << std::endl;
										CinBuffer_ClearOptpt('\n');
										_getche();
										continue;
									}
									else
									{
										if (NewModifiedTask.TargetDateTime.tm_mon < MIN_TIME_MONTH || NewModifiedTask.TargetDateTime.tm_mon > MAX_TIME_MONTH || NewModifiedTask.TargetDateTime.tm_mon < TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_mon || std::cin.fail())
										{
											std::cin.clear();
											std::cerr << "[INPUT ERR] |> Target Month Parameter is either invalid or less from current date. Press Any Key To Try Again." << std::endl;
											CinBuffer_ClearOptpt('\n');
											_getche();
											continue;
										}
										else
										{
											if (NewModifiedTask.TargetDateTime.tm_mday < MIN_TIME_DAY || NewModifiedTask.TargetDateTime.tm_mday > MAX_TIME_DAY || (NewModifiedTask.TargetDateTime.tm_year == TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_year && NewModifiedTask.TargetDateTime.tm_mon == TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_mon && (NewModifiedTask.TargetDateTime.tm_mday < TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_mday)) || std::cin.fail())
											{
												// ! If same month, check day.
												std::cin.clear();
												std::cerr << "[INPUT ERR] |> Target Day Parameter is either invalid or less from current date. Press Any Key To TryAgain." << std::endl;
												CinBuffer_ClearOptpt('\n');
												_getche();
												continue;
											}
										}
										std::cout << "[Req, Seperate by Space | 00:00 - 23:59] Time To Remind You |> ", std::cin >> NewModifiedTask.TargetDateTime.tm_hour >> NewModifiedTask.TargetDateTime.tm_min;

										// ! Add Some Today To Today Sens Time. Currently WORK ON PROGRESS.
										if ((NewModifiedTask.TargetDateTime.tm_hour > MIN_TIME_HOUR || NewModifiedTask.TargetDateTime.tm_hour <= MAX_TIME_HOUR) || (NewModifiedTask.TargetDateTime.tm_min >= MIN_TIME_MIN || NewModifiedTask.TargetDateTime.tm_min <= MAX_TIME_MIN) || !std::cin.fail())
										{

											// ! Prerequisite Condition, we can only get to this point if and only the datetime is exactly the same as the user added. Means 09/24/2019 == 09/24/2019. If we intend to have same date but different year then we go to else statement.

											if (NewModifiedTask.TargetDateTime.tm_year == TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_year && (NewModifiedTask.TargetDateTime.tm_mon == TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_mon && NewModifiedTask.TargetDateTime.tm_mday == TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_mday))
											{

												// ! Prerequisite Condition, if the datetime is exactly the same as the user added. Means 09/24/2019 == 09/24/2019. We check if the latest time is added by the user greater or less than.
												// * Exactly done conditioning.

												if (NewModifiedTask.TargetDateTime.tm_hour >= TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_hour)
												{
													if (NewModifiedTask.TargetDateTime.tm_min < TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_min)
													{
														std::cerr << "[INPUT ERR] |> Time Minute is Less Than the Expected Day. Please Try Again." << std::endl;
														CinBuffer_ClearOptpt('\n');
														_getche();
														continue;
													}
													else
													{
														break;
													}
												}
												else
												{
													std::cerr << "[INPUT ERR] |> Time Hour is Lesser Than Expected Hour. Please Try Again." << std::endl;
													CinBuffer_ClearOptpt('\n');
													_getche();
													continue;
												}
											}
											else
											{
												// ! We proceed as there will be no conflict at timing.
												break;
											}
										}
										else
										{
											std::cin.clear();
											std::cerr << "[INPUT ERR] |> Time Input is Invalid. Keep in mind that I need 24 hour format. Press Any Key To Try Again." << std::endl;
											CinBuffer_ClearOptpt('\n');
											_getche();
											continue;
										}
										break;
									}
									break;
								}
								try
								{
									if (NewModifiedTask.TaskName != "0")
										TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskName.assign(NewModifiedTask.TaskName);

									if (NewModifiedTask.TaskInCharge != "0")
										TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskInCharge.assign(NewModifiedTask.TaskInCharge);

									if (NewModifiedTask.ReminderType != TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderType)
										TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderType = NewModifiedTask.ReminderType;

									switch (NewModifiedTask.ReminderType)
									{
									// ! Clear Some Other Variable When That CASE is not using that variable.
									case QuickRemind:
										if (NewModifiedTask.NotifyByTime != 0)
										{
											TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).RemindTime = *NewModifiedTask.TempTM;
											TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime = {0};
											break;
										}

									case DateBasedRemind:
										(NewModifiedTask.TargetDateTime.tm_year != 0) ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_year = NewModifiedTask.TargetDateTime.tm_year : DO_NOTHING;
										(NewModifiedTask.TargetDateTime.tm_mon != 0) ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_mon = NewModifiedTask.TargetDateTime.tm_mon : DO_NOTHING;
										(NewModifiedTask.TargetDateTime.tm_mday != 0) ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_mday = NewModifiedTask.TargetDateTime.tm_mday : DO_NOTHING;

										(NewModifiedTask.TargetDateTime.tm_hour != 0) ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_hour = NewModifiedTask.TargetDateTime.tm_hour : DO_NOTHING;
										(NewModifiedTask.TargetDateTime.tm_min != 0) ? TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TargetDateTime.tm_min = NewModifiedTask.TargetDateTime.tm_min : DO_NOTHING;

										TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).RemindTime = {0};
										break;
									}

									std::cout << "[Confirmation, Success] |> Task Modification @ '" << TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskName << "' is now applied~!" << std::endl;
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
	/*
	Potential Deprecation.
	try
	{
		sort(TaskList.begin(), TaskList.end(), TaskSort_Handler);
	}
	catch (...)
	{
		std::cerr << "[Error] Cannot sort objects. Unknown Detailed Error." << std::endl;
	}
	*/
}

void TTRM::MenuSel_RQT() noexcept(false)
{
	if (TaskList.size())
	{
		std::cout << std::endl
				  << "[WARNING] |> Are you sure you want delete all tasks in queue system?" << std::endl
				  << "[WARNING] |> All task can be restored if the database still contains all data you just deleted." << std::endl
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