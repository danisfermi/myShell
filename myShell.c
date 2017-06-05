#include<stdio.h>
#include<stdlib.h>

// Function to read a line from command into the buffer
char *readLine()
{
	char *line = (char *)malloc(sizeof(char)*1024); // Dynamically Allocate Buffer
	char c;
	int pos=0, bufsize=1024;
	if (!line) // Buffer Allocation Failed
	{
		printf("\nBuffer Allocation Error.");
		exit(EXIT_FAILURE);
	}
	while(TRUE)
	{
		c=getchar(c);
		if (c==EOF || c=='\n') // If End of File or New line, replace with Null character
		{
			line[pos]='\0';
			return line;
		}
		else
		{
			line[pos]=c;
		}
		pos++;
		// If we have exceeded the buffer
		if (pos>=bufsize)
		{
			bufsize+=1024;
			line=realloc(line, 1024);
			if (!line) // Buffer Allocation Failed
			{
			printf("\nBuffer Allocation Error.");
			exit(EXIT_FAILURE);
			}
		}
	}

}

// Read and Parse from Config File
char SHELL_NAME[50] = "myShell";
int QUIT = 0;
int readConfig()
{
	FILE *fptr;
	char line[200];
	fptr=fopen("config", "r");
	if (fptr==NULL)
	{
		printf("Unable to find config file.");
		return 1;
	}
	else
	{
		while(fgets(line, sizeof(line), fptr)!= NULL)
		{
			printf("\n%s", line);
			// Code to Parse Config File
		}
	}
	fclose(fptr);
	return 1;
}

// When myShell is called Interactively
int myShellInteract()
{
	char *line;
	char **args;
	while(QUIT!=0)
	{
		printf("%s> ", SHELL_NAME);
		line=readLine();
		args=splitLine(line);
		execLine(args);
		free(line);
		free(args);
	}
	return 1;
}

// When myShell is called with a Script as Argument
int myShellScript(char filename[100])
{
	printf("Received Script. Opening %s", filename);
	FILE *fptr;
	fptr=fopen(filename, "r");
	if (fptr==NULL)
	{
		printf("\nUnable to open file.");
		return 1;
	}
	else
	{
		printf("\nFile Opened. Parsing.");
		while(fgets(line, sizeof(line), fptr)!= NULL)
		{
			printf("\n%s", line);
			// Code to Parse Config File
		}
	}
	fclose(fptr);
	return 1;
}

int main(int argc, char **argv)
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