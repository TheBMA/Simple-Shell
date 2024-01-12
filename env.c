#include "main.h"
/**
 * get_environment - prints environment variables.
 * Return: void
 */
void get_environment(void)
{
	char **env = environ;

	for (; *env != NULL ; env++)
	{
		putstr(*env);
		putstr("\n");
	}

}
