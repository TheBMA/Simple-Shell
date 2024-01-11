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
	char *token_list[20];

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
				get_environment(void);
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
 * create_child_process - Creates a new child process using fork().
 *
 * Return: Process ID of the child in the parent,
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
 * execute_command_in_child - Executes a command in a child process.
 *
 * @token_list: An array of command tokens
 * @shellname: The name of the shell cmd
 * Return: Exit status of the child process.
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
		free(token_list[0]);
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
 * wait_for_child -  Waits for the termination of a child process.
 *
 * @pid: Process ID of the child process.
 * (Unused attribute is optional.)
 * Return: On success, returns the process ID of the terminated child.
 * On failure, returns -1.
 */
void wait_for_child(pid_t pid __attribute__((unused)))
{
	int wait_child = wait(NULL);

	if (wait_child == -1)
	{
		perror("wait failed");
		exit(EXIT_FAILURE);
	}
}
/**
 * execute_command_helper -  Executes a command in a child process
 * and waits for its completion.
 * @token_list:  Array of command tokens.
 * @shellname:  - Name of the shell program.
 *
 * Return: void.
*/
void execute_command_helper(char *token_list[], char *shellname)
{
	pid_t pid = create_child_process();

	if (pid == 0)
	{
		execute_command_in_child(token_list, shellname);
	}
	else
	{
		/*Code in the parent process*/
		wait_for_child(pid);
	}
}
