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
/**
 * _setenv - Changes or Adds an environment variable.
 *
 * @name: The name of the environment variable to change or add.
 * @value: The value of the environment variable to change or add.
 * @overwrite: A flag indicating if the variable should be overwritten.
 *
 * Return: If you are poor (insufficient RAM) - -1.
 *         Otherwise - 0.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	char *env_var, *new_value;
	char **new_environ;
	size_t envsize = 0;
	int i;
	size_t name_len = _strlen(name),
		   value_len = _strlen(value);

	env_var = _getenv(name);

	new_value = malloc(sizeof(char) * (name_len + 1 + value_len + 1));
	if (!new_value)
		return (-1);

	_strcpy(new_value, name);
	_strcat(new_value, "=");
	_strcat(new_value, value);

	while (environ[envsize])
		envsize++;

	if (env_var)
		new_environ = malloc(sizeof(char *) * (envsize + 1));
	else
		new_environ = malloc(sizeof(char *) * (envsize + 2));
	if (!new_environ)
	{
		free(new_value);
		return (-1);
	}

	for (i = 0; environ[i]; i++)
	{
		new_environ[i] = malloc(_strlen(environ[i] + 1));
		if (!new_environ[i])
		{
			for (i--; i >= 0; i--)
				free(new_environ[i]);
			free(new_environ);
			free(new_value);
			return (-1);
		}
		_strcpy(new_environ[i], environ[i]);
	}

	environ = new_environ;
	env_var = _getenv(name);

	if (env_var && overwrite)
	{
		env_var = new_value;
		return (0);
	}

	environ[i] = new_value;
	environ[i + 1] = NULL;

	return (0);
}
