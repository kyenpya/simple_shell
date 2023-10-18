#include "main.h"

int check_file(char *full_path);

/**
 * find_program -this finds a program in path
 * @data: this is a pointer to the program's data
 * Return: prints 0 if success, errcode otherwise
 */
int find_program(data_of_program *data)
{
	int i = 0, rets_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);

	/**prints if is a full_path or an executable in the same path */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data);/* this search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; directories[i]; i++)
	{/* this appends the function_name to path */
		directories[i] = str_concat(directories[i], data->tokens[0]);
		rets_code = check_file(directories[i]);
		if (rets_code == 0 || rets_code == 126)
		{/*
		  * print if the file was found,
		  * is not a directory and has execute permissions
		  */
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[i]);
			free_array_of_pointers(directories);
			return (rets_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (rets_code);
}

/**
 * tokenize_path - this  tokenize the path in directories
 * @data: this is a pointer to the program's data
 * Return: the array of path directories
 */
char **tokenize_path(data_of_program *data)
{
	int i = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	/* this gets the PATH value*/
	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{ / this is path not found /
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	/* this finds the number of directories in the PATH */
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			counter_directories++;
	}

	/* this reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * counter_directories);

	/ this tokenize and duplicate each token of path /
	i = 0;
	tokens[i] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file - this checks if exists a file, if it is not a directory and
 * if it has execution permissions for permissions.
 * @full_path: the pointer to the full file name
 * Return: print 0 on success, or error code if it exists.
 */
int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/ print if not exist the file /
	errno = 127;
	return (127);
}
