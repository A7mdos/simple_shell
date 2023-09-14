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
	char *env_var, *new_var;
	char **new_environ;
	size_t envsize = 0,
		   name_len = _strlen(name),
		   value_len = _strlen(value);
	int i;

	env_var = _getenv(name);

	new_var = malloc(sizeof(char) * (name_len + 1 + value_len + 1));
	if (!new_var)
		return (-1);

	_strcpy(new_var, name);
	_strcat(new_var, "=");
	_strcat(new_var, value);

	while (environ[envsize])
		envsize++;

	if (env_var)
		new_environ = malloc(sizeof(char *) * (envsize + 1));
	else
		new_environ = malloc(sizeof(char *) * (envsize + 2));
	if (!new_environ)
	{
		free(new_var);
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
			free(new_var);
			return (-1);
		}
		_strcpy(new_environ[i], environ[i]);
	}

	environ = new_environ;
	env_var = _getenv(name);

	if (env_var && overwrite)
	{
		env_var = new_var;
		return (0);
	}

	environ[i] = new_var;
	environ[i + 1] = NULL;

	return (0);
}


/**
 * _unsetenv - Deletes an environment variable.
 *
 * @name: The name of the environment variable to delete.
 *
 * Return: If you are poor (insufficient RAM) - -1.
 *         Otherwise - 0.
 */
int _unsetenv(const char *name)
{
	char *env_var;
	char **new_environ;
	size_t envsize = 0;
	int i, j;

	env_var = _getenv(name);
	if (!env_var)
		return (0);

	while (environ[envsize])
		envsize++;

	new_environ = malloc(sizeof(char *) * envsize);
	if (!new_environ)
		return (-1);

	for (i = 0, j = 0;
		 environ[i];
		 i++, j++)
	{
		if (env_var == environ[i])
			continue;

		new_environ[j] = malloc(_strlen(environ[i] + 1));
		if (!new_environ[j])
		{
			for (j--; j >= 0; j--)
				free(new_environ[j]);
			free(new_environ);
			return (-1);
		}

		_strcpy(new_environ[j], environ[i]);
	}

	environ = new_environ;
	environ[envsize - 1] = NULL;

	return (0);
}
