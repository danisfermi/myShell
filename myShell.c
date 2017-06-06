#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For strtok() and strcmp()
#include <unistd.h> // For fork(), pid_t
#include <sys/wait.h> // For waitpid() and associated macros

// Function to read a line from command into the buffer
char *readLine()
{
	char *line = (char *)malloc(sizeof(char) * 1024); // Dynamically Allocate Buffer
	char c;
	int pos = 0, bufsize = 1024;
	if (!line) // Buffer Allocation Failed
	{
		printf("\nBuffer Allocation Error.");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		c=getchar();
		if (c == EOF || c == '\n') // If End of File or New line, replace with Null character
		{
			line[pos] = '\0';
			return line;
		}
		else
		{
			line[pos] = c;
		}
		pos ++;
		// If we have exceeded the buffer
		if (pos >= bufsize)
		{
			bufsize += 1024;
			line = realloc(line, sizeof(char) * bufsize);
			if (!line) // Buffer Allocation Failed
			{
			printf("\nBuffer Allocation Error.");
			exit(EXIT_FAILURE);
			}
		}
	}

}

// Function to split a line into constituent commands
char **splitLine(char *line)
{
	char **tokens = (char **)malloc(sizeof(char *) * 64);
	char *token;
	char delim[10] = " \t\n\r\a";
	int pos = 0, bufsize = 64;
	if (!tokens)
	{
		printf("\nBuffer Allocation Error.");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, delim);
	while (token != NULL)
	{
		tokens[pos] = token;
		pos ++;
		if (pos >= bufsize)
		{
			bufsize += 64;
			line = realloc(line, bufsize * sizeof(char *));
			if (!line) // Buffer Allocation Failed
			{
			printf("\nBuffer Allocation Error.");
			exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delim);
	}
	tokens[pos] = NULL;
	return tokens;
}

// Function to create child process and run command
int myShellLaunch(char **args)
{
	pid_t pid, wpid;
	int status;
	pid = fork();
	if (pid == 0)
	{
		// The Child Process
		if (execvp(args[0], args) == -1)
		{
			perror("myShell: ");
		}
	exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		//Forking Error
		perror("myShell: ");
	}
	else
	{
		// The Parent Process
	do 
	{
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

// Function to execute command from terminal
int execShell(char **args)
{
	return 1;
}

// Read and Parse from Config File
char SHELL_NAME[50] = "myShell";
int QUIT = 0;
int readConfig()
{
	FILE *fptr;
	char line[200];
	fptr = fopen("config", "r");
	if (fptr == NULL)
	{
		printf("Unable to find config file.\n");
		return 1;
	}
	else
	{
		while(fgets(line, sizeof(line), fptr) != NULL)
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
	while(QUIT == 0)
	{
		printf("%s> ", SHELL_NAME);
		line=readLine();
		args=splitLine(line);
		execShell(args);
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
	char line[200];
	fptr = fopen(filename, "r");
	if (fptr == NULL)
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
	if (argc == 1)
		myShellInteract();
	else if (argc == 2)
		myShellScript(argv[1]);
	else
		printf("\nInvalid Number of Arguments");

	// Exit the Shell
	return EXIT_SUCCESS;
}