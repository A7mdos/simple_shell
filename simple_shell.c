#include "shell.h"


int execute(char **args);
int get_args(char ***args);
int run_args(char ***args);
void free_args(char **args);

char *program_name;
int history;


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
	int status, ret, allocated_command = 0;
	char *command = args[0];

	if (command[0] != '/')
	{
		command = get_location(command);
		allocated_command = 1;
	}

	fork_pid = fork();
	if (fork_pid == -1) /* fork failed */
	{
		if (allocated_command)
			free(command);
		perror("Error child");
		return (1);
	}
	if (fork_pid == 0) /* child process */
	{
		if (!command || (access(command, F_OK) == -1))
			return(write_error(args, 127));

		if (access(command, X_OK) == -1)
			return (write_error(args, 126));

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
 * Return: If tokenization failed - SPLT_ERR.
 *         Otherwise - 0.
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
		return (get_args(args)); /* Be aware of the call stack */
	}
	if (nread == -1) /* Ctrl+D */
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}

	line[nread - 1] = '\0';
	*args = strsplit(line, " ");
	if (!*args)
		return (SPLT_ERR);

	free(line);
	return (0);
}


/**
 * run_args - Gets arguments and executes them if required.
 *
 * @args: A pointer to an array to store the arguments.
 *
 * Return: If tokenization failed - SPLT_ERR.
 *		   If an error occurs - an appropriate error code.
 *         Otherwise - The exit value of the last executed command.
 */
int run_args(char ***args)
{
	int ret;

	ret = get_args(args);
	if (ret == SPLT_ERR)
		return (SPLT_ERR);

	ret = execute(*args);
	history++;

	free_args(*args);
	return (ret);
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
 * @argc: Arguments count.
 * @argv: Arguments vector
 *
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	char **args = NULL;
	int sui;
	pid_t fork_pid;
	int status;

	program_name = argv[0];
	history = 1;
	signal(SIGINT, handle_ctrl_c);

	while (1)
	{
		write(STDOUT_FILENO, ">>> ", 4);

		sui = run_args(&args);
		if (sui == SPLT_ERR)
			perror("Failed to tokenize");
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
