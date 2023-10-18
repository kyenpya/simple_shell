#include "main.h"
/**
 * execute - this executes a command with its entire path variables.
 * @data: this is a pointer to the program's data
 * Return: print If sucess returns zero, otherwise, return -1.
 */
int execute(data_of_program *data)
{
	int retval = 0, status;
	pid_t pidd;

	/* this check for program in built ins */
	retval = builtins_list(data);
	if (retval != -1)/* print if program was found in built ins */
		return (retval);

	/* this checks for program file system */
	retval = find_program(data);
	if (retval)
	{/* print if program not found */
		return (retval);
	}
	else
	{/* print if program was found */
		pidd = fork(); /* this create a child process */
		if (pidd == -1)
		{ /* print if the fork call failed */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/* print I am the child process, I execute the program*/
			retval = execve(data->tokens[0], data->tokens, data->env);
			if (retval == -1) /* print if error when execve*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* print I am the father, I wait and check the exit status of the child */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
