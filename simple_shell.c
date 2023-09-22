#include "shell.h"


int execute(char **args);
int get_args(char ***args);
int run_args(char ***args);
void free_args(char **args);

char *program_name;
int history;
int status;
char *prompt;
int prompt_size;

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
	int ret = 0;

	UNUSED(argc);

	program_name = argv[0];
	history = 1;
	status = 0;
	prompt = ">>> ";
	prompt_size = _strlen(prompt);
	signal(SIGINT, handle_ctrl_c);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, prompt_size);
		ret = run_args(&args);
		if (ret == END_OF_FILE)
			exit(status);
	}

	return (status);
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
	int ret = 0, allocated_command = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		command = get_location(command);
		allocated_command = 1;
	}

	if (!command)
		return (write_error(args, 127));

	if (access(command, F_OK) == -1)
	{
		if (allocated_command)
			free(command);
		return (write_error(args, 127));
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
		if (allocated_command)
			free(command);
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
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, prompt_size);
		history++;
		return (get_args(args_ptr)); /* Be aware of the call stack */
	}
	if (nread == -1) /* Ctrl+D or END_OF_FILE*/
		return (END_OF_FILE);

	line[nread - 1] = '\0';
	*args_ptr = strsplit(line, " ");

	free(line);

	if (!*args_ptr)
		return (SPLT_ERR);

	return (0);
}


/**
 * run_args - Gets arguments, executes them if required
 *			  and modifies the status.
 *
 * @args_ptr: A pointer to an array to store the arguments.
 *
 * Return: If tokenization failed - SPLT_ERR.
 *		   If EOF was read - END_OF_FILE.
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
		return (END_OF_FILE);
	}

	command = *args_ptr[0];
	if (!command)
		return (0);

	builtin = get_builtin(command);
	if (builtin)
		status = builtin(*args_ptr);
	else
		status = execute(*args_ptr);

	history++;

	free_args(*args_ptr);
	return (status);
}


/**
 * free_args - Frees up memory taken by an array of arguments.
 *
 * @args: A NULL-terminated array of strings (arguments) to be freed.
 */
void free_args(char **args)
{
	size_t i = 0;

	if (args)
	{
		while (args[i] != NULL)
			free(args[i++]);
		free(args);
	}
}
