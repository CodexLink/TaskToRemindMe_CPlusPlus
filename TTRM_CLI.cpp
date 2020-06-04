/*
 # Task To Remind Me C++ CLI | TTRM_CLI.cpp


*/

#include "TTRM_SRC/TTRM_CoreDecl.h"

TTRM CoreFunction(tru);

int main(unsigned short argc, char *argv[])
{
	if (argc > CONTAINS_ONE_ELEM)
		CoreFunction.ParseGivenParam(argc, argv);

	if (CoreFunction.Cmpnt_Initializer())
		CoreFunction.SP_DisplayMenu();

	std::cout << std::endl
			  << "\tProgram Termination |> Program Terminating at Console Close Sequence.";
	std::cout << std::endl
			  << std::endl
			  << "\tGroup Members at CPE21FB1 Data Structure Group 5\n\t\tProject Lead: 'Janrey Licas',\n\t\tSystem Director: 'Rejay Mar Senar'"
			  << std::endl;
	std::cout << std::endl
			  << "\tGoodbye.";
	DelayRunTimeBy(SLEEP_SYS_TERM);
	exit(FUNC_OOS);
}