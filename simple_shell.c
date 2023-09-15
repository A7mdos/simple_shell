#include "shell.h"


/**
 * execute - Executes a command in a child process.
 *
 * @args: An array of the command with its arguments.
 *
 * Return: If an error occurs - an appropriate error code.
 *         Otherwise - The exit value of the last executed command.
 */
int execute(char **args)
{
	pid_t fork_pid;
	int status, ret;
	char *command = args[0];

	fork_pid = fork();
	if (fork_pid == -1)
	{
		perror("Error child");
		return (1);
	}
	if (fork_pid == 0) /* child process */
	{
		if (execve(command, args, environ) == -1)
		{
			perror("Error");
			exit(1);
		}
	}
	else /* parent process */
	{
		wait(&status);
		ret = WEXITSTATUS(status);
	}

	return (ret);
}


/**
 * get_args - Reads and tokenizes arguments from the command line.
 *
 * @args: A pointer to an array to store the tokenized arguments.
 *
 * Return: If an error occurs - -1 or CTRL_D.
 *         Otherwise - the tokenized array of arguments.
 */
int get_args(char ***args)
{
	size_t n = 0;
	ssize_t nread;
	char *line = NULL;

	nread = getline(&line, &n, stdin);
	if (nread == -1 || nread == 1)
		free(line);

	if (nread == 1) /*Enter -only- was read (Could it be sth other than Enter?)*/
	{
		write(STDOUT_FILENO, ">>> ", 4);
		return (get_args(args));
	}
	if (nread == -1)
		return (CTRL_D);

	line[nread - 1] = '\0';
	*args = strsplit(line, " ");
	if (!*args)
		return (ESPLT);

	free(line);
	return (0);
}


/**
 * free_args - Frees up memory taken by an array of arguments.
 *
 * @args: A NULL-terminated array of strings (arguments) to be freed.
 */
void free_args(char **args)
{
	size_t i = 0;

	while (args[i] != NULL)
		free(args[i++]);
	free(args);
}


/**
 * main - A simple UNIX command interpreter.
 *
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	char **args = NULL;
	int sui;
	pid_t fork_pid;
	int status;

	signal(SIGINT, handle_ctrl_c);

	while (1)
	{
		write(STDOUT_FILENO, ">>> ", 4);

		sui = get_args(&args);
		if (sui == CTRL_D)
		{
			write(STDIN_FILENO, "\n", 1);
			exit(0);
		}
		if (sui == ESPLT)
		{
			perror("Failed to tokenize");
			continue;
		}

		execute(args);
		free_args(args);
	}

	return (0);
}


/**
 * Some concerns:
 *
 * - I replace '\n' with '\0' so the end of the line becomes '\0' '\0'
 *		maybe I should just remove '\n' ?
 * - Ending input with Ctrl + D.
 */
