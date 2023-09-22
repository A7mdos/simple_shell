#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);
char *error_2(char **args);


/**
 * error_126 - Creates an error message for 'permission denied' failures.
 *
 * @args: An array of arguments including the command.
 *
 * Return: The error message string.
 */
char *error_126(char **args)
{
	char *error_msg, *history_str;
	int len;

	history_str = int_to_str(history);
	if (!history_str)
		return (NULL);

	len = _strlen(program_name) + _strlen(history_str) + _strlen(args[0]) + 24;
	error_msg = malloc(sizeof(char) * (len + 1));
	if (!error_msg)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error_msg, program_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, history_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, args[0]);
	_strcat(error_msg, ": Permission denied\n");

	free(history_str);
	return (error_msg);
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
	char *error_msg, *history_str;
	int len;

	history_str = int_to_str(history);
	if (!history_str)
		return (NULL);

	len = _strlen(program_name) + _strlen(history_str) + _strlen(args[0]) + 16;
	error_msg = malloc(sizeof(char) * (len + 1));
	if (!error_msg)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error_msg, program_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, history_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, args[0]);
	_strcat(error_msg, ": not found\n");

	free(history_str);
	return (error_msg);
}


/**
 * error_2 - Creates an error message for 'Illegal number' errors.
 *
 * @args: An array of arguments including the command.
 *
 * Return: The error message string.
 */
char *error_2(char **args)
{
	char *error_msg, *history_str;
	int len;

	history_str = int_to_str(history);
	if (!history_str)
		return (NULL);

	len = _strlen(program_name) + _strlen(history_str) + _strlen(args[0]) + 27;
	error_msg = malloc(sizeof(char) * (len + 1));
	if (!error_msg)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error_msg, program_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, history_str);
	_strcat(error_msg, ": exit: Illegal number: ");
	_strcat(error_msg, args[0]);
	_strcat(error_msg, "\n");

	free(history_str);
	return (error_msg);
}
