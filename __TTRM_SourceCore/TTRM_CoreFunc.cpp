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
	std::cout << std::endl << "Function Execution Done...";
}

bool TTRM::ComponentCheck(bool isNeededToRun)
{
	if (isNeededToRun)
	{
		return TERM_SUCCESS;
	}
	else
	{
		return TERM_FAILED;
	}
}

bool TTRM::runSystemMenu(void) const
{
	char DisplayMenu_Input = INIT_CHAR_NULL;
	while (NOT_REQ_TERM)
	{
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
			<< std::endl << "10 |> Terminate Program"
			<< std::endl << std::endl;

		std::cout << "[Input] Your Choice |> ";
		switch (_getche())
		{
		case AddTask:
			break;
		case DeleteTask:
			break;
		case EditTask:
			break;
		case ViewTask:
			break;
		case ManualDatabaseRefresh:
			break;
		case RequeueTasks:
			break;
		case AutoStartup:
			break;
		case WinToastIntegration:
			break;
		case Termination:
			break;
		}
		break;
	}
	return RETURN_BACK_NOTHING;
}