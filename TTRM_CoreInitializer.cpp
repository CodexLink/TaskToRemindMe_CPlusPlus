/* Task To Remind Me C++ CLI using Win32 API = RIP Portabiltiy
    Primarily Created for Data Structure and Algorithm Basic Level Class
    Initially Created by Janrey "CodexLink" Licas, 08/15/2019, 15:35
    Represented as Data Struct Group 5
*/

#include "__TTRM_SourceCore/TTRM_CoreDeclarations.h"

TTRM CoreFunction;

int main(unsigned short argc, char *argv[])
{
    if (argc > CONTAINS_ONE_ELEM)
		  CoreFunction.ParseGivenParam(argc, argv);
    
	if (CoreFunction.Cmpnt_Initializer())
        CoreFunction.SP_DisplayMenu();
	
	std::cout << std::endl << "\tProgram Termination |> Program Terminating at Console Close Sequence.";
	std::cout << std::endl
		<< std::endl
		<< "\tGroup Members at CPE21FB1 Data Structure Group 5\n\t\tProject Lead: 'Janrey Licas',\n\t\tSystem Director: 'Rejay Mar Senar'"
		<< std::endl;
	std::cout << std::endl << "\tGoodbye.";
	DelayRunTimeBy(SLEEP_SYS_TERM);
	exit(FUNC_OOS);
}