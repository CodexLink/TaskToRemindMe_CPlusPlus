/*
	# Task To Remind Me Core Definitions | TTRM_CoreDef.cpp
    # File Category Type: Core Function Body Definition
	# Version: Version Post.06042020.1955

	# Created by Janrey Licas | http://github.com/CodexLink
	! Licensed in GPL-3.0 | See LICENSE.md for more information.
*/

#include "TTRM_CoreDecl.h"

// # Might be fixed later about this one.
// ! Force Requiring Non-Class Variables, These Variables are declared to reduce insanity while working on them.

volatile std::deque<struct TASK_DATALIST> TaskList;
unsigned short WinToast_ReturnTrigger;

std::string TTRM::Gen_UniqueRID() noexcept(true)
{
	std::string GeneratedID = NULL_STR;
	srand((unsigned int)time(NULL));
	for (unsigned short IterHandler_UnShort = INIT_BASE_NUM; IterHandler_UnShort < RAND_MAXID_LENGTH; IterHandler_UnShort++)
	{
		GeneratedID += AlphaNumConst[rand() % RAND_MODULO_VAL];
	}
	return GeneratedID;
}

unsigned __stdcall TTRM::MultiThread_Wrapper(void *DataReserved)
{
	HANDLE MultiThreadWrapper = NULL;
	while (CONTINOUS_RNN_PROC)
	{
		MultiThreadWrapper = (HANDLE)_beginthreadex(0, 0, &TTRM::MultiThread_ScanReminders, 0, 0, 0);
		WaitForSingleObject(MultiThreadWrapper, INFINITE);
		DelayRunTimeBy(WAIT_STARTTHREAD);
	}
	return THREAD_OOS;
}

unsigned __stdcall TTRM::MultiThread_ScanReminders(void *ArgsReserved)
{
	auto ObjectScanIter = INIT_BASE_NUM;
	// ! Redeclaration Since This Function is Static, I don't want to take more time to inherit class to static function member.
	const char *SaveStatePath_WT = "TTRM_SaveState._ttrmdat";
	const char *FilePointState_WT = "TTRM_SaveStatesTemp._ttrmdat";
	if (TaskList.size())
	{
		for (ObjectScanIter = INIT_BASE_NUM; ObjectScanIter < TaskList.size(); ObjectScanIter++)
		{
			if (mktime(&TaskList.at(ObjectScanIter).ReminderData) <= time(NULL))
			{
				WinToast_ReturnTrigger = INIT_BASE_NUM;
				WinToast_ReminderPrompt(TaskList.at(ObjectScanIter).TaskName, TaskList.at(ObjectScanIter).TaskInCharge, TaskList.at(ObjectScanIter).ReminderType, TaskList.at(ObjectScanIter).NotifyByTime, TaskList.at(ObjectScanIter).ReminderData);
				while (THREAD_AWAIT_CMPLT)
				{
					if (WinToast_ReturnTrigger == SNOOZE_REMINDER)
					{
						time_t CurrentTime = mktime(&TaskList.at(ObjectScanIter).ReminderData) + ((MAX_TIME_MIN + ADJUST_BY_ONE) * SNOOZE_TIME);
						tm *TempIncrementer = localtime(&CurrentTime);
						TaskList.at(ObjectScanIter).ReminderData = *TempIncrementer;
						return THREAD_PRC_TERM;
					}
					else if (WinToast_ReturnTrigger == DISCARD_REMINDER)
					{
						std::fstream WinToast_StateHandler;
						std::fstream WinToast_TempStateHandler;
						std::vector<std::string> WinToast_PayloadHandler;
						std::string WinToast_DicedData, WinToast_DataLine;

						WinToast_StateHandler.open(SaveStatePath_WT, std::ios::in);
						WinToast_TempStateHandler.open(FilePointState_WT, std::ios::out);

						while (!WinToast_StateHandler.eof() && std::getline(WinToast_StateHandler, WinToast_DataLine))
						{
							WinToast_PayloadHandler.clear();
							std::stringstream TempDataHandler(WinToast_DataLine);

							for (WinToast_DataLine; std::getline(TempDataHandler, WinToast_DicedData, ','); WinToast_PayloadHandler.push_back(WinToast_DicedData))
								;
							// * We delete data by comparing saved epoch time task and system saved epoch time task.
							if (WinToast_PayloadHandler[0] != TaskList.at(ObjectScanIter).TaskID)
							{
								if (!WinToast_StateHandler.eof())
								{
									for (unsigned IterHandler = INIT_BASE_NUM; IterHandler < WinToast_PayloadHandler.size(); IterHandler++)
									{
										WinToast_TempStateHandler << WinToast_PayloadHandler[IterHandler] << (IterHandler == (WinToast_PayloadHandler.size() - ADJUST_BY_ONE) ? "\n" : ",");
									}
								}
							}
						}
						WinToast_StateHandler.close();
						WinToast_TempStateHandler.close();
						remove(SaveStatePath_WT);
						rename(FilePointState_WT, SaveStatePath_WT);
						TaskList.erase(TaskList.begin() + (ObjectScanIter));
						return THREAD_PRC_TERM;
					}
					else
					{
						DelayRunTimeBy(WAIT_STARTTHREAD);
						continue;
					}
				}
				return (unsigned)TaskList.size(); // * THREAD_PRC_TERM;
			}
			else
			{
				continue;
			}
		}
	}
	else
	{
		return THREAD_NOTASK_REPEAT;
	}
}

void TTRM::WinToast_ReminderPrompt(std::string ReadTaskName, std::string ReadPersonInCharge, unsigned short ReadReminderType, time_t ReadNotifyByTime, tm TMToRead) noexcept
{
	std::wstring SnoozeTime = std::to_wstring(SNOOZE_TIME);

	// * WString Conversion from std::String. We don't want to change things globally by replacing std::string with std::wstring. Too late to change something that most functions used.
	std::wstring ConvWStr_TaskN(ReadTaskName.begin(), ReadTaskName.end());
	std::wstring ConvWStr_RPIC(ReadPersonInCharge.begin(), ReadPersonInCharge.end());

	std::wstringstream ConvWStr_DateTimeData;
	WinToastTemplate ShowReminder(WinToastTemplate::Text04);
	if (ReadReminderType == QuickRemind)
	{
		ConvWStr_DateTimeData << L"Time Triggered at " << std::setw(2) << std::setfill(L'0') << TMToRead.tm_hour << L":" << std::setw(2) << std::setfill(L'0') << TMToRead.tm_min;
		ShowReminder.setTextField(L"Quick Reminder Triggered~!", WinToastTemplate::FirstLine);
		ShowReminder.setTextField(ConvWStr_DateTimeData.str(), WinToastTemplate::ThirdLine);
	}
	else
	{
		ConvWStr_DateTimeData << L"Date Time Triggered at " << std::setfill(L'0') << std::setw(2) << (TMToRead.tm_mon + 1) << "/" << std::setfill(L'0') << std::setw(2) << TMToRead.tm_mday << "/" << std::setfill(L'0') << std::setw(2) << (TMToRead.tm_year + START_CTIME) << ", " << std::setfill(L'0') << std::setw(2) << TMToRead.tm_hour << ":" << std::setfill(L'0') << std::setw(2) << TMToRead.tm_min << std::endl;
		ShowReminder.setTextField(L"Date-Based Reminder Triggered~!", WinToastTemplate::FirstLine);
		ShowReminder.setTextField(ConvWStr_DateTimeData.str(), WinToastTemplate::ThirdLine);
	}
	ShowReminder.setTextField(L"Task '" + ConvWStr_TaskN + L"' for " + ConvWStr_RPIC, WinToastTemplate::SecondLine);

	ShowReminder.setAttributionText(PROJECT_NAME);
	ShowReminder.setDuration(WinToastTemplate::Duration::Long);
	ShowReminder.addAction(L"Snooze for " + SnoozeTime + L" Minutes");
	ShowReminder.addAction(L"Dismiss");
	ShowReminder.setAudioPath(WinToastTemplate::Reminder);
	WinToast::instance()->showToast(ShowReminder, new TTRM_WinToast);
}

void TTRM::ParseGivenParam(unsigned short argcount, char *argv[])
{
	unsigned int IterHandler_UnInt = INIT_BASE_NUM;
	std::cout << "\tQuick Tasks To Remind Me C++ in CLI version. BETA" << std::endl
			  << std::endl;
	std::cout << "\t\tCreated by Data Structure Group 5, Group Members {\n \t\t\tHeader Core Developer: 'Janrey Licas',\n \t\t\tAppFlow Director: 'Rejay Mar'\n};" << std::endl
			  << std::endl;
	std::cout << "[Perform Parameter Given] |> Counted Parameter: " << argcount << std::endl;
	while (!strcmp(argv[IterHandler_UnInt], "") && IterHandler_UnInt != LIMIT_ARGC_COUNTER)
	{
		// TODO: Create more features here. Use switch for Selection of Data here.
		std::cout << " Parameter Index " << IterHandler_UnInt << " |> Parameter Value -> " << argv[IterHandler_UnInt] << std::endl;
	}
}

