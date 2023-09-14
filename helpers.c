#include "shell.h"


int num_len(int n);
char *int_to_str(int n);
int str_to_int(char *str);


/**
 * num_len - Calculates the number of digits in an integer.
 *
 * @n: The integer to find the length of.
 *
 * Return: The length (number of digits) of the integer.
 */
int num_len(int n)
{
	unsigned int num;
	int len = 1;

	if (n < 0)
	{
		num = n * -1;
		len++;
	}
	else
	{
		num = n;
	}

	while (num >= 10)
	{
		num /= 10;
		len++;
	}

	return (len);
}

/**
 * int_to_str - Converts an integer to a string.
 *
 * @n: The integer to be converted.
 *
 * Return: The converted string.
 *
 * Description: A sufficient memory area is allocated for the string.
 */
char *int_to_str(int n)
{
	unsigned int num;
	int len = num_len(n);
	char *str;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);

	if (n < 0)
	{
		num = n * -1;
		str[0] = '-';
	}
	else
	{
		num = n;
	}

	str[len] = '\0';

	len--;
	do {
		str[len] = (num % 10) + '0';
		num /= 10;
		len--;
	} while (num > 0);

	return (str);
}


/**
 * str_to_int - convert a string to an integer
 *
 * @str: the string to be converted
 *
 * Return: the extracted integer from the string
 */
int str_to_int(char *str)
{
	int sign = 1, digit;
	unsigned int number = 0;
	char chr = *str;

	while (chr != '\0')
	{
		if (chr == '-')
		{
			sign *= -1;
		}
		else if (chr >= '0' && chr <= '9')
		{
			digit = chr - '0';
			number = number * 10 + digit;
		}
		else if (number)
		{
			break;
		}

		str++;
		chr = *str;
	}

	return (sign * number);
}
