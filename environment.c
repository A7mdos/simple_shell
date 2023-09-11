#include "shell.h"


char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);


/**
 * _getenv - Gets an environment variable.
 *
 * @name: The name of the environment variable to get.
 *
 * Return: If the environment variable does not exist - NULL.
 *         Otherwise - a pointer to the environment variable.
 */
char *_getenv(const char *name)
{
	int i = 0, len;

	len = _strlen(name);
	while (environ[i])
	{
		if (_strncmp(name, environ[i], len) == 0)
			return (environ[i]);
		i++;
	}
	return (NULL);
}
