#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);
char *error_2(char **args);
char *error_env(char **args);


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
	int error_len;
	char *command = args[0];

	history_str = int_to_str(history);
	if (!history_str)
		return (NULL);

	error_len = _strlen(program_name) + _strlen(history_str) +
				_strlen(command) + 24;
	error_msg = malloc(sizeof(char) * (error_len + 1));
	if (!error_msg)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error_msg, program_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, history_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, command);
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
	int error_len;
	char *command = args[0];

	history_str = int_to_str(history);
	if (!history_str)
		return (NULL);

	error_len = _strlen(program_name) + _strlen(history_str) +
				_strlen(command) + 16;
	error_msg = malloc(sizeof(char) * (error_len + 1));
	if (!error_msg)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error_msg, program_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, history_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, command);
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
	int error_len;
	char *trash = args[1];

	history_str = int_to_str(history);
	if (!history_str)
		return (NULL);

	error_len = _strlen(program_name) + _strlen(history_str) +
				_strlen(trash) + 27;
	error_msg = malloc(sizeof(char) * (error_len + 1));
	if (!error_msg)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error_msg, program_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, history_str);
	_strcat(error_msg, ": exit: Illegal number: ");
	_strcat(error_msg, trash);
	_strcat(error_msg, "\n");

	free(history_str);
	return (error_msg);
}


/**
 * error_env - Creates an error message for fshell_env errors.
 *
 * @args: An array of arguments including the command.
 *
 * Return: The error message string.
 */
char *error_env(char **args)
{
	char *error_msg, *history_str;
	int error_len;
	char *command = args[0];

	history_str = int_to_str(history);
	if (!history_str)
		return (NULL);

	error_len = _strlen(program_name) + _strlen(history_str) +
				_strlen(command) + 45;
	error_msg = malloc(sizeof(char) * (error_len + 1));
	if (!error_msg)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error_msg, program_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, history_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, command);
	_strcat(error_msg, ": Unable to add/remove from environment\n");

	free(history_str);
	return (error_msg);
}
