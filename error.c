#include "shell.h"

/**
 * write_error - Writes an error message to stderr.
 *
 * @args: Array of arguments including the command name.
 * @err: The error's value.
 *
 * Return: The error's value.
 */
int write_error(char **args, int err)
{
	char *error_msg;

	/*TODO: create an error struct instead of using switch */
	switch (err)
	{
	case 126:
		error_msg = error_126(args);
		break;
	case 127:
		error_msg = error_127(args);
		break;
	case 2:
		error_msg = error_2(args);
		break;
	case 69:
		error_msg = error_env(args);
		break;
	}

	write(STDERR_FILENO, error_msg, _strlen(error_msg));

	if (error_msg)
		free(error_msg);

	return (err);
}
