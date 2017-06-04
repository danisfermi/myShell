#include<stdio.h>
#include<stdlib.h>
// Read and Parse from Config File
void readConfig()
{
	FILE *fptr;
	char line[500];
	fptr=fopen("config","r");
	if (fptr==NULL)
	{
		printf("\nUnable to find config file.");
		return 1;
	}
	else
	{
		while(fgets(line,sizeof(line),file) != NULL)
		{
			// Code to Parse Config File
		}
	}
	fclose(fptr);
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
