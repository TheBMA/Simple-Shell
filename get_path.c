#include "main.h"

/**
 * full_path - provides directories which hold the command (full path)
 * @command: the file to look for
 * Return: pointer to the path of the file
*/
char *get_path(char *command)
{
    extern char **environ;
	char path[BUFFER_SIZE], *ptr_path, **env = environ, *paths, *path_token;
	int i = 0;

	if (access(command, F_OK) == 0)
		return (command);
	while (env[i] != NULL)
	{
		if (_strcmp(env[i], "PATH=") == 0)
		{
			paths = _strdup(env[i] + 5);
			path_token = strtok(paths, ":");
			while (path_token)
			{
				ptr_path = _strcpy(path, path_token);
				ptr_path = _strcat(path, "/");
				ptr_path = _strdup(_strcat(path, command));
				if (access(ptr_path, X_OK) == 0)
				{
					free(paths);
					return (ptr_path);
				}
				free(ptr_path);
				path_token = strtok(NULL, ":");
			}
			free(paths);
		}
		i++;
	}
	return (NULL);
}