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
	char *token_list[20], *path, **env = **environ, *env_token;
	pid_t pid, wait_child;
	int executable, i;

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
		
				env_token = strtok(env, ":");

				while (env_token)
				{
					
					for (env = environ; *env != NULL; env++)
					{
						putstr(*env);
					}

					env_token = strtok(NULL, ":");
				}
				

			}
			free(command);

			if (_strcmp(token_list[0], "exit") == 0)
			{
				free(command);
				exit(EXIT_SUCCESS);
			}


			pid = fork();

			/* It returns -1 if it fails */
			if (pid == -1)
			{
				free(command);
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

				/* Generate the path to the first command(file name)before execution */
				path = get_path(token_list[0]);

				/* Handle the case when path is NULL (executable not found) */
				if (path == NULL)
				{
					perror(shellname);
					free(command);
					exit(EXIT_FAILURE);
				}

				executable = execve(path, token_list, NULL);

				if (executable == -1)
				{
					perror(shellname);
					free(command);
					exit(EXIT_FAILURE);
				}

				free(command);
				exit(EXIT_SUCCESS);
			}

			/* In the parent process, fork returns the pid */
			else
			{
				wait_child = wait(NULL);

				if (wait_child == -1)
				{
					free(command);
					perror("wait failed");
					exit(EXIT_FAILURE);
				}
			}
		}
	}
}
