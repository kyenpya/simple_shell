#include "main.h"

/**
 * env_get_key -this gets the value of an environment variable
 * @key: this is the environment variable of interest
 * @data: the struct of the program's data
 * Return:this is a pointer to the value of the
 * variable or NULL if it doesn't exist
 */
char *env_get_key(char *key, data_of_program *data)
{
	int i, keys_length = 0;

	/* this validates the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* this obtains the leng of the variable requested */
	keys_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* this Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->env[i], keys_length) &&
		 data->env[i][keys_length] == '=')
		{/* this returns the value of the key NAME=  when find it*/
			return (data->env[i] + keys_length + 1);
		}
	}
	/* this returns NULL if did not find it */
	return (NULL);
}

/**
 * env_set_key -this overwrites the value of the environment variable
 * or creates another it if does not exist.
 * @key: this is the name of the variable to set
 * @value: the new value
 * @data: the struct of the program's data
 * Return: prints 1 if the parameters are NULL,
 * 2 if there is an erroror 0 if sucess.
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int i, keys_length = 0, is_new_key = 1;

	/* this validates the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* this obtains the leng of the variable requested */
	keys_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* this Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->env[i], keys_length) &&
		 data->env[i][keys_length] == '=')
		{/* prints If key already exists */
			is_new_key = 0;
			/* this frees the entire variable, it is new created below */
			free(data->env[i]);
			break;
		}
	}
	/* this makes an string of the form key=value */
	data->env[i] = str_concat(str_duplicate(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (is_new_key)
	{/*
	  * prints if the variable is new, it is created at
	  * end of actual list and we need
	  */
	/* this is to put the NULL value in the next position */
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - this removes a key from the environment
 * @key: this is the key to remove
 * @data: this is the sructure of the program's data
 * Return: prints 1 if the key was removed, 0 if the key does not exist;
 */
int env_remove_key(char *key, data_of_program *data)
{
	int i, keys_length = 0;

	/* this validates the arguments */
	if (key == NULL || data->env == NULL)
		return (0);

	/* this obtains the leng of the variable requested */
	keys_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* this iterates through the environ and checks for coincidences */
		if (str_compare(key, data->env[i], keys_length) &&
		 data->env[i][keys_length] == '=')
		{/* prints if key already exists, remove them */
			free(data->env[i]);

			/* this moves the others keys one position down */
			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			/* this puts the NULL value at the new end of the list */
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - this prints the current environ
 * @data: the struct for the program's data
 * Return: prints nothing
 */
void print_environ(data_of_program *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}
