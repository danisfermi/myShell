#include<stdio.h>
#include<stdlib.h>
// Read and Parse from Config File
void readConfig()
{

}

// When myShell is called Interactively


// When myShell is called with a Script as Argument


int main(int argc, char *argv)
{
	// Read from myShell Configuration Files
	readConfig();
	// Parsing commands Interactive mode or Script Mode
	if (argc==0)
		myShellInteract();
	else if (argc==1)
		myShellScript(argv[1]);
	else
		printf("\nInvalid Number of Arguments");

	// Exit the Shell
	return EXIT_SUCCESS;
}
