#include "main.h"

/**
 * execute_command - executes a command.
 * Prototype: void execute_command(char *command, char *shellname);
 * @command: a string of characters (command + arguments)
 * @shellname: the name chosen at compilation.
 * Return: void
 */
void execute_command(char *command, char *shellname)
{
	char *token_list[20], *path;
	pid_t pid, wait_child;
	int i;

	if (command == NULL)
	{
		perror("Command is NULL");
		exit(EXIT_FAILURE);
	}
	else
	{
		token_list[0] = strtok(command, " \n");

		if (token_list[0] != NULL)
		{
			if (_strcmp(token_list[0], "env") == 0)
			{
				print_environment();
			}
			free(command);

			if (_strcmp(token_list[0], "exit") == 0)
			{
				free(command);
				exit(EXIT_SUCCESS);
			}

			/* Create a separate function for command execution */
			execute_command_helper(token_list, shellname);
		}
	}
}

/**
 * execute_command_helper - executes the command in the child process.
 * Prototype: void execute_command_helper(char *token_list[], char *shellname);
 * @token_list: array of command tokens
 * @shellname: the name chosen at compilation.
 * Return: void
 */
void execute_command_helper(char *token_list[], char *shellname)
{
	pid_t pid, wait_child;
	int executable, i;

	pid = fork();

	/* It returns -1 if it fails */
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}

	/* In the child process, fork returns 0 */
	if (pid == 0)
	{
		for (i = 1; token_list[i - 1] != NULL; i++)
		{
			token_list[i] = strtok(NULL, " \n");
		}

		/* Generate the path to the first command (file name) before execution */
		char *path = get_path(token_list[0]);

		/* Handle the case when path is NULL (executable not found) */
		if (path == NULL)
		{
			perror(shellname);
			free(token_list[0]);  // Free the command token
			exit(EXIT_FAILURE);
		}

		executable = execve(path, token_list, NULL);

		if (executable == -1)
		{
			perror(shellname);
			free(token_list[0]);  // Free the command token
			exit(EXIT_FAILURE);
		}

		free(token_list[0]);  // Free the command token
		exit(EXIT_SUCCESS);
	}

	/* In the parent process, fork returns the pid */
	else
	{
		wait_child = wait(NULL);

		if (wait_child == -1)
		{
			perror("wait failed");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * print_environment - prints environment variables.
 * Prototype: void print_environment(void);
 * Return: void
 */
void print_environment()
{
	char **env = environ;

	while (*env != NULL)
	{
		putstr(*env);
		env++;
	}
}
