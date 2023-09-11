#include "shell.h"

/**
 * handle_ctrl_c - Prints a new prompt When catching <Ctrl + C> signal.
 *
 * @signum: The signal number.
 */
void handle_ctrl_c(int signum)
{
	UNUSED(signum);

	write(STDIN_FILENO, "\n", 1);
	write(STDIN_FILENO, ">>> ", 4);
}
