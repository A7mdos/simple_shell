#include "shell.h"

int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, int n);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, int n);



/**
 * _strlen - calculates the length of a string
 *
 * @s: the string to get the length of
 *
 * Return: the length of the string
 */
int _strlen(const char *s)
{
	int i = 0, length = 0;

	while (s[i++] != '\0')
		length++;

	return (length);
}
