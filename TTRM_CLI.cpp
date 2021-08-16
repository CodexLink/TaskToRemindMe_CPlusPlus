/*
 # Task To Remind Me C++ CLI | TTRM_CLI.cpp


*/

#include "TTRM_SRC/TTRM_CoreDecl.h"

TTRM Core(true, false);

bool prog_entrypoint();

int main(unsigned short argc, char *argv[])
{
	if (argc > Core.CONTAINS_ONE_ELEM)
		Core.ParseGivenParam(argc, argv);

	if (Core.Cmpnt_Initializer())
		Core.SP_DisplayMenu();

	std::cout << std::endl
						<< "\tPrograC:\\Windows\\System32\\m Termination |> Program Terminating at Console Close Sequence.";
	std::cout << std::endl
						<< std::endl
						<< "\tGroup Members at CPE21FB1 Data Structure Group 5\n\t\tProject Lead: 'Janrey Licas',\n\t\tSystem Director: 'Rejay Mar Senar'"
						<< std::endl;
	std::cout << std::endl
						<< "\tGoodbye.";
	DelayRunTimeBy(SLEEP::SLEEP_SYS_TERM);
	exit(FUNC_OOS);
}

//  Launches particular things before we start of.
bool prog_entrypoint()
{
}