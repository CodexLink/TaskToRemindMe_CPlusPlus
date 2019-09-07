/* Task To Remind Me C++ CLI using Win32 API = RIP Portabiltiy
    Primarily Created for Data Structure and Algorithm Basic Level Class
    Initially Created by Janrey "CodexLink" Licas, 08/15/2019, 15:35
    Represented as Data Struct Group 7
*/

#include "__TTRM_SourceCore/TTRM_Core.h"

TTRM CoreFunction;

// We insist to use std::vector. But for the sake of accomplishing only said goals. We'll be go to std::queue;
	

std::queue<TTRM_TaskData> TaskList;

int main(unsigned short argc, char *argv[])
{
    if (argc > POS_OFFSET_BY_ONE)
		  CoreFunction.ParseGivenParam(argc, argv);
    
    if (!CoreFunction.ComponentCheck(IGNORE_PROCESS))
		return TERM_FAILED;
    
	CoreFunction.runSystemMenu();

	//End Scope. TTRM Should Call Destructors.
}