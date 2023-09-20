#include "shell.h"


/**
 * get_location - Locates a command in the PATH.
 *
 * @command: The command to locate.
 *
 * Return: If you are poor (insufficient RAM) or
 *		   the command cannot be located - NULL.
 *         Otherwise - A pointer to an allocated space for
 *					   the pathname of the command.
 */
char *get_location(char *command)
{
	char *PATH, *pathname;
	Node *head, *dir_node;
	struct stat st;

	PATH = _getenv("PATH");
	if (!PATH)
		return (NULL);

	head = build_path_dirs(PATH + 5);

	dir_node = head;
	while (dir_node)
	{
		pathname = malloc(_strlen(dir_node->dir) + _strlen(command) + 2);
		if (!pathname)
			return (NULL);

		_strcpy(pathname, dir_node->dir);
		_strcat(pathname, "/");
		_strcat(pathname, command);

		if (stat(pathname, &st) == 0)
		{
			free_list(head);
			return (pathname);
		}

		dir_node = dir_node->next;
		free(pathname);
	}

	free_list(head);

	return (NULL);
}
