#include "shell.h"

/**
 * strsplit - Splits a string into an array of words.
 *
 * @str: The string to be split.
 * @delimiter: A pointer to the delimiter that
 *			   seperates tokens (words) in str.
 *
 * Return: If you are poor (insufficient RAM) - NULL.
 *		   Otherwise - A NULL terminated array of strings
 *					   representing the seperated words.
 *
 * Description: This version does not affect the original string.
 *		Allocated memory should be freed later.
 */
char **strsplit(const char *str, const char *delimiter)
{
	char *str_copy = strdup(str);

	char **words;
	char *token = strtok(str_copy, delimiter);
	size_t count = 1;

	words = malloc(sizeof(char *));
	if (!words)
		return (NULL);

	while (token != NULL)
	{
		words = realloc(words, (count + 1) * sizeof(char *));
		if (!words)
			return (NULL);

		words[count - 1] = _strdup(token);
		words[count] = NULL;
		if (!words[count - 1])
			return (NULL);

		count++;
		token = strtok(NULL, delimiter);
	}

	free(str_copy);

	return (words);
}
