/* Task To Remind Me C++ CLI using Win32 API = RIP Portabiltiy
    Primarily Created for Data Structure and Algorithm Basic Level Class
    Initially Created by Janrey "CodexLink" Licas, 08/15/2019, 15:35
    Represented as Data Struct Group 7
*/

#include "__TTRM_SourceCore/TTRM_CoreDeclares.h"

TTRM CoreFunction;

int main(unsigned short argc, char *argv[])
{
    //CoreFunction.MultiThreadHandler = (HANDLE)_beginthreadex(0, 0, &CoreFunction.MultiThread_ScanReminders, 0, 0, &CoreFunction.MultiThreadID);
    
    if (argc > POS_OFFSET_BY_ONE)
		  CoreFunction.ParseGivenParam(argc, argv);
    
    if (!CoreFunction.ComponentCheck(IGNORE_PROCESS))
		return CoreFunction.TERM_FAILED;
    
	CoreFunction.runSystemMenu();

	//End Scope. TTRM Should Call Destructors.
}