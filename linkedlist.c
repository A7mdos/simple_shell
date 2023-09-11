#include "shell.h"


Node *add_node_end(Node **head, const char *dir);
void free_list(Node *head);
Node *get_path_dir(char *paths);



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
