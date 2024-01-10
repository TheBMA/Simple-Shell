#include "main.h"

/**
 * get_path - generates directories which hold the command (full path)
 * @command: the executable file to find
 * Return: pointer to the path of the file
*/
char *get_path(char *command)
{
	/***environ is defined externally and used to access the environment variables*/
    extern char **environ;
	char path[BUFFER_SIZE], *ptr_path, **env_var = environ, *path_cpy, *path_token;
	int i = 0;

	/**Checks the accessibiliy to the file and if it is*/
	if (access(command, F_OK) == 0)
		return (command);
	while (env_var[i] != NULL)
	{
		if (_strcmp(env_var[i], "PATH=") == 0)
		{
			/** extract the content of the environ skipping the 1st 5 caharcters PATH= **/
			path_cpy = _strdup(env_var[i] + 5);
			path_token = strtok(path_cpy, ":");

			while (path_token)
			{
				 /* to build the path for the command, we copy the directory path and concatenate the command to it */
				ptr_path = _strcpy(path, path_token);
				ptr_path = _strcat(path, "/");
				ptr_path = _strdup(_strcat(path, command));
				if (access(ptr_path, X_OK) == 0)
				{
					free(path_cpy);
					return (ptr_path);
				}
				free(ptr_path);
				path_token = strtok(NULL, ":");
			}
			free(path_cpy);
		}
		i++;
	}
	return (NULL);
}