// ! Slightly Not Cleaned.
unsigned short TTRM::Cmpnt_Initializer()
{
	TTRM_TaskData SaveStateContainer;
	long Console_PosX = INIT_BASE_NUM, Console_PosY = INIT_BASE_NUM;
	HWND ConsoleWnd = GetConsoleWindow();
	RECT ConsoleWindow, ClientScrWindow;
	HMENU Console_BtnClose = GetSystemMenu(ConsoleWnd, FALSE);

	SetConsoleTitle("Tasks To Remind Me C++ CLI, Version Initial.10092018.1955 | Data Structure Group 5 >> https://github.com/CodexLink/TaskToRemindMe_CPlusPlus");

	std::cout << std::endl
			  << std::endl
			  << "\t";
	PrintConsoleASCII(ASCII_FullBlock, 1);
	PrintConsoleASCII(ASCII_HDivider, 90);
	PrintConsoleASCII(ASCII_FullBlock, 1);
	std::cout << std::endl
			  << std::endl
			  << "\tConsole Position and Styling |> Working On It." << std::endl;

	GetClientRect(ConsoleWnd, &ConsoleWindow);
	GetWindowRect(ConsoleWnd, &ClientScrWindow);
	Console_PosX = GetSystemMetrics(SM_CXSCREEN) / 2 - (ClientScrWindow.right - ClientScrWindow.left) / 2,
	Console_PosY = GetSystemMetrics(SM_CYSCREEN) / 2 - (ClientScrWindow.bottom - ClientScrWindow.top) / 2,
	MoveWindow(ConsoleWnd, Console_PosX, Console_PosY, ClientScrWindow.right - ClientScrWindow.left, (ClientScrWindow.bottom - ClientScrWindow.top) * 2, TRUE);
	EnableMenuItem(Console_BtnClose, SC_CLOSE, MF_GRAYED);

	std::cout << "\tConsole Position and Styling |> Done." << std::endl
			  << std::endl;

	std::cout << "\tComponent Checking Point | Before Program Initialization..." << std::endl
			  << std::endl
			  << "\tWinToast Library |> Checking Compatibility...";

	if (WinToast::isCompatible())
	{
		std::cout << std::endl
				  << "\tWinToast Library |> Compatible. Setting Up Parameters..." << std::endl;

		WinToast::instance()->setAppName(PROJECT_NAME);
		WinToast::instance()->setAppUserModelId(WinToast::configureAUMI(PROJECT_CREATOR, PROJECT_NAME, PROJECT_SHORTCODE, PROJECT_VER));
		//
		std::cout << "\tWinToast Library |> Application Name Loaded." << std::endl;
		std::cout << "\tSave State Load  |> Opening SaveState File..." << std::endl;
		SaveStateHandler.open(SaveStatePath, std::ios::in);

		if (SaveStateHandler.is_open())
		{
			std::cout << "\tSave State Load  |> SaveState File Opened! Iterating and Collecting Saved Reminders";
			while (std::getline(SaveStateHandler, DataLineHandler))
			{
				std::cout << ".";
				PayloadHandler.clear();
				std::stringstream RowHandler(DataLineHandler);

				while (std::getline(RowHandler, ConvertedHandler, ','))
				{
					PayloadHandler.push_back(ConvertedHandler);
				}
				SaveStateContainer.TaskID = PayloadHandler[0];
				SaveStateContainer.TaskName = PayloadHandler[1];
				SaveStateContainer.TaskInCharge = PayloadHandler[2];
				SaveStateContainer.ReminderType = std::stoi(PayloadHandler[3]);
				time_t EpochHandler = std::stoll(PayloadHandler[4]);
				SaveStateContainer.TempTM = localtime(&EpochHandler);
				SaveStateContainer.ReminderData = *SaveStateContainer.TempTM;
				++IterHandler_UnInt;
				TaskList.push_back(SaveStateContainer);
			}
			SaveStateHandler.close();
			std::cout << std::endl
					  << std::endl
					  << "\tSave State Loaded |> Done. Loaded " << IterHandler_UnInt << " Reminders!" << std::endl;
		}
		else
		{
			std::cout << "\tSave State Create |> Save File Doesn't Exist. Creating Save File..." << std::endl;

			TempSaveStateHandler.open(FilePointState, std::ios::out);

			if (TempSaveStateHandler.is_open())
			{
				std::cout << "\tSave State Create |> SaveState File Created!" << std::endl;
				TempSaveStateHandler.close();
				rename(FilePointState, SaveStatePath);
				std::cout << std::endl
						  << "\t";
				PrintConsoleASCII(ASCII_VLDivider, 1);
				PrintConsoleASCII(ASCII_HDivider, 3);
				PrintConsoleASCII(ASCII_HDivider, 90);
				PrintConsoleASCII(ASCII_VRDivider, 1);
				std::cout << std::endl
						  << std::endl;
			}
			else
			{
				std::cout << "\tSave State Create |> SaveState File Creation Failure. Fatal Error | Terminating Program" << std::endl
						  << std::endl;
				std::cout << "\t";
				PrintConsoleASCII(ASCII_FullBlock, 1);
				PrintConsoleASCII(ASCII_HDivider, 90);
				PrintConsoleASCII(ASCII_FullBlock, 1);
				DelayRunTimeBy(SLEEP_ERROR_PROMPT);
				return TERM_FAILED;
			}
		}
		SaveStateHandler.close();

		if (WinToast::instance()->initialize())
		{
			WinToastTemplate TaskCountShow(WinToastTemplate::Text02);
			std::wstring TaskCount = std::to_wstring(TaskList.size());
			std::wstring WelcomeFirstPT = L"Hello User! You currently have ";
			std::wstring WelcomeSecondPT = (TaskList.size() <= CONTAINS_ONE_ELEM) ? L" task" : L" tasks";
			std::wstring WelcomeThirdPT = L" for today.";

			TaskCountShow.setTextField(PROJECT_NAME, WinToastTemplate::FirstLine);
			TaskCountShow.setAttributionText(L"Data Struct Group 5");
			TaskCountShow.setTextField(WelcomeFirstPT + TaskCount + WelcomeSecondPT + WelcomeThirdPT, WinToastTemplate::SecondLine);

			std::cout << "\tWinToast Library |> Library Prepped." << std::endl;
			if (!WinToast::instance()->showToast(TaskCountShow, new TTRM_WinToast))
			{
				std::cerr << "\tWinToast Library |> Error. Could Not Launch Toast Notification!" << std::endl;
				Sleep(SLEEP_SIGNIFICANT_ERR);
			}

			std::cout << std::endl
					  << "\tMulti-Threading | Starting Simultaneous Threading Wrapper..." << std::endl;
			// * Start Our Threading and Checking of Reminders.
			_beginthreadex(0, 0, &TTRM::MultiThread_Wrapper, 0, 0, &MTID_Handler);
			std::cout << "\tMulti-Threading | Simultaneous Wrapper Threading Initialized..." << std::endl
					  << std::endl;
			std::cout << "\t";
			PrintConsoleASCII(ASCII_FullBlock, 1);
			PrintConsoleASCII(ASCII_HDivider, 90);
			PrintConsoleASCII(ASCII_FullBlock, 1);
			DelayRunTimeBy(SLEEP_OPRT_FINISHED);
			return TERM_SUCCESS;
		}
		else
		{
			std::cerr << "\tWinToast Library |> Error. Cannot Initialize WinToast Library, Program Terminated." << std::endl
					  << std::endl;
			std::cout << "\t";
			PrintConsoleASCII(ASCII_FullBlock, 1);
			PrintConsoleASCII(ASCII_HDivider, 90);
			PrintConsoleASCII(ASCII_FullBlock, 1);
			DelayRunTimeBy(SLEEP_ERROR_PROMPT);
			return TERM_FAILED;
		}
	}
	else
	{
		std::cerr << "\tWinToast Library |> Error. Cannot Initialize WinToast Library, Program Terminated." << std::endl;
		std::cout << "\t";
		PrintConsoleASCII(ASCII_FullBlock, 1);
		PrintConsoleASCII(ASCII_HDivider, 90);
		PrintConsoleASCII(ASCII_FullBlock, 1);
		DelayRunTimeBy(SLEEP_ERROR_PROMPT);
		return TERM_FAILED;
	}
	return FUNC_OOS;
}

