#include "shell.h"


int execute(char **args);
int get_args(char ***args);
int run_args(char ***args);
void free_args(char **args);

char *program_name;
int history;


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
	int exe_ret;

	UNUSED(argc);

	program_name = argv[0];
	history = 1;
	signal(SIGINT, handle_ctrl_c);

	if (!isatty(STDIN_FILENO))
	{
		while (1)
			run_args(&args);

	}

	while (1)
	{
		write(STDOUT_FILENO, ">>> ", 4);

		exe_ret = run_args(&args);
		if (exe_ret == SPLT_ERR)
			perror("Failed to tokenize");
	}

	return (0);
}



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

	if (command[0] != '/' && command[0] != '.')
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
		if (!command)
			return (write_error(args, 127));

		if (access(command, F_OK) == -1)
			return (write_error(args, 127));

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
 * @args_ptr: A pointer to an array to store the tokenized arguments.
 *
 * Return: If tokenization failed - SPLT_ERR.
 *		   If EOF was read - END_OF_FILE.
 *         Otherwise, on success - 0.
 */
int get_args(char ***args_ptr)
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
		return (get_args(args_ptr)); /* Be aware of the call stack */
	}
	if (nread == -1) /* Ctrl+D or END_OF_FILE*/
		return (END_OF_FILE);

	line[nread - 1] = '\0';
	*args_ptr = strsplit(line, " ");
	if (!*args_ptr)
		return (SPLT_ERR);

	free(line);
	return (0);
}


/**
 * run_args - Gets arguments and executes them if required.
 *
 * @args_ptr: A pointer to an array to store the arguments.
 *
 * Return: If tokenization failed - SPLT_ERR.
 *		   If an error occurs - an appropriate error code.
 *         Otherwise - The exit value of the last executed command.
 */
int run_args(char ***args_ptr)
{
	int ret;
	int (*builtin)(char **args);
	char *command;

	ret = get_args(args_ptr);
	if (ret == SPLT_ERR)
		return (SPLT_ERR);
	if (ret == END_OF_FILE)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}

	command = *args_ptr[0];
	if (!command)
		return (0);

	builtin = get_builtin(command);
	if (builtin)
		ret = builtin(*args_ptr);
	else
		ret = execute(*args_ptr);

	history++;

	free_args(*args_ptr);
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
