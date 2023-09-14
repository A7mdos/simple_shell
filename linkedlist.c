#include "shell.h"


Node *add_node_end(Node **head, const char *dir);
void free_list(Node *head);
Node *build_path_dirs(char *paths);



/**
 * add_node_end - Adds a new node at the end
 *                of a linked list.
 *
 * @head: The adderss of a pointer to the head of the linked list.
 * @dir: The directory path (string) to be added to the new node.
 *
 * Return: If you are poor (insufficient RAM) - NULL.
 *         Otherwise - the address of the new element.
 */
Node *add_node_end(Node **head, const char *dir)
{
	Node *new_node, *tail_node;

	new_node = malloc(sizeof(Node));
	if (new_node == NULL)
		return (NULL);

	new_node->dir = dir;
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}

	tail_node = *head;
	while (tail_node->next != NULL)
		tail_node = tail_node->next;

	tail_node->next = new_node;

	return (new_node);
}


/**
 * free_list - Frees a linked list.
 *
 * @head: A pointer to the head of the linked list to be freed.
 */
void free_list(Node *head)
{
	Node *temp;

	while (head != NULL)
	{
		temp = head->next;
		free(head->dir);
		free(head);
		head = temp;
	}
}


/**
 * build_path_dirs - Builds a linked list of the PATH directories.
 *
 * @paths: The string containing colon-separated list of paths.
 *
 * Return: If you are poor (insufficient RAM) - NULL.
 *		   Otherwise - A pointer to the built linked list.
 *
 * Description: Splits the string of colon-separated paths into a linked list.
 */
Node *build_path_dirs(char *paths)
{
	char **dirs;
	Node *head = NULL;
	int i = 0;

	dirs = strsplit(paths, ":");
	if (!dirs)
		return (NULL);

	while (dirs[i])
	{
		if (add_node_end(&head, dirs[i]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
		i++;
	}

	free(dirs);

	return (head);
}