void TTRM::SetConsoleCurPos(short SP_X, short SP_Y) noexcept(true)
{
	COORD ConsolePosInfo = {SP_X, SP_Y};
	HANDLE ConsoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(ConsoleHandler, ConsolePosInfo);
	return;
}

void TTRM::PrintConsoleASCII(unsigned char CharToIter, unsigned short IterValue)
{
	while (IterValue--)
	{
		std::cout << ASCII_CharPrint(CharToIter);
	}
	return;
}

std::string TTRM::SP_DisplayTasksParser(REMINDER_TYPES IntType) noexcept(true)
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

void TTRM::SP_DisplayTasks(DISPLAY_OPTIONS WindowID_INT)
{
	unsigned short TaskNumHandler = START_BY_ONE;
	bool isAtHome = false;
	if (!TaskList.size())
	{
		std::cerr << std::endl
				  << "\tThere are no tasks in queue! Please add one." << std::endl;
		return;
	}
	else
	{
		std::cout << std::endl
				  << "\tThere" << (TaskList.size() <= CONTAINS_ONE_ELEM ? " is " : " are ") << TaskList.size() << (TaskList.size() <= CONTAINS_ONE_ELEM ? " task" : " tasks");
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
			break;
		}
		for (auto IterTasks : TaskList)
		{
			if (isAtHome && TaskNumHandler > TASK_DISPLAY_LIMIT)
			{
				std::cout << std::endl
						  << "\t... And there are other " << (TaskList.size() + ADJUST_BY_ONE) - TaskNumHandler << (((TaskList.size() + ADJUST_BY_ONE) - TaskNumHandler) == CONTAINS_ONE_ELEM ? " task" : " tasks") << " available!" << std::endl;
				break;
			}
			else
			{
				std::cout << "\tTask # " << TaskNumHandler << " | ";

				switch (IterTasks.ReminderType)
				{
				case QuickRemind:
					// ! Done
					std::cout << SP_DisplayTasksParser((TTRM::REMINDER_TYPES)IterTasks.ReminderType) << " |> " << IterTasks.TaskName << " | In Charge: " << IterTasks.TaskInCharge << ", Trigger Time at " << std::setfill('0') << std::setw(2) << IterTasks.ReminderData.tm_hour << ":" << std::setfill('0') << std::setw(2) << IterTasks.ReminderData.tm_min << std::endl;
					break;

				case DateBasedRemind:
					// ! Done
					std::cout << SP_DisplayTasksParser((TTRM::REMINDER_TYPES)IterTasks.ReminderType) << " |> " << IterTasks.TaskName << " | In Charge |> " << IterTasks.TaskInCharge << ", Date and Time Trigger |> " << std::setfill('0') << std::setw(2) << IterTasks.ReminderData.tm_mon + 1 << "/" << std::setfill('0') << std::setw(2) << IterTasks.ReminderData.tm_mday << "/" << std::setfill('0') << std::setw(2) << IterTasks.ReminderData.tm_year + START_CTIME << ", " << std::setfill('0') << std::setw(2) << IterTasks.ReminderData.tm_hour << ":" << std::setfill('0') << std::setw(2) << IterTasks.ReminderData.tm_min << std::endl;
					break;

				default:
					break;
				}
				TaskNumHandler++;
			}
		}
	}
	return;
}

std::string TTRM::SP_DLT() const
{
	time_t TimeStamp = time(NULL);
	std::stringstream StrTime;
	tm *TimeStorage = localtime(&TimeStamp);
	StrTime << TimeStorage->tm_mon + ADJUST_BY_ONE << "/" << std::setfill('0') << std::setw(2) << TimeStorage->tm_mday << "/" << std::setfill('0') << std::setw(2) << (TimeStorage->tm_year + START_CTIME) << " | " << std::setfill('0') << std::setw(2) << TimeStorage->tm_hour << ":" << std::setfill('0') << std::setw(2) << TimeStorage->tm_min << ":" << std::setfill('0') << std::setw(2) << TimeStorage->tm_sec;
	return StrTime.str();
}

// ! Starting Point of Program |> Display Menu, Does Not Throw Any Exceptions
void TTRM::SP_DisplayMenu()
{
	while (CONTINOUS_RNN_PROC)
	{
		signed int InputHandler_Int = INIT_BASE_NUM;
		ConsoleCall("CLS");
		std::cout << std::endl
				  << std::endl
				  << "\t" << PROJECT_NAME_STRL << " | " << PROJECT_VER_STRL << std::endl
				  << std::endl;
		std::cout << "\tLocal System Time Last Frame |> " << SP_DLT() << std::endl;
		std::cout << std::endl
				  << "\t";
		PrintConsoleASCII(ASCII_VLDivider, 1);
		PrintConsoleASCII(ASCII_HDivider, 3);
		std::cout << " Task List, Arranged by Recent Insertion ";
		PrintConsoleASCII(ASCII_HDivider, 30);
		PrintConsoleASCII(ASCII_VRDivider, 1);
		std::cout << std::endl;
		SP_DisplayTasks(AtHome);
		std::cout << std::endl
				  << "\t";
		PrintConsoleASCII(ASCII_VLDivider, 1);
		PrintConsoleASCII(ASCII_HDivider, 3);
		std::cout << " System Options ";
		PrintConsoleASCII(ASCII_HDivider, 55);
		PrintConsoleASCII(ASCII_VRDivider, 1);
		std::cout << std::endl
				  << std::endl
				  << "\tChoice #1 |> Add a Task To Remind You" << std::endl
				  << "\tChoice #2 |> Delete a Task That Reminds You" << std::endl
				  << "\tChoice #3 |> Edit / Modify an Existing Task for Alterations" << std::endl
				  << std::endl
				  << "\tChoice #4 |> View All Tasks Without Limit" << std::endl
				  << "\tChoice #5 |> Remove All Tasks at Save State and Queue System" << std::endl
				  << std::endl
				  << "\tChoice #6 |> Refresh Tasks from Save State" << std::endl
				  << "\tChoice #7 |> Refresh Menu Display for Current Local Time Update" << std::endl
				  << std::endl
				  << "\tChoice #0 |> Terminate / Exit / Close The Program" << std::endl
				  << std::endl;
		std::cout << "\t";
		PrintConsoleASCII(ASCII_VLDivider, 1);
		PrintConsoleASCII(ASCII_HDivider, 3);
		PrintConsoleASCII(ASCII_HDivider, 71);
		PrintConsoleASCII(ASCII_VRDivider, 1);
		std::cout << std::endl
				  << std::endl;

		std::cout << "\t[USER INPUT] Your Choice and ENTER |> ";
		std::cin >> InputHandler_Int;
		BufferClear_STDIN('\n');
		if (std::cin.fail())
		{
			std::cin.clear();
			BufferClear_STDIN('\n');
			std::cout << std::endl
					  << "\t[INPUT ERROR] Input is Detected as Non-Integer.";
			DelayRunTimeBy(SLEEP_ERROR_PROMPT);
			continue;
		}
		// ! Stack the function.
		// ! Return to 'this' function so that we can go back to this function easily.
		switch (InputHandler_Int)
		{
		case AddTask:
			DC_ATask();
			break;

		case DeleteTask:
			DC_DTask();
			break;

		case EditTask:
			DC_ETask();
			break;

		case ViewTask:
			DC_VTask();
			break;

		case RemoveAllTask:
			DC_RQT();
			break;

		case RefreshTaskList:
			DC_RTLFSS();
			break;

		case RefreshMenu:
			std::cout << std::endl
					  << "\t[TASKLIST REFRESH] Refreshing Task List Display for Value Updates...";
			DelayRunTimeBy(SLEEP_DISPLAY_WINDOW);
			continue;

		case Termination:
			break;

		default:
			std::cout << std::endl
					  << "\t[INPUT ERROR] User Picked Choices That is Not-Existing from Choices!";
			DelayRunTimeBy(SLEEP_ERROR_PROMPT);
			break;
		}
		if (!InputHandler_Int)
			return;
	}
}

