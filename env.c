#include "main.h"
/**
 * get_environment - prints environment variables.
 * Prototype: void print_environment(void);
 * Return: void
 */
void get_environment(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		putstr(*env);
		env++;
	}
}
