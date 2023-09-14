#include "shell.h"


void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);


/**
 * _realloc - Reallocates a dynamic memory block.
 *
 * @ptr: A pointer to a memory block previously allocated.
 * @old_size: The size in bytes of the allocated space for ptr.
 * @new_size: The size in bytes for the new memory block.
 *
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 or you are poor (insufficient RAM) - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr, *ptr_copy;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	for (i = 0; (i < old_size) && (i < new_size); i++)
		new_ptr[i] = ptr_copy[i];

	free(ptr);
	return (new_ptr);
}
