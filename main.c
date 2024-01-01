#include "main.h"

/**
 * main - simple shell
 *
 * Return: 0
 */

int main(void)
{
	char *buffer;

	while (1)
	{
		write(STDOUT_FILENO, "Cash $ ", 7);
		buffer = take_command();
		execute_command(buffer);
		free(buffer);
	}

	return (0);
}

/**
 * take_command - takes a command line from standard input using getline
 * Prototype: char *take_command(void);
 * (which is better? getline or read?)
 * Return: the command line.
 */

char *take_command(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t read;

	/*getline doesn't take STDIN_FILENO or 0 as input*/
	read = getline(&command, &len, stdin);

	if (read == -1)
	{
		write(STDERR_FILENO, "Can't read command", 18);
		exit(1);
	}

	return (command);
}

/**
 * execute_command - executes a command.
 * Prototype: void execute_command(char *command);
 * @command: a string of characters (command + arguments)
 * (currently doesn't do anything)
 * Return: void
 */

void execute_command(char *command)
{
	size_t len = 0, i = 0;

	if (command == NULL)
		write(STDOUT_FILENO, "\n", 1);
	else if (*command == '\n')
		;
	else
	{
		while (command[i] != '\0')
		{
			len++;
			i++;
		}

		write(STDOUT_FILENO, "Cash $: ", 8);
		write(STDOUT_FILENO, command, len - 1);
		write(STDOUT_FILENO, " command not found\n", 19);
	}
}
