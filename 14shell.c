#include "shell.h"
/**
 * main - this initializes the variables of the program
 * @argc: thie number of values received from the command line
 * @argv: this is values received from the command line
 * @env: this is number of values received from the command line
 * Return: prints zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	inicialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* prints We are in the terminal, interactive mode */
		errno = 2;/*????????*/
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - this prints the prompt in a new line
 * when a signal SIGINT (ctrl + c) is sent to a program
 * @UNUSED: this is option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * inicialize_data - this initializes the struct with the info of the program
 * @data: this is pointer to the structure of data
 * @argv: this is array of arguments pased to the program execution
 * @env: the environ passed to a program execution
 * @argc: the number of values received from the command line
 */
void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/* this defines the file descriptor to be read*/
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
/**
 * sisifo - this is a infinite loop that shows the prompt
 * @prompt: this prompt to print
 * @data: this is a infinite loop that shows the prompt
 */
void sisifo(char *prompt, data_of_program *data)
{
	int error_code = 0, strings_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = strings_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno); /* prints  if EOF is the fisrt Char of string, exit*/
		}
		if (strings_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* prints if a text is given to prompt, execute */
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}
