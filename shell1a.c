#include "shell.h"

#define BUFFER_SIZE 1024
/**
 *main - shell entry
 *
 * Return: 0
 */
int main(void)
{
	char disp[] = "#cisfun$ ";
	char commandEx[BUFFER_SIZE];

	pid_t pd;

	while (1)
	{
		printf("%s", disp);

		if (fgets(commandEx, BUFFER_SIZE, stdin) == NULL)
			break;

		commandEx[strcspn(commandEx, "\n")] = '\0';

		pd = fork();

		if (pd == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		} else if (pd == 0)
		{
			execlp(commandEx, commandEx, (char *)NULL);
			perror(commandEx);
			exit(EXIT_FAILURE);
		}
		else
		{
			int status;

			wait(&status);
		}
	}
	printf("\n");
	return (0);
}
