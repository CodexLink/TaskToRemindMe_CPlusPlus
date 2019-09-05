/*
    Technical Project Specific Essential Function CPP File by Janrey "CodexLink" Licas
    File Category Type: Core Function Body Definition, "CoreFunc".
	This CPP file will only contain 
*/

#include "TTRM_Core.h"


void TTRM::ParseGivenParam(unsigned short argcount, char *argv[])
{
	unsigned int ParamIter = INIT_NULL;
    std::cout << "Task To Remind Me C++ in CLI version. BETA" << std::endl << std::endl;
	std::cout << "Created by Data Structure Group 5, Group Members {\n Header Core Developer: 'Janrey Licas',\n AppFlow Director: 'Rejay Mar'\n};" << std::endl << std::endl;
	std::cout << "[Perform Parameter Given] |> Counted Parameter: " << argcount << std::endl;
	while (!strcmp(argv[ParamIter], "") && ParamIter != LIMIT_ARGC_COUNTER)
	{
		// Create more features here. Use switch for Selection of Data here.
		std::cout << " Parameter Index "<< ParamIter << " |> Parameter Value -> "<< argv[ParamIter] << std::endl;
	}
}

bool TTRM::ComponentCheck(bool isNeededToRun)
{
	std::cout << std::endl << "Function Execution Done...";
	WinToast::instance()->setAppName(L"CodexLink SmplTLKit Console Version");
	std::cout << "Application Name Loaded." << std::endl;
	WinToast::instance()->setAppUserModelId(WinToast::configureAUMI(L"Janrey", L"Licas",L"CodexLink's SmpleTLKit Beta Version", L"20180103"));
	std::cout << "Application Profile Loaded." << std::endl;
	if (!WinToast::instance()->initialize()) {
		std::wcout << L"Critical Error! Could not initialize the library!" << std::endl;
		Sleep(1000);
	}
	else {
		std::cout << "" << std::endl;
		std::wcout << L"WinToast Initialized. Header and Settings Handler Loaded." << std::endl;
	}
	WinToastTemplate StartupInitialization = WinToastTemplate(WinToastTemplate::Text02);
	StartupInitialization.setTextField(L"CodexLink SmplTLKit User Authentication", WinToastTemplate::FirstLine);
	StartupInitialization.setTextField(L"CodexLink has logged on. Welcome My Man!", WinToastTemplate::SecondLine);

	if (!WinToast::instance()->showToast(StartupInitialization, new TTRM_TechFunc)) {
		std::wcout << L"Error: Could not launch your toast notification!" << std::endl;
		Sleep(5000);
	}
	std::cout << "Demo WinToast Finished." << std::endl;
	while(1);
	if (isNeededToRun)
	{
		return TERM_SUCCESS;
	}
	else
	{
		return TERM_FAILED;
	}
}

signed short TTRM::runSystemMenu(void) const
{
	signed int DisplayMenu_Input = INIT_NULL;
	while (NOT_REQ_TERM)
	{
		WinAPI_CMDCall("CLS");
		std::cout << std::endl << "Task To Remind Me C++ in CLI version. BETA" << std::endl << std::endl;
		std::cout << "Time From Your Local System [Last Updated] |> " << std::endl;

		std::cout << std::endl << "=== Incoming Task for Today ====================" << std::endl << std::endl;
		std::cout << "=== Task Function Menu ====================" << std::endl
			<< std::endl << "1 |> Add a Task"
			<< std::endl << "2 |> Delete a Task"
			<< std::endl << "3 |> Edit a Task"
			<< std::endl << "4 |> View All Tasks"
			<< std::endl << "5 |> Sort All Tasks"
			<< std::endl << std::endl << "=== Technical Function Menu ====================" << std::endl
			<< std::endl << "6 |> Manually Refresh All Tasks from Database (Hard Reset)"
			<< std::endl << "7 |> Requeue All Tasks from Database (Soft Reset)"
			<< std::endl << "8 |> Auto-Start Application : Current Status > [" << "Unknown Yet]"
			<< std::endl << "9 |> WinToast Remind Integration: Current Status > [" << "Unknown Yet]"
			<< std::endl << "0 |> Terminate Program"
			<< std::endl << std::endl;

		std::cout << "[Input] Your Choice then PRESS ENTER |> ";
		std::cin >> DisplayMenu_Input;
		if (std::cin.fail())
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "[ERROR] CIN FAILED." << std::endl;
			delay_time(SLEEP_ERROR_PROMPT);
			continue;
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
		case RequeueTasks:
			MenuSel_ReqTasks();
			break;
		case AutoStartup:
			MenuSel_AutoStart();
			break;
		case WinToastIntegration:
			MenuSel_WTI();
			break;
		case Termination:
			break;
		default:
			std::cout << std::endl << "[ERROR] User Inputted Not Included in the List!" << std::endl;
			delay_time(SLEEP_ERROR_PROMPT);
			break;
		}
		if (!DisplayMenu_Input)	break;
	}
	return USER_OUTOFSCOPE_TERM_SUCCESS;
}

void TTRM::MenuSel_ATask(void) const
{
	WinAPI_CMDCall("CLS");
	// Add Design here
	std::cout << "Task Name |> ";
	std::cout << "1" << std::endl;
}
void TTRM::MenuSel_DTask(void) const
{
	WinAPI_CMDCall("CLS");
	std::cout << "2" << std::endl;
}
void TTRM::MenuSel_ETask(void) const
{
	WinAPI_CMDCall("CLS");
	std::cout << "3" << std::endl;
}
void TTRM::MenuSel_VTask(void) const
{
	WinAPI_CMDCall("CLS");
	std::cout << "4" << std::endl;
}
void TTRM::MenuSel_DBRefresh(void) const
{
	WinAPI_CMDCall("CLS");
	std::cout << "5" << std::endl;
}
void TTRM::MenuSel_ReqTasks(void) const
{
	WinAPI_CMDCall("CLS");
	std::cout << "6" << std::endl;
}
void TTRM::MenuSel_AutoStart(void) const
{
	WinAPI_CMDCall("CLS");
	std::cout << "7" << std::endl;
}
void TTRM::MenuSel_WTI(void) const
{
	WinAPI_CMDCall("CLS");
	std::cout << "8" << std::endl;
}