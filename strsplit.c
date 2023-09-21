#include "shell.h"


int word_len(char *str, char *delimiter);
int words_count(char *str, char *delimiter);
char **_strsplit(char *line, char *delimiter);

/**
 * word_len - Finds the delimiter index of the end
 *			  of the first word within a string.
 *
 * @str: The string to be split.
 * @delimiter: A pointer to the delimiter that
 *			   seperates tokens (words) in str.
 *
 * Return: The delimiter index marking the end of
 *         the intitial word pointed to be str.
 */
int word_len(char *str, char *delimiter)
{
	int i = 0, len = 0;

	while (str[i] && str[i] != *delimiter)
	{
		len++;
		i++;
	}

	return (len);
}


/**
 * words_count - Counts the number of words
 *               within a string.
 *
 * @str: The string to be split.
 * @delimiter: A pointer to the delimiter that
 *			   seperates tokens (words) in str.
 *
 * Return: The number of words contained within str.
 */
int words_count(char *str, char *delimiter)
{
	int i, words = 0, len;

	len = _strlen(str);

	for (i = 0; i < len; i++)
	{
		if (str[i] != *delimiter)
		{
			i += word_len(str + i, delimiter);
			words++;
		}
	}

	return (words);
}


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
char **strsplit(char *str, char *delimiter)
{
	int i = 0, words, t, letters, l;
	char **splt;

	words = words_count(str, delimiter);
	if (words == 0)
		return (NULL);

	splt = malloc(sizeof(char *) * (words + 2));
	if (!splt)
		return (NULL);

	for (t = 0; t < words; t++)
	{
		while (str[i] == *delimiter)
			i++;

		letters = word_len(str + i, delimiter);

		splt[t] = malloc(sizeof(char) * (letters + 1));
		if (!splt[t])
		{
			for (i -= 1; i >= 0; i--)
				free(splt[i]);
			free(splt);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			splt[t][l] = str[i];
			i++;
		}

		splt[t][l] = '\0';
	}
	splt[t] = NULL;
	splt[t + 1] = NULL;

	return (splt);
}
