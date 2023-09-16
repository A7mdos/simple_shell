#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - Creates an error message for 'permission denied' failures.
 *
 * @args: An array of arguments including the command.
 *
 * Return: The error message string.
 */
char *error_126(char **args)
{
	char *error, *history_str;
	int len;

	history_str = int_to_str(history);
	if (!history_str)
		return (NULL);

	len = _strlen(program_name) + _strlen(history_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, program_name);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(history_str);
	return (error);
}

/**
 * error_127 - Creates an error message for 'command not found' failures.
 *
 * @args: An array of arguments including the command.
 *
 * Return: The error message string.
 */
char *error_127(char **args)
{
	char *error, *history_str;
	int len;

	history_str = int_to_str(history);
	if (!history_str)
		return (NULL);

	len = _strlen(program_name) + _strlen(history_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, program_name);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(history_str);
	return (error);
}
