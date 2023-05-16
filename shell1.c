#include "shell.h"

void commandExec(char* line)
{
	pid_t pidline;

	pidline = fork();

	if (pidline == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pidline == 0)
	{
		if (execlp(line, line, (char *)NULL) == -1)
		{
			perror(line);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;
		waitpid(pidline, &status, 0);
	}
}
int main(void)
{
	char prompt[] ="#cisfun$ ";
	char line[BUFFER_SIZE];

	while (1)
	{
		printf("%s", prompt);

		if (fgets(line, BUFFER_SIZE, stdin) == NULL)
			break;
		line[strcspn(line, "\n")] = '\0';

		commandExec(line);
	}
	printf("\n");
	return (0);
}


