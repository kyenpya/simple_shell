#include "main.h"

/**
 * long_to_string - this converts a number to a string.
 * @number: the number to be converted in an string.
 * @string: the buffer to save the number as string.
 * @base: this is the base to convert number
 *
 * Return: prints Nothing.
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long cociente = number;
	char letters[] = {"0123456789abcdef"};

	if (cociente == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (cociente)
	{
		if (cociente < 0)
			string[index++] = letters[-(cociente % base)];
		else
			string[index++] = letters[cociente % base];
		cociente /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	str_reverse(string);
}


/**
 * _atoi - this converts a string to an integer.
 *
 * @s: the pointer to str origin.
 * Return: prints int of string or 0.
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;
	/*1- print analisys sign*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	/*2 - this extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/**
 * count_characters - this counts the coincidences of character in string.
 *
 * @string: the pointer to str origin.
 * @character: the string with  chars to be counted
 * Return: prints int of string or 0.
 */
int count_characters(char *string, char *character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			counter++;
	}
	return (counter);
}
