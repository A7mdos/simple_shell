#include "shell.h"


char **_getenv(char *name);
/*int _unsetenv(char *name);*/


/**
 * _getenv - Gets an environment variable.
 *
 * @name: The name of the environment variable to get.
 *
 * Return: If the environment variable does not exist - NULL.
 *         Otherwise - a pointer to the environment variable.
 */
char **_getenv(char *name)
{
	int i = 0, len;

	len = _strlen(name);
	while (environ[i])
	{
		if (_strncmp(name, environ[i], len) == 0)
			return (&environ[i]);
		i++;
	}
	return (NULL);
}
