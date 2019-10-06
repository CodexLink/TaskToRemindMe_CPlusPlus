/* Task To Remind Me C++ CLI using Win32 API = RIP Portabiltiy
    Primarily Created for Data Structure and Algorithm Basic Level Class
    Initially Created by Janrey "CodexLink" Licas, 08/15/2019, 15:35
    Represented as Data Struct Group 7
*/

#include "__TTRM_SourceCore/TTRM_CoreDeclarations.h"

TTRM CoreFunction;

int main(unsigned short argc, char *argv[])
{
    if (argc > CONTAINS_ONE_ELEM)
		  CoreFunction.ParseGivenParam(argc, argv);
    
    if (!CoreFunction.ComponentCheck(RUN_PROCESS))
		return CoreFunction.TERM_FAILED;
    
	CoreFunction.runSystemMenu();

	//End Scope. TTRM Should Call Destructors.
}