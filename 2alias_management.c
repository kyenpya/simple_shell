#include "shell.h"

/**
 * print_alias -this adds, remove or show aliases
 * @data: the struct for the program's data
 * @alias: the name of the alias to be printed
 * Return: print zero if sucess, or another number if
 * its declared in the arguments
 */
int print_alias(data_of_program *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (str_compare(data->alias_list[i], alias, alias_length)
				&&	data->alias_list[i][alias_length] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias -this adds, remove or show aliases
 * @data: the struct for the program's data
 * @name: the name of the requested alias.
 * Return: prints zero if sucess, or another number
 * if its declared in the arguments
 */
char *get_alias(data_of_program *data, char *name)
{
	int i, alias_length;

	/* this validate the arguments */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{/* this Iterates through the environ and check
	  * for coincidence of the varname
	  */
		if (str_compare(name, data->alias_list[i], alias_length) &&
			data->alias_list[i][alias_length] == '=')
		{/* this returns the value of the key NAME=  when find it */
			return (data->alias_list[i] + alias_length + 1);
		}
	}
	/* this returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias -this adds, or override alias
 * @alias_string: the alias to be seted in the form (name='value')
 * @data: the struct for the program's data
 * Return: prints zero if sucess, or other
 * number if its declared in the arguments
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/* this validate the arguments */
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	/* this Iterates alias to find = char */
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{/* this search if the value of the alias is another alias */
			temp = get_alias(data, alias_string + i + 1);
			break;
		}

	/*
	 *this Iterates through the alias list and check
	 * for coincidence of the varname
	 */
	for (j = 0; data->alias_list[j]; j++)
		if (str_compare(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{/*prints if the alias alredy exist */
			free(data->alias_list[j]);
			break;
		}

	/* this adds the alias */
	if (temp)
	{/* prints if the alias already exist */
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[j] = str_duplicate(buffer);
	}
	else /* prints if the alias does not exist */
		data->alias_list[j] = str_duplicate(alias_string);
	return (0);
}
