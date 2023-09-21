#include "shell.h"

int (*get_builtin(char *command))(char **args);
int fshell_exit(char **args);


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
	/*	{ "env", fshell_env }, */
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
 * Return: Exits with the given status value, or 0 if not given.
 */
int fshell_exit(char **args)
{
	int status = 0;

	if (args[1])
		status = str_to_int(args[1]);

	free_args(args);
	exit(status);
}