void TTRM::DC_ATask()
{
	while (FUNC_AWAIT_CMPLT)
	{
		TTRM_TaskData NewTask; // * Create Object To Pass On...
		time_t CurrentDateTime = time(NULL);
		tm *CurrentTContainer = localtime(&CurrentDateTime);
		ConsoleCall("CLS");

		std::cout << std::endl
				  << std::endl
				  << "\t";
		PrintConsoleASCII(ASCII_VLDivider, 1);
		PrintConsoleASCII(ASCII_HDivider, 3);
		std::cout << " Task To Remind You Insertion ";
		PrintConsoleASCII(ASCII_HDivider, 55);
		PrintConsoleASCII(ASCII_VRDivider, 1);
		std::cout << std::endl
				  << std::endl;
		std::cout << "\tThings To Know For Reminder Insertion"
				  << std::endl
				  << std::endl
				  << "\t\t1. Reminder Task Name Must Be 2 Characters and Above"
				  << std::endl
				  << "\t\t2. Reminder In Charge Name Must Be 2 Characters and Above" << std::endl
				  << std::endl
				  << "\tFor Cancelling Insertion Operation, 'TYPE --CANCEL' On Any Of Those TWO Parameters" << std::endl;
		std::cout << std::endl
				  << "\t";
		PrintConsoleASCII(ASCII_VLDivider, 1);
		PrintConsoleASCII(ASCII_HDivider, 88);
		PrintConsoleASCII(ASCII_VRDivider, 1);
		std::cout << std::endl
				  << std::endl;
		std::cout << "\tName of the Task To Remind You |> ", std::getline(std::cin, NewTask.TaskName);

		if (NewTask.TaskName.length() < CHAR_MIN_TASKNAME || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << std::endl
					  << "\t[INPUT ERROR] |> TaskName Character Is Not Enough. Press Enter Key To Try Again.";
			BufferClear_STDIN('\n');
			continue;
		}
		else if (NewTask.TaskName == "--CANCEL")
		{
			std::cin.clear();
			std::cerr << std::endl
					  << "\t[OPRT ABORT] |> New Task Insertion Operation is Cancelled by User...";
			DelayRunTimeBy(SLEEP_OPRT_FINISHED);
			return;
		}

		std::cout << "\tName Of The Person In Charge at The Task |> ", std::getline(std::cin, NewTask.TaskInCharge);

		if (NewTask.TaskInCharge.length() < CHAR_MIN_INCHARGE || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << std::endl
					  << "\t[INPUT ERROR] |> Task In Charge Character Is Not Enough. Press Enter Key To Try Again.";
			BufferClear_STDIN('\n');
			continue;
		}
		else if (NewTask.TaskInCharge == "--CANCEL")
		{
			std::cin.clear();
			std::cerr << std::endl
					  << "\t[OPRT ABORT] |> New Task Insertion Operation is Cancelled by User...";
			DelayRunTimeBy(SLEEP_OPRT_FINISHED);
			return;
		}

		std::cout << std::endl
				  << "\t";
		PrintConsoleASCII(ASCII_VLDivider, 1);
		PrintConsoleASCII(ASCII_HDivider, 3);
		std::cout << " Task To Remind You Insertion ";
		PrintConsoleASCII(ASCII_HDivider, 55);
		PrintConsoleASCII(ASCII_VRDivider, 1);
		std::cout << std::endl
				  << std::endl;
		std::cout << "\tThings To Know For Reminder Types and What To Choose"
				  << std::endl
				  << std::endl
				  << "\t\t1. Quick Reminder - Reminds You Quickly Based On Minutes Left To Trigger."
				  << std::endl
				  << "\t\t|> Requires > Input by Minutes, Minimum = 1 | Maximum = 180"
				  << std::endl
				  << std::endl
				  << "\t\t2. Date Based Reminder - Reminds You Based On Given Date and Time To Trigger."
				  << std::endl
				  << "\t\t|> Requires > Date and Time, Let Seperator Be Space, (MM/DD/YYYY, HH:MM)."
				  << std::endl
				  << "\t\t|> Due To Complexity, Checking of Date and Time will be executed after inputting" << std::endl
				  << "\t\t   all date and time required parameters."
				  << std::endl
				  << std::endl
				  << "\tFor Cancelling Insertion Operation, TYPE '0' At This Point." << std::endl;
		std::cout << std::endl
				  << "\t";
		PrintConsoleASCII(ASCII_VLDivider, 1);
		PrintConsoleASCII(ASCII_HDivider, 88);
		PrintConsoleASCII(ASCII_VRDivider, 1);

		std::cout << std::endl
				  << std::endl
				  << "\t"
				  << "Type of Reminder To Trigger, Choice # |> ",
			std::cin >> NewTask.ReminderType;

		if (NewTask.ReminderType < CancelOperation || NewTask.ReminderType > DateBasedRemind || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << std::endl
					  << "\t[INPUT ERROR] |> Reminder Type Input is Invalid. Press Any Key To Try Again.";
			BufferClear_STDIN('\n');
			_getche();
			continue;
		}
		else
		{
			switch (NewTask.ReminderType)
			{
			case CancelOperation:
				std::cerr << std::endl
						  << "\t[OPRT ABORT] |> New Task Insertion Operation is Cancelled by User...";
				DelayRunTimeBy(SLEEP_OPRT_FINISHED);
				return;

			case QuickRemind:
				std::cout << "\tMinutes Left To Remind You |> ", std::cin >> NewTask.NotifyByTime;
				if (NewTask.NotifyByTime <= QUICKR_MIN_TIME || NewTask.NotifyByTime > QUICKR_MAX_TIME)
				{
					std::cerr << std::endl
							  << "\t[INPUT ERROR] |> Time Entered is invalid. Please try again by pressing any key to restart.";
					BufferClear_STDIN('\n');
					_getche();
					continue;
				}
				else
				{
					CurrentDateTime = time(NULL) + (((time_t)(MAX_TIME_MIN + ADJUST_BY_ONE)) * NewTask.NotifyByTime);
					NewTask.TempTM = localtime(&CurrentDateTime);
					NewTask.ReminderData = *NewTask.TempTM;
					break;
				}

			case DateBasedRemind:
				CurrentDateTime = time(NULL);
				NewTask.TempTM = localtime(&CurrentDateTime);
				NewTask.ReminderData = *NewTask.TempTM; // ! Avoiding Error MKTime Returns -1 as an Error.

				std::cout << "\tTarget Date of Reminding, Remember (MM DD YYYY) |> ", std::cin >> NewTask.ReminderData.tm_mon >> NewTask.ReminderData.tm_mday >> NewTask.ReminderData.tm_year;
				//! Sets Parameters To Comply with MKtime
				// ! Conditions, If User Input Is Lesser Than Todays Time Will Be Considered as Invalid~!
				if (NewTask.ReminderData.tm_mon < MIN_TIME_MONTH || NewTask.ReminderData.tm_mon > MAX_TIME_MONTH || std::cin.fail())
				{
					std::cerr << std::endl
							  << "\t[INPUT ERROR] |> Target Month Parameter is either invalid or less from current date. Press Any Key To Try Again.";
					std::cin.clear();
					BufferClear_STDIN('\n');
					_getche();
					continue;
				}
				else
				{
					if (NewTask.ReminderData.tm_mday < MIN_TIME_DAY || NewTask.ReminderData.tm_mday > MAX_TIME_DAY || std::cin.fail())
					{
						std::cin.clear();
						std::cerr << std::endl
								  << "\t[INPUT ERROR] |> Target Day Parameter is either invalid or less from current date. Press Any Key To Try Again.";
						BufferClear_STDIN('\n');
						_getche();
						continue;
					}
					else
					{
						// ! Check Year, If 2018, But 2019
						if (NewTask.ReminderData.tm_year < CurrentTContainer->tm_year)
						{
							std::cerr << std::endl
									  << "\t[INPUT ERROR] |> Target Year Parameter is either invalid or less from current date. Press Any Key To Try Again.";
							std::cin.clear();
							BufferClear_STDIN('\n');
							_getche();
							continue;
						}
					}

					std::cout << "\tTime To Remind You, Remember, (HH MM) |> ", std::cin >> NewTask.ReminderData.tm_hour >> NewTask.ReminderData.tm_min;

					// ! Today To Today Sens Time. Currently WORK ON PROGRESS. Checks if Input is following 24-Hour Standards.
					if ((NewTask.ReminderData.tm_hour > MIN_TIME_HOUR || NewTask.ReminderData.tm_hour <= MAX_TIME_HOUR) || (NewTask.ReminderData.tm_min >= MIN_TIME_MIN || NewTask.ReminderData.tm_min <= MAX_TIME_MIN) || !std::cin.fail())
					{
						// ! We Modify Users Date To Comply with MKTime
						CurrentDateTime = time(NULL);
						CurrentTContainer = localtime(&CurrentDateTime);
						NewTask.ReminderData.tm_year -= START_CTIME, NewTask.ReminderData.tm_mon -= ADJUST_BY_ONE, NewTask.ReminderData.tm_sec = CurrentTContainer->tm_sec;

						// ! Checks User Input Dates Were Lesser Than The Expected Date, Means, Anything Below Than Today's DAte Will Be Considered Invalid.
						if (mktime(&NewTask.ReminderData) < time(NULL))
						{
							time_t CurrentTime = time(NULL);
							tm *LocalTime = localtime(&CurrentTime);
							//std::cout << "\n\n\tEpoch Time " << mktime(&NewTask.ReminderData) << " " << time(NULL);
							//std::cout << "\tDebug | Month" << NewTask.ReminderData.tm_mon << " | " << CurrentTContainer->tm_mon << std::endl;
							//std::cout << "\tDebug | Day" << NewTask.ReminderData.tm_mday << " | " << CurrentTContainer->tm_mday << std::endl;
							//std::cout << "\tDebug | Year" << NewTask.ReminderData.tm_year << " | " << CurrentTContainer->tm_year << std::endl;
							//std::cout << "\tDebug | Hour" << NewTask.ReminderData.tm_hour << "  |" << CurrentTContainer->tm_hour << std::endl;
							//std::cout << "\tDebug | Minute" << NewTask.ReminderData.tm_min << " | " << CurrentTContainer->tm_min << std::endl;
							//std::cout << "\tDebug | Second" << NewTask.ReminderData.tm_sec << " | " << CurrentTContainer->tm_sec << std::endl
							//<< std::endl;

							std::cout << "\t[DATE ERROR] User Inputted Date and Time That is Lesser Than Today's Date and Time!";
							BufferClear_STDIN('\n');
							DelayRunTimeBy(SLEEP_ERROR_PROMPT);
							continue;
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
						std::cerr << std::endl
								  << "\t[INPUT ERROR] |> Time Input is Invalid. Keep in mind that I need 24 hour format. Press Any Key To Try Again.";
						BufferClear_STDIN('\n');
						_getche();
						continue;
					}
					break;
				}
			}

			try
			{
				SaveStateHandler.open(SaveStatePath, std::ios::out | std::ios::app);
				if (SaveStateHandler.is_open())
				{
					if (NewTask.ReminderType == QuickRemind)
					{
						SaveStateHandler << Gen_UniqueRID() << "," << NewTask.TaskName << "," << NewTask.TaskInCharge << "," << NewTask.ReminderType << "," << mktime(NewTask.TempTM) << std::endl;
					}
					else
					{
						NewTask.ReminderData.tm_sec = INIT_BASE_NUM;
						SaveStateHandler << Gen_UniqueRID() << "," << NewTask.TaskName << "," << NewTask.TaskInCharge << "," << NewTask.ReminderType << "," << mktime(&NewTask.ReminderData) << std::endl;
					}
					TaskList.push_back(NewTask);
				}

				SaveStateHandler.close();
				std::cout << std::endl
						  << "\t[INSERTION] |> Task '" << NewTask.TaskName << "' has been Successfully Added to the Queue System!";
				DelayRunTimeBy(SLEEP_OPRT_FINISHED);
				break;
			}
			catch (std::exception &ErrMessage)
			{
				std::cerr << std::endl
						  << ErrMessage.what() << std::endl;
				DelayRunTimeBy(SLEEP_SIGNIFICANT_ERR);
				continue;
			}
			catch (...)
			{
				std::cerr << "\t[PROCESS] Unknown Error..." << std::endl;
				DelayRunTimeBy(SLEEP_SIGNIFICANT_ERR);
				continue;
			}
		}
	}
	return;
}
void TTRM::DC_DTask()
{
	while (FUNC_AWAIT_CMPLT)
	{
		size_t TaskHandlerSize = TaskList.size();
		char InputHandler_Char = NULL_CHAR;
		char InputHandler_Char = NULL_CHAR;
		unsigned int IterHandler_UnInt = INIT_BASE_NUM;
		ConsoleCall("CLS");
		std::cout << std::endl
				  << std::endl
				  << "\t";
		PrintConsoleASCII(ASCII_VLDivider, 1);
		PrintConsoleASCII(ASCII_HDivider, 3);
		std::cout << " Currently Available Reminders To Trigger From The Queue System ";
		PrintConsoleASCII(ASCII_HDivider, 25);
		PrintConsoleASCII(ASCII_VRDivider, 1);
		std::cout << std::endl;
		SP_DisplayTasks(DeleteTask);
		std::cout << std::endl
				  << "\t";
		PrintConsoleASCII(ASCII_VLDivider, 1);
		PrintConsoleASCII(ASCII_HDivider, 3);
		PrintConsoleASCII(ASCII_HDivider, 89);
		PrintConsoleASCII(ASCII_VRDivider, 1);
		std::cout << std::endl
				  << std::endl;
		if (TaskHandlerSize)
		{
			std::cout << "\t[INFORM] Please Select A Task To Delete According To Task #." << std::endl;
			std::cout << "\t[INPUT] Task # or '0' To Go Back To Menu |> ", std::cin >> IterHandler_UnInt;
			if (std::cin.fail())
			{
				std::cin.clear();
				BufferClear_STDIN('\n');
				std::cerr << std::endl
						  << "\t[INPUT ERROR] Input is Non-Integer.";
				DelayRunTimeBy(SLEEP_ERROR_PROMPT);
				continue;
			}
			else
			{
				if (IterHandler_UnInt)
				{
					if (IterHandler_UnInt <= TaskHandlerSize)
					{
						std::cout << std::endl
								  << "\t[WARNING] |> Are you sure you want to delete this task: '" << TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).TaskName << "'?" << std::endl
								  << "\t[WARNING] |> This action is irreversible. Continue???" << std::endl
								  << "\t[INPUT  ] |> ['Y'es or 'N'o] |> ",
							std::cin >> InputHandler_Char;
						if (std::cin.fail())
						{
							std::cin.clear();
							BufferClear_STDIN('\n');
							std::cerr << std::endl
									  << "\t[INPUT ERROR] Input is Non-Integer.";
						}
						else
						{
							switch (InputHandler_Char)
							{
							case CONFIRMED_TRUE_LOWER:
							case CONFIRMED_TRUE_UPPER:

								SaveStateHandler.open(SaveStatePath, std::ios::in);
								TempSaveStateHandler.open(FilePointState, std::ios::out);

								while (!SaveStateHandler.eof() && std::getline(SaveStateHandler, DataLineHandler))
								{
									PayloadHandler.clear();
									std::stringstream TempDataHandler(DataLineHandler);

									for (DataLineHandler; std::getline(TempDataHandler, ConvertedHandler, ','); PayloadHandler.push_back(ConvertedHandler))
										;
									// ! We delete data by comparing saved epoch time task and system saved epoch time task.
									if (PayloadHandler[0] != TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).TaskID)
									{
										if (!SaveStateHandler.eof())
										{
											for (unsigned short IterHandler_UnShort = INIT_BASE_NUM; IterHandler_UnShort < PayloadHandler.size(); IterHandler_UnShort++)
											{
												TempSaveStateHandler << PayloadHandler[IterHandler_UnShort] << (IterHandler_UnShort == (PayloadHandler.size() - ADJUST_BY_ONE) ? "\n" : ",");
											}
										}
									}
								}
								SaveStateHandler.close();
								TempSaveStateHandler.close();

								remove(SaveStatePath);
								rename(FilePointState, SaveStatePath);

								std::cout << std::endl
										  << "\t[CONFIRMATION, SUCCESS] |> Task '" << TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).TaskName << "' deleted.";
								TaskList.erase(TaskList.begin() + (IterHandler_UnInt - ADJUST_BY_ONE));
								DelayRunTimeBy(SLEEP_OPRT_FINISHED);
								continue;

							case CONFIRMED_FALSE_LOWER:
							case CONFIRMED_FALSE_UPPER:
								std::cout << std::endl
										  << "\t[CONFIRMATION, SUCCESS] |> Reminder Task Deletion Cancelled.";
								DelayRunTimeBy(SLEEP_OPRT_FINISHED);
								continue;

							default:
								std::cout << std::endl
										  << "\t[CONFIRMATION, ERROR] |> User Input is Invalid.";
								std::cin.clear();
								BufferClear_STDIN('\n');
								DelayRunTimeBy(SLEEP_OPRT_FAILED);
								continue;
							}
						}
					}
					else
					{
						std::cerr << std::endl
								  << "\t[OPRT ERROR] User Requested To Delete Tasks Non-Existent or Out of Range of Task List!";
						DelayRunTimeBy(SLEEP_ERROR_PROMPT);
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
			std::cerr << std::endl
					  << "\t[VIEW INFO] Task Queue is currently empty! Please add some task/s.";
			DelayRunTimeBy(SLEEP_OPRT_FINISHED);
			break;
		}
	}
	return;
}

void TTRM::DC_ETask()
{
	while (FUNC_AWAIT_CMPLT)
	{
		TTRM_TaskData NewModifiedTask; // * Create Object To Pass On...
		time_t CurrentDateTime = time(NULL);
		tm *CurrentTContainer = localtime(&CurrentDateTime);
		size_t TaskHandlerSize = TaskList.size();
		unsigned int IterHandler_UnInt = INIT_BASE_NUM;
		ConsoleCall("CLS");
		if (TaskHandlerSize)
		{
			std::cout << std::endl
					  << std::endl
					  << "\t";
			PrintConsoleASCII(ASCII_VLDivider, 1);
			PrintConsoleASCII(ASCII_HDivider, 3);
			std::cout << " Currently Available Reminders To Trigger From The Queue System ";
			PrintConsoleASCII(ASCII_HDivider, 25);
			PrintConsoleASCII(ASCII_VRDivider, 1);
			std::cout << std::endl;
			SP_DisplayTasks(EditTask);
			std::cout << std::endl
					  << "\t";
			PrintConsoleASCII(ASCII_VLDivider, 1);
			PrintConsoleASCII(ASCII_HDivider, 3);
			PrintConsoleASCII(ASCII_HDivider, 89);
			PrintConsoleASCII(ASCII_VRDivider, 1);
			std::cout << std::endl
					  << std::endl;
			std::cout << "\t[INPUT] Please Select A Task # or '0' To Go Back Menu |> ",
				std::cin >> IterHandler_UnInt;
			if (std::cin.fail())
			{
				std::cin.clear();
				BufferClear_STDIN('\n');
				std::cerr << "\t[INPUT ERROR] Input Invalid. Please try again." << std::endl;
				DelayRunTimeBy(SLEEP_ERROR_PROMPT);
				continue;
			}
			else
			{
				if (IterHandler_UnInt)
				{
					if (IterHandler_UnInt <= TaskHandlerSize)
					{
						std::cout << std::endl
								  << "\t[WARNING] |> Are you sure you want to edit this task: '" << TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).TaskName << "'?" << std::endl
								  << "\t[INPUT  ] | ['Y'es or 'N'o] |> ",
							std::cin >> InputHandler_Char;
						if (std::cin.fail())
						{
							std::cerr << "\t[INPUT ERROR] Value Received is Invalid. Please try again.";
							std::cin.clear();
							BufferClear_STDIN('\n');
						}
						else
						{
							switch (InputHandler_Char)
							{
							case CONFIRMED_TRUE_LOWER:
							case CONFIRMED_TRUE_UPPER:
								BufferClear_STDIN('\n');
								std::cout << std::endl
										  << "\t";
								PrintConsoleASCII(ASCII_VLDivider, 1);
								PrintConsoleASCII(ASCII_HDivider, 3);
								std::cout << " Task To Remind You Modification ";
								PrintConsoleASCII(ASCII_HDivider, 56);
								PrintConsoleASCII(ASCII_VRDivider, 1);
								std::cout << std::endl
										  << std::endl;
								std::cout << "\tThings To Know For Reminder Data Modification"
										  << std::endl
										  << std::endl
										  << "\t\t1. Reminder Task Name Must Be 2 Characters and Above"
										  << std::endl
										  << "\t\t2. Reminder In Charge Name Must Be 2 Characters and Above" << std::endl
										  << std::endl
										  << "\tYou cannot cancel this operation. If you want to ignore, please keep putting 0 to retain data." << std::endl;
								std::cout << std::endl
										  << "\t";
								PrintConsoleASCII(ASCII_VLDivider, 1);
								PrintConsoleASCII(ASCII_HDivider, 92);
								PrintConsoleASCII(ASCII_VRDivider, 1);
								std::cout << std::endl
										  << std::endl;
								std::cout << "\tName of the Task To Remind You, Put '0' To Retain |> ", std::getline(std::cin, NewModifiedTask.TaskName);
								if (NewModifiedTask.TaskName != "0")
								{
									if (NewModifiedTask.TaskName.length() <= CHAR_MIN_TASKNAME || std::cin.fail())
									{
										std::cin.clear();
										std::cerr << std::endl
												  << "\t[INPUT ERROR] |> TaskName Character Is Not Enough. Press Enter Key To Try Again.";
										BufferClear_STDIN('\n');
										continue;
									}
								}
								std::cout << "\tName Of The Person In Charge at The Task, Put '0' To Retain |> ", std::getline(std::cin, NewModifiedTask.TaskInCharge);
								if (NewModifiedTask.TaskInCharge != "0")
								{
									if (NewModifiedTask.TaskInCharge.length() < CHAR_MIN_INCHARGE || std::cin.fail())
									{
										std::cin.clear();
										std::cerr << std::endl
												  << "\t[INPUT ERROR] |> Task In Charge Character Is Not Enough. Press Enter Key To Try Again.";
										BufferClear_STDIN('\n');
										continue;
									}
								}
								std::cout << std::endl
										  << "\t";
								PrintConsoleASCII(ASCII_VLDivider, 1);
								PrintConsoleASCII(ASCII_HDivider, 3);
								std::cout << " Task To Remind You Modification ";
								PrintConsoleASCII(ASCII_HDivider, 56);
								PrintConsoleASCII(ASCII_VRDivider, 1);
								std::cout << std::endl
										  << std::endl;
								std::cout << "\tThings To Know For Reminder Types and What To Choose"
										  << std::endl
										  << std::endl
										  << "\t\t1. Quick Reminder - Reminds You Quickly Based On Minutes Left To Trigger."
										  << std::endl
										  << "\t\t|> Requires > Input by Minutes, Minimum = 1 | Maximum = 180"
										  << std::endl
										  << std::endl
										  << "\t\t2. Date Based Reminder - Reminds You Based On Given Date and Time To Trigger."
										  << std::endl
										  << "\t\t|> Requires > Date and Time, Let Seperator Be Space, (MM/DD/YYYY, HH:MM)."
										  << std::endl
										  << "\t\t|> Due To Complexity, Checking of Date and Time will be executed after inputting" << std::endl
										  << "\t\t   all date and time required parameters."
										  << std::endl
										  << std::endl
										  << "\tFor Cancelling Insertion Operation, TYPE '0' At This Point." << std::endl;
								std::cout << std::endl
										  << "\t";
								PrintConsoleASCII(ASCII_VLDivider, 1);
								PrintConsoleASCII(ASCII_HDivider, 92);
								PrintConsoleASCII(ASCII_VRDivider, 1);

								std::cout << std::endl
										  << std::endl
										  << "\tType of Reminder To Trigger, Choice # |> ",
									std::cin >> NewModifiedTask.ReminderType;
								if (NewModifiedTask.ReminderType)
								{
									if (NewModifiedTask.ReminderType < QuickRemind || NewModifiedTask.ReminderType > DateBasedRemind || std::cin.fail())
									{
										std::cin.clear();
										std::cerr << std::endl
												  << "\t[INPUT ERROR] |> Reminder Type Input is Invalid. Press Any Key To Try Again.";
										BufferClear_STDIN('\n');
										_getche();
										continue;
									}
								}
								else
								{
									NewModifiedTask.ReminderType = TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderType;
								}

								switch (NewModifiedTask.ReminderType)
								{
								case QuickRemind:

									std::cout << "\tMinutes Left To Remind You |> ", std::cin >> NewModifiedTask.NotifyByTime;
									if (NewModifiedTask.NotifyByTime < QUICKR_INV_MAX_TIME || NewModifiedTask.NotifyByTime > QUICKR_MAX_TIME)
									{
										std::cerr << "\t[INPUT ERROR] |> Time Entered is invalid. Please try again by pressing any key to restart.";
										BufferClear_STDIN('\n');
										_getche();
										continue;
									}
									else
									{
										if (NewModifiedTask.NotifyByTime)
										{
											CurrentDateTime = mktime(&TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderData) + (((time_t)(MAX_TIME_MIN + ADJUST_BY_ONE)) * NewModifiedTask.NotifyByTime);
											NewModifiedTask.TempTM = localtime(&CurrentDateTime);
											TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderData = *NewModifiedTask.TempTM;
											NewModifiedTask.ReminderData = *NewModifiedTask.TempTM;
											//NewModifiedTask.TempTM->tm_year += START_CTIME, NewModifiedTask.TempTM->tm_mon += ADJUST_BY_ONE;
											break;
										}
										else
										{
											break;
										}
									}

								case DateBasedRemind:
									CurrentDateTime = time(NULL);
									CurrentTContainer = localtime(&CurrentDateTime);   //, CurrentTContainer->tm_year += START_CTIME, CurrentTContainer->tm_mon += ADJUST_BY_ONE;
									NewModifiedTask.ReminderData = *CurrentTContainer; // ! Avoiding Error MKTime Returns -1 as an Error.

									std::cout << "\tTarget Date of Reminding, Remember (MM DD YYYY), Type The Same Date To Retain |> ", std::cin >> NewModifiedTask.ReminderData.tm_mon >> NewModifiedTask.ReminderData.tm_mday >> NewModifiedTask.ReminderData.tm_year;
									if (NewModifiedTask.ReminderData.tm_mon < MIN_TIME_MONTH || NewModifiedTask.ReminderData.tm_mon > MAX_TIME_MONTH || std::cin.fail())
									{
										std::cin.clear();
										std::cerr << std::endl
												  << "\t[INPUT ERROR] |> Target Month Parameter is either invalid or less from current date. Press Any Key To Try Again.";
										BufferClear_STDIN('\n');
										_getche();
										continue;
									}
									else
									{
										if (NewModifiedTask.ReminderData.tm_mday < MIN_TIME_DAY || NewModifiedTask.ReminderData.tm_mday > MAX_TIME_DAY || std::cin.fail())
										{
											std::cin.clear();
											std::cerr << std::endl
													  << "\t[INPUT ERROR] |> Target Day Parameter is either invalid or less from current date. Press Any Key To Try Again.";
											BufferClear_STDIN('\n');
											_getche();
											continue;
										}
										else
										{

											if (NewModifiedTask.ReminderData.tm_year < CurrentTContainer->tm_year)
											{
												// ! If same month, check day
												std::cin.clear();
												std::cerr << std::endl
														  << "\t[INPUT ERROR] |> Target Year Parameter is either invalid or less from current date. Press Any Key To Try Again.";
												BufferClear_STDIN('\n');
												_getche();
												continue;
											}
										}
										std::cout << "\tTime To Remind You, Remember, (HH MM), Type The Same Time To Retain |> ", std::cin >> NewModifiedTask.ReminderData.tm_hour >> NewModifiedTask.ReminderData.tm_min;

										if ((NewModifiedTask.ReminderData.tm_hour > MIN_TIME_HOUR || NewModifiedTask.ReminderData.tm_hour <= MAX_TIME_HOUR) || (NewModifiedTask.ReminderData.tm_min >= MIN_TIME_MIN || NewModifiedTask.ReminderData.tm_min <= MAX_TIME_MIN) || !std::cin.fail())
										{
											CurrentDateTime = time(NULL);
											CurrentTContainer = localtime(&CurrentDateTime);
											NewModifiedTask.ReminderData.tm_year -= START_CTIME, NewModifiedTask.ReminderData.tm_mon -= ADJUST_BY_ONE, NewModifiedTask.ReminderData.tm_sec = CurrentTContainer->tm_sec;

											if (mktime(&NewModifiedTask.ReminderData) < time(NULL))
											{
												std::cout << "\t[DATE ERROR] User Time Minute is Lesser Than Today's Time Minute!";
												BufferClear_STDIN('\n');
												DelayRunTimeBy(SLEEP_ERROR_PROMPT);
												continue;
											}
											else
											{
												break;
											}
										}
										else
										{
											std::cin.clear();
											std::cerr << std::endl
													  << "\t[INPUT ERROR] |> Time Input is Invalid. Keep in mind that I need 24 hour format. Press Any Key To Try Again.";
											BufferClear_STDIN('\n');
											_getche();
											continue;
										}
										break;
									}
								}
								try
								{

									NewModifiedTask.TaskID.assign(TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).TaskID);

									if (NewModifiedTask.TaskName != "0")
									{
										TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).TaskName.assign(NewModifiedTask.TaskName);
									}
									else
									{
										NewModifiedTask.TaskName.assign(TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).TaskName);
									}

									if (NewModifiedTask.TaskInCharge != "0")
									{
										TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).TaskInCharge.assign(NewModifiedTask.TaskInCharge);
									}
									else
									{
										NewModifiedTask.TaskInCharge.assign(TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).TaskInCharge);
									}

									if (NewModifiedTask.ReminderType != TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderType)
									{
										TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderType = NewModifiedTask.ReminderType;
									}
									else
									{
										NewModifiedTask.ReminderType = TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderType;
									}

									switch (NewModifiedTask.ReminderType)
									{
									case DateBasedRemind:
										if (NewModifiedTask.ReminderData.tm_year != 0)
										{
											TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderData.tm_year = NewModifiedTask.ReminderData.tm_year;
										}
										else
										{
											NewModifiedTask.ReminderData.tm_year = TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderData.tm_year;
										}

										if (NewModifiedTask.ReminderData.tm_mon != 0)
										{
											TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderData.tm_mon = NewModifiedTask.ReminderData.tm_mon;
										}
										else
										{
											NewModifiedTask.ReminderData.tm_mon = TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderData.tm_mon;
										}

										if (NewModifiedTask.ReminderData.tm_mday != 0)
										{
											TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderData.tm_mday = NewModifiedTask.ReminderData.tm_mday;
										}
										else
										{
											NewModifiedTask.ReminderData.tm_mday = TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderData.tm_mday;
										}

										if (NewModifiedTask.ReminderData.tm_hour != 0)
										{
											TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderData.tm_hour = NewModifiedTask.ReminderData.tm_hour;
										}
										else
										{
											NewModifiedTask.ReminderData.tm_hour = TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderData.tm_hour;
										}

										if (NewModifiedTask.ReminderData.tm_min != 0)
										{
											TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderData.tm_min = NewModifiedTask.ReminderData.tm_min;
										}
										else
										{
											NewModifiedTask.ReminderData.tm_min = TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).ReminderData.tm_min;
										}
										break;
									}

									SaveStateHandler.open(SaveStatePath, std::ios::in);
									TempSaveStateHandler.open(FilePointState, std::ios::out);

									while (!SaveStateHandler.eof() && std::getline(SaveStateHandler, DataLineHandler))
									{
										PayloadHandler.clear();
										std::stringstream TempDataHandler(DataLineHandler);

										for (DataLineHandler; std::getline(TempDataHandler, ConvertedHandler, ','); PayloadHandler.push_back(ConvertedHandler))
											;

										if (PayloadHandler[0] != TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).TaskID)
										{
											if (!SaveStateHandler.eof())
											{
												for (unsigned short IterHandler_UnShort = INIT_BASE_NUM; IterHandler_UnShort < PayloadHandler.size(); IterHandler_UnShort++)
												{
													TempSaveStateHandler << PayloadHandler[IterHandler_UnShort] << (IterHandler_UnShort == (PayloadHandler.size() - ADJUST_BY_ONE) ? "\n" : ",");
												}
											}
										}
										else
										{
											if (!SaveStateHandler.eof())
											{
												TempSaveStateHandler << NewModifiedTask.TaskID << "," << NewModifiedTask.TaskName << "," << NewModifiedTask.TaskInCharge << "," << NewModifiedTask.ReminderType << "," << mktime(&NewModifiedTask.ReminderData) << "\n";
											}
										}
									}

									SaveStateHandler.close();
									TempSaveStateHandler.close();

									remove(SaveStatePath);
									rename(FilePointState, SaveStatePath);

									std::cout << std::endl
											  << "\t[CONFIRMATION, SUCCESS] |> Task Modification @ '" << TaskList.at(IterHandler_UnInt - ADJUST_BY_ONE).TaskName << "' is now applied~!";
									DelayRunTimeBy(SLEEP_OPRT_FINISHED);
									continue;
								}
								catch (...)
								{
									std::cout << std::endl
											  << "\t[PROCESS] Unknown error has occured...";
									DelayRunTimeBy(SLEEP_SIGNIFICANT_ERR);
									continue;
								}

							case CONFIRMED_FALSE_LOWER:
							case CONFIRMED_FALSE_UPPER:
								std::cout << std::endl
										  << "\t[CONFIRMATION, SUCCESS] |> Task Deletion Cancelled.";
								DelayRunTimeBy(SLEEP_OPRT_FINISHED);
								continue;

							default:
								std::cout << std::endl
										  << "\t[CONFIRMATION, ERROR] |> User Input Invalid.";
								std::cin.clear();
								BufferClear_STDIN('\n');
								DelayRunTimeBy(SLEEP_OPRT_FAILED);
								continue;
							}
						}
					}
					else
					{
						std::cerr << std::endl
								  << "\t[INPUT ERROR] |> User Requested To Delete Tasks Non-Existent or Out of Range...";
						DelayRunTimeBy(SLEEP_ERROR_PROMPT);
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
			std::cerr << std::endl
					  << "\t[VIEW INFO] > Task Queue is currently empty! Please add some task/s.";
			DelayRunTimeBy(SLEEP_OPRT_FINISHED);
			break;
		}
	}
	return;
}
void TTRM::DC_VTask()
{
	ConsoleCall("CLS");
	std::cout << std::endl
			  << std::endl
			  << "\t";
	PrintConsoleASCII(ASCII_VLDivider, 1);
	PrintConsoleASCII(ASCII_HDivider, 3);
	std::cout << " Currently Available Reminders To Trigger From The Queue System ";
	PrintConsoleASCII(ASCII_HDivider, 25);
	PrintConsoleASCII(ASCII_VRDivider, 1);
	std::cout << std::endl;
	SP_DisplayTasks(ViewTask);
	std::cout << std::endl
			  << "\t";
	PrintConsoleASCII(ASCII_VLDivider, 1);
	PrintConsoleASCII(ASCII_HDivider, 3);
	PrintConsoleASCII(ASCII_HDivider, 89);
	PrintConsoleASCII(ASCII_VRDivider, 1);
	std::cout << std::endl
			  << std::endl;
	std::cout << "\tPress any KEY to go back from System Menu.";
	_getche();
	return;
}

