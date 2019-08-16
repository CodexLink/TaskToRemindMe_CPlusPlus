#include "TechProSpEssential.h"

void TTRM_ClassInitializer::ParseGivenParam(unsigned short argcount, char *argv[])
{
    std::cout << "Hello World!" << std::endl;
	std::cout << "There is " << argcount << " parameters given and here are the following: ";
	for (auto i = 0; i < (sizeof(argv) / sizeof(argv[0])); i++)
	{
		std::cout << argv[i] << " ";
	}

	std::cout << std::endl << "Function Execution Done...";
	while (1);
}