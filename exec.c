#include "main.h"

/**
 * create_child_process - Creates a new child process using fork.
 *
 * Return: The process ID of the child in the parent,
 * 0 in the child, or -1 on failure.
 */
pid_t create_child_process(void)
{
pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}

	return (pid);
}

/**
 * execute_command_in_child - Executes a command in the child process.
 *
 * @token_list: Array of command tokens.
 * @shellname: Name of the shell program.
 *
 * Return: void.
 */
void execute_command_in_child(char *token_list[], char *shellname)
{
	int executable, i;
	char *path;

	for (i = 1; token_list[i - 1] != NULL; i++)
	{
		token_list[i] = strtok(NULL, " \n");
	}

	/* Generate the path to the first command (file name) before execution */
	path = get_path(token_list[0]);

	/* Handle the case when path is NULL (executable not found) */
	if (path == NULL)
	{
		perror(shellname);
		/*free(token_list[0]);*/
		exit(EXIT_FAILURE);
	}

	executable = execve(path, token_list, NULL);

	if (executable == -1)
	{
		perror(shellname);
		free(token_list[0]);
		exit(EXIT_FAILURE);
	}

	free(token_list[0]);
	exit(EXIT_SUCCESS);
}

/**
 * wait_for_child - Handles the parent process after forking.
 *
 * @command: A string of characters (command + arguments).
 *
 * Return: void.
 */
void wait_for_child(char *command)
{
	pid_t wait_child = wait(NULL);

	if (wait_child == -1)
	{
		free(command);
		perror("wait failed");
		exit(EXIT_FAILURE);
	}
}

/**
 * execute_command - Executes a command.
 * @command: A string of characters (command + arguments).
 * @shellname: The name chosen at compilation.
 *
 * Return: void.
 */
void execute_command(char *command, char *shellname)
{
	char *token_list[20];
	pid_t pid;

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
			if (_strcmp(token_list[0], "exit") == 0)
			{
				free(command);
				exit(EXIT_SUCCESS);
			}
			if (_strcmp(token_list[0], "env") == 0)
			{
				get_environment();
			}

			pid = create_child_process();

			/* In the child process, fork returns 0 */
			if (pid == 0)
			{
				execute_command_in_child(token_list, shellname);
			}
			/* In the parent process, fork returns the pid */
			else
			{
				wait_for_child(command);
			}
		}
	}
}
