#include "main.h"

/**
 * main - simple shell
 * @argc: arguments count
 * @argv: arguments vector
 * Return: 0
 */

int main(int argc, char *argv[])
{
	char *buffer;

	/*unused parameter*/
	(void)argc;

	while (1)
	{
		putstr("Cash $ ");
		buffer = take_command();
		execute_command(buffer, argv[0]);
		free(buffer);
	}

	return (0);
}

/**
 * putstr - prints a string to standard output
 * (basically a _putchar for strings)
 * Prototype: void putstr(char *str);
 * @str: the string to print
 * Return: void
 */

void putstr(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		write(STDOUT_FILENO, &str[i], 1);
}


/**
 * take_command - takes a command line from standard input using getline
 * Prototype: char *take_command(void);
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
		exit(EXIT_FAILURE);
	}

	return (command);
}

/**
 * execute_command - executes a command.
 * Prototype: void execute_command(char *command, char *shellname);
 * @command: a string of characters (command + arguments)
 * @shellname: the name chosen at compilation.
 * (currently takes the exit command)
 * Return: void
 */

void execute_command(char *command, char *shellname)
{
	char *token;

	if (command == NULL)
	{
		putstr("\n");
		write(STDERR_FILENO, "Command is NULL", 15);
		exit(EXIT_FAILURE);
	}

	else if (*command == '\n')
		;
	else
	{
		token = strtok(command, " \n");

		/* if strcmp is allowed */
		if (strcmp(token, "exit") == 0)
		{
			free(command);
			exit(EXIT_SUCCESS);
		}

		/*else handle if token is PATH or not*/

		putstr(shellname);
		putstr(": No such file or directory\n");
	}
}