void TTRM::DC_RQT()
{
	char InputHandler_Char = NULL_CHAR;
	if (TaskList.size())
	{
		std::cout << std::endl
				  << std::endl
				  << "\t";
		PrintConsoleASCII(ASCII_VLDivider, 1);
		PrintConsoleASCII(ASCII_HDivider, 3);
		std::cout << " Task Queue and Save State Deletion - Confirmation ";
		PrintConsoleASCII(ASCII_HDivider, 20);
		PrintConsoleASCII(ASCII_VRDivider, 1);
		std::cout << std::endl
				  << std::endl
				  << "\t[WARNING] |> Are you sure you want delete all your tasks reminders from the queue system and save state?" << std::endl
				  << "\t[WARNING] |> This action is irreversible. Continue???" << std::endl
				  << "\t[INPUT  ] |> ['Y'es or 'N'o] |> ",
			std::cin >> InputHandler_Char;
		switch (InputHandler_Char)
		{
		case CONFIRMED_TRUE_LOWER:
		case CONFIRMED_TRUE_UPPER:
			remove(SaveStatePath);
			SaveStateHandler.open(SaveStatePath, std::ios::out);
			SaveStateHandler.close();
			TaskList.clear();
			std::cout << std::endl
					  << "\t[PROCESS] |> All Tasks Reminder Saved from the Queue System and Save States are Wiped!";
			DelayRunTimeBy(SLEEP_OPRT_FINISHED);
			break;
		case CONFIRMED_FALSE_LOWER:
		case CONFIRMED_FALSE_UPPER:
			std::cout << std::endl
					  << "\t[PROCESS] |> Task Reminder Queue and Save State Wipe Operation Cancelled.";
			DelayRunTimeBy(SLEEP_OPRT_FINISHED);
			break;
		default:
			std::cin.clear();
			BufferClear_STDIN('\n');
			std::cout << std::endl
					  << "\t[ERROR  ] |> Invalid Input. Task Reminder Queue and Save State Wipe Operation Cancelled.";
			DelayRunTimeBy(SLEEP_OPRT_FINISHED);
			break;
		}
		return;
	}
	else
	{
		std::cerr << std::endl
				  << "\t[INFORM ] Your Task List is currently empty! Please add one.";
		DelayRunTimeBy(SLEEP_OPRT_FINISHED);
		return;
	}
}

