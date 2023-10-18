#include "main.h"

/**
 * builtins_list -this searches for a match and executes
 * the associate builtin.
 * @data: the struct for the program's data
 * Return: this Returns the return of the executed function
 * execute if there is a match,
 * otherwise only return -1.
 **/
int builtins_list(data_of_program *data)
{
	int iterator;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};
	/* this walks through the structure */
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
		/* prints if there is a match between the given command and a builtin, */
		if (str_compare(options[iterator].builtin, data->command_name, 0))
		{
			/* this execute the function, and return the return value of the function */
			return (options[iterator].function(data));
		}
		/*prints if there is no match return -1 */
	}
	return (-1);
}
