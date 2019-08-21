/* Task To Remind Me C++ CLI using Win32 API = RIP Portabiltiy
    Primarily Created for Data Structure and Algorithm Basic Level Class
    Initially Created by Janrey "CodexLink" Licas, 08/15/2019, 15:35
    Represented as Data Struct Group 7
*/

#include "TTRM_Core.h"

TTRM CoreFunction;

int main(unsigned short argc, char *argv[])
{
    if (argc > POS_OFFSET_BY_ONE)
		  CoreFunction.ParseGivenParam(argc, argv);
    
    if (!CoreFunction.ComponentCheck(IGNORE_PROCESS))
    {
      return TERM_FAILED;
    }

	CoreFunction.DisplayMenu();

	exit(TERM_SUCCESS);
}