void TTRM::DC_RTLFSS()
{
	TTRM_TaskData SaveStateContainer;
	unsigned int IterHandler_UnInt = INIT_BASE_NUM;
	TaskList.clear();

	std::cout << std::endl
			  << "\t";
	PrintConsoleASCII(ASCII_VLDivider, 1);
	PrintConsoleASCII(ASCII_HDivider, 3);
	std::cout << " Updating Task List From Save State - Explicit ";
	PrintConsoleASCII(ASCII_HDivider, 24);
	PrintConsoleASCII(ASCII_VRDivider, 1);
	std::cout << std::endl
			  << std::endl
			  << "\tSave State Load  |> Refreshing List from Save State File." << std::endl;
	SaveStateHandler.open(SaveStatePath, std::ios::in);
	if (SaveStateHandler.is_open())
	{
		std::cout << "\tSave State Load  |> SaveState File Opened! Collecting Reminders to Queue System.";
		while (std::getline(SaveStateHandler, DataLineHandler))
		{
			std::cout << ".";
			PayloadHandler.clear();
			std::stringstream RowHandler(DataLineHandler);

			while (std::getline(RowHandler, ConvertedHandler, ','))
			{
				PayloadHandler.push_back(ConvertedHandler);
			}
			SaveStateContainer.TaskID = PayloadHandler[0];
			SaveStateContainer.TaskName = PayloadHandler[1];
			SaveStateContainer.TaskInCharge = PayloadHandler[2];
			SaveStateContainer.ReminderType = std::stoi(PayloadHandler[3]);
			time_t EpochHandler = std::stoll(PayloadHandler[4]);
			SaveStateContainer.TempTM = localtime(&EpochHandler);
			SaveStateContainer.ReminderData = *SaveStateContainer.TempTM;
			++IterHandler_UnInt;
			TaskList.push_back(SaveStateContainer);
		}
		SaveStateHandler.close();
		std::cout << std::endl
				  << std::endl
				  << "\tSave State Loaded |> Done. Loaded " << IterHandler_UnInt << " Reminders!" << std::endl;
		std::cout << std::endl
				  << "\t";
		PrintConsoleASCII(ASCII_VLDivider, 1);
		PrintConsoleASCII(ASCII_HDivider, 3);
		PrintConsoleASCII(ASCII_HDivider, 71);
		PrintConsoleASCII(ASCII_VRDivider, 1);
	}
	else
	{
		std::cout << std::endl
				  << "\tSave State Create |> Save File Doesn't Exist. Creating Save File..." << std::endl;
		TempSaveStateHandler.open(FilePointState, std::ios::out);
		if (TempSaveStateHandler.is_open())
		{
			std::cout << "\tSave State Create |> SaveState File Created!" << std::endl;
			TempSaveStateHandler.close();
			rename(FilePointState, SaveStatePath);
			std::cout << std::endl
					  << "\t";
			PrintConsoleASCII(ASCII_VLDivider, 1);
			PrintConsoleASCII(ASCII_HDivider, 3);
			PrintConsoleASCII(ASCII_HDivider, 71);
			PrintConsoleASCII(ASCII_VRDivider, 1);
		}
		else
		{
			std::cout << "\tSave State Create |> SaveState File Creation Failure. Fatal Error | Terminating Program" << std::endl;
			std::cout << std::endl
					  << "\t";
			PrintConsoleASCII(ASCII_VLDivider, 1);
			PrintConsoleASCII(ASCII_HDivider, 3);
			PrintConsoleASCII(ASCII_HDivider, 71);
			PrintConsoleASCII(ASCII_VRDivider, 1);
			std::cout << std::endl
					  << std::endl;
			TTRM::~TTRM(); // ! Calls Destructors Because This Function is VOID. So we terminate, explicitly.
		}
	}
	SaveStateHandler.close();
	DelayRunTimeBy(SLEEP_OPRT_FINISHED);
	return;
}

// ! CORE FUNCTION CONTENT DECLARATION - END POINT

// * ----------------------------------------------------------------------------

// ! TECHNICAL FUNCTION CONTENT DECLARATION - STARTING POINT

// ! WinToast FUNCTION CONTENT DECLARATION - STARTING POINT

// ! These Functions Only Does Those...
void TTRM_WinToast::toastActivated() const
{
	; //WinToast_ReturnTrigger = SNOOZE_REMINDER;
}
void TTRM_WinToast::toastActivated(int actionIndex) const
{
	if (!actionIndex)
	{
		WinToast_ReturnTrigger = SNOOZE_REMINDER;
	}
	else
	{
		WinToast_ReturnTrigger = DISCARD_REMINDER;
	}
}
void TTRM_WinToast::toastDismissed(WinToastDismissalReason state) const
{
	switch (state)
	{
	case UserCanceled:
		WinToast_ReturnTrigger = DISCARD_REMINDER;
		break;
	case TimedOut:
	case ApplicationHidden:
		WinToast_ReturnTrigger = SNOOZE_REMINDER;
		break;
	default:
		WinToast_ReturnTrigger = IGNORE_REMINDER;
		break;
	}
}
void TTRM_WinToast::toastFailed() const
{
	; //WinToast_ReturnTrigger = DISCARD_REMINDER;
}

// ! WinToast FUNCTION CONTENT DECLARATION - END POINT

/*
	# Task To Remind Me Core Definitions | TTRM_CoreDef.cpp
    # File Category Type: Core Function Body Definition
	# Version: Version Post.06042020.1955

	# Created by Janrey Licas | http://github.com/CodexLink
	! Licensed in GPL-3.0 | See LICENSE.md for more information.
*/