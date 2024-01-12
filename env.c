#include "main.h"
/**
 * get_environment - prints environment variables.
 * Return: void
 */
void get_environment(void)
{
	char **env = environ, *env_token;

	env_token = strtok(*env, ":");
	
	while (*env != NULL)
	{
		while (env_token != NULL)
		{
			putstr(*env);
			putstr("\n");
			env_token = strtok(NULL, ":");
		}

		env++;
	}

}
