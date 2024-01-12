#include "main.h"
/**
 * get_environment - prints environment variables.
 * Prototype: void print_environment(void);
 * Return: void
 */
void get_environment(void)
{
	char **env = environ, *env_token;

	while (*env != NULL)
	{
		env_token = strtok(*env, ":");

		while (env_token != NULL)
		{
			putstr(*env);
			env_token = strtok(NULL, ":");
		}
		env++;
	}
}
