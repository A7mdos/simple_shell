#include "shell.h"

/* strdup() is not allowed - Implement ur own */

char *_strchr(char *s, char c);
char *_strstr(char *haystack, char *needle);
char *_strcpy(char *dest, const char *src);
char *_strncpy(char *dest, const char *src, int n);
char *_strdup(char *str);

/**
 * _strchr - Locates a character in a string.
 *
 * @s: The string to be searched.
 * @c: The character to be located.
 *
 * Return: If @c is found, a pointer to the first occurence.
 *         If @c is not found, NULL.
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (s + i);

		i++;
	}

	if (s[i] == c)
		return (s + i);

	return ('\0');
}
/**
 * _strstr - Locates a substring.
 *
 * @haystack: The string to be searched.
 * @needle: The substring to be located.
 *
 * Return: If the substring is located, a pointer to the beginning
 *                                       of the located substring.
 *         If the substring is not located, NULL.
 */

char *_strstr(char *haystack, char *needle)
{
	int i, j;

	i = 0;
	while (haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] != '\0')
		{
			if (haystack[i + j] != needle[j])
				break;

			j++;
		}

		if (needle[j] == '\0')
			return (haystack + i);

		i++;
	}

	return ('\0');
}
