/* Task To Remind Me C++ CLI using Win32 API = RIP Portabiltiy
    Primarily Created for Data Structure and Algorithm Basic Level Class
    Initially Created by Janrey "CodexLink" Licas, 08/15/2019, 15:35
    Represented as Data Struct Group 7
*/

#include "TechProSpEssential.h"

// THIS Main Function will only able to receive up to 5 maximum parameters.
TTRM_ClassInitializer Sys;

int main(unsigned short argc, char *argv[])
{
    (!argc) ? Sys.ParseGivenParam(argc, argv) : (RETURN_NULL);
    return TERM_SUCCESS;
}