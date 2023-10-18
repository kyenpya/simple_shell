#include "main.h"

/**
 * str_length - this returns the length of a string.
 * @string: This represents the reference to a string.
 * Return: this is the length of string.
 */
int str_length(char *string)
{
	int length = 0;

	if (string == NULL)
		return (0);

	while (string[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * str_duplicate - this duplicates only string
 * @string: this is the String to be copied
 * Return: this is pointer to the array
 */
char *str_duplicate(char *string)
{
	char *result;
	int length, i;

	if (string == NULL)
		return (NULL);

	length = str_length(string) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < length ; i++)
	{
		result[i] = string[i];
	}

	return (result);
}

/**
 * str_compare - this Compares two strings
 * @string3: this is String one, or the shorter
 * @string4: this is String two, or the longer
 * @number: the number of characters to be compared, 0 if infinite
 * Return: prints 1 if the strings are equals,0 if the strings are different
 */
int str_compare(char *string3, char *string4, int number)
{
	int iterator;

	if (string3 == NULL && string4 == NULL)
		return (1);

	if (string3 == NULL || string4 == NULL)
		return (0);

	if (number == 0) /* infinite longitud */
	{
		if (str_length(string3) != str_length(string4))
			return (0);
		for (iterator = 0; string3[iterator]; iterator++)
		{
			if (string3[iterator] != string4[iterator])
				return (0);
		}
		return (1);
	}
	else /* prints if there is a number of chars to be compared */
	{
		for (iterator = 0; iterator < number ; iterator++)
		{
			if (string3[iterator] != string4[iterator])
			return (0);
		}
		return (1);
	}
}

/**
 * str_concat - this concatenates two strings.
 * @string3: this is String to be concatenated
 * @string4: this is String to be concatenated
 *
 * Return: this is pointer to the array
 */
char *str_concat(char *string3, char *string4)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (string3 == NULL)
		string3 = "";
	length1 = str_length(string3);

	if (string4 == NULL)
		string4 = "";
	length2 = str_length(string4);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* this is copy of string3 */
	for (length1 = 0; string3[length1] != '\0'; length1++)
		result[length1] = string3[length1];
	free(string3);

	/* this is copy of string4 */
	for (length2 = 0; string4[length2] != '\0'; length2++)
	{
		result[length1] = string4[length2];
		length1++;
	}

	result[length1] = '\0';
	return (result);
}


/**
 * str_reverse - this reverses a string.
 *
 * @string: This represents the reference to a string.
 * Return: prints void.
 */
void str_reverse(char *string)
{

	int i = 0, length = str_length(string) - 1;
	char hold;

	while (i < length)
	{
		hold = string[i];
		string[i++] = string[length];
		string[length--] = hold;
	}
}
