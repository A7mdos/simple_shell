#include "shell.h"

int (*get_builtin(char *command))(char **args);
int fshell_exit(char **args);
int fshell_env(char **args);
int fshell_setenv(char **args);


/**
 * get_builtin - Gets the corresponding fshell builtin
 *               function for a given command name.
 *
 * @command: The builtin command's name.
 *
 * Return: if the command is not an fshell builtin - NULL
 *		   Otherwise - A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *command))(char **args)
{
	int i;
	Builtin builtins[] = {
		{ "exit", fshell_exit },
		{ "env", fshell_env },
		{ "setenv", fshell_setenv },
	/*	{ "unsetenv", fshell_unsetenv }, */
		{ NULL, NULL }
	};

	for (i = 0; builtins[i].name; i++)
		if (_strcmp(builtins[i].name, command) == 0)
			return (builtins[i].func);

	return (NULL);
}


/**
 * fshell_exit - Causes normal process termination
 *				 for the fshell shell.
 *
 * @args: An array of arguments containing the exit value.
 *
 * Return: If exit status is invalid - 2
 *		   Otherwise - exits with the given status value,
 *					   or the previous if not given.
 */
int fshell_exit(char **args)
{
	int i;
	char *exit_arg = args[1];

	if (exit_arg)
	{
		for (i = 0; exit_arg[i]; i++)
		/*TODO numbers starting with a '+' shouldn't be considered invalid */
			if (exit_arg[i] < '0' || exit_arg[i] > '9')
				return (write_error(args, 2));

		status = str_to_int(exit_arg);
	}

	free_args(args);
	exit(status);
}


/**
 * fshell_env - Prints the current environment.
 *
 * @args: An array of arguments to the env command (including the command).
 *
 * Return: If no enviroment is available - -1.
 *		   Otherwise - 0.
 */
int fshell_env(char **args)
{
	int i;

	UNUSED(args);

	if (!environ)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}


/**
 * fshell_setenv - Initializes a new environment variable,
 *				   or modifies an existing one.
 *
 * @args: An array of arguments to the setenv command (including the command).
 *
 * Return: If an error occurs - 69.
 *         Otherwise - 0.
 */
int fshell_setenv(char **args)
{
	char **env_var = NULL, **new_environ, *new_var,
		 *name = args[1],
		 *value = args[2];
	size_t name_len, value_len, envsize = 0;
	int i;

	if (!name || !value)
		return (write_error(args, 69));

	name_len = _strlen(name);
	value_len = _strlen(value);
	new_var = malloc(name_len + 1 + value_len + 1);
	if (!new_var)
		return (write_error(args, 69));

	_strcpy(new_var, name);
	_strcat(new_var, "=");
	_strcat(new_var, value);

	env_var = _getenv(name);
	if (env_var)
	{
		*env_var = new_var;
		return (0);
	}

	while (environ[envsize])
		envsize++;

	new_environ = malloc(sizeof(char *) * (envsize + 2));
	if (!new_environ)
	{
		free(new_var);
		return (write_error(args, 69));
	}

	for (i = 0; environ[i]; i++)
		new_environ[i] = environ[i];

	environ = new_environ;
	environ[i] = new_var;
	environ[i + 1] = NULL;

	return (0);
}
