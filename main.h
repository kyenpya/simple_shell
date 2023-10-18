#ifndef MAIN_H
#define MAIN_H

#include <stdio.h> /* this is for printf*/
#include <unistd.h>  /* this is for fork, execve*/
#include <stdlib.h>
#include <string.h>  /* this is for strtok*/
#include <stddef>
#include <errno.h> /* this is for errno and perror */
#include <sys/types.h>  /* this is for type pid */
#include <sys/wait.h> /* this is for wait */
#include <sys/stat.h> /* this is for use of stat function */
#include <signal.h>/* this is for signal management */
#include <fcnt1.h> /* this is for open files*/

/************* This is MACROS **************/

#include "macros.h" /* this is for msg help and prompt */

/******* THESE ARE THE STRUCTURES ********/

/**
 * struct info- this is the struct for the program's data
 * @program_name: this is the name of the executable
 * @input_line: this is pointer to the input read for _getline
 * @command_name: this is pointer to the first command typed by the user
 * @exec_counter: this is number of excecuted comands
 * @file_descriptor: this is file descriptor to the input of commands
 * @tokens: this is the pointer to array of tokenized input
 * @env: this is the copy of the environ
 * @alias_list: this is array of pointers with aliases.
 */

typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - this is the struct for the builtins
 * @builtin: this is the name of the builtin
 * @function: this is the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


/*****THESE ARE THE  MAIN FUNCTIONS ******/


/*==this is for  shell.c  ====*/

/* this is to Initialize the struct with the info of the program */
void inicialize_data(data_of_program *data, int arc, char *argv[], char **env);

/* this is to Make the infinite loop that shows the prompt*/
void sisifo(char *prompt, data_of_program *data);

/* this is to Print the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);


/*===this is for  _getline.c  ===*/

/* this is to Read one line of the standar input*/
int _getline(data_of_program *data);

/* this is to split the each line for the logical operators if it exist */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);


/*===== this is for expansions.c ====*/

/* this is to expand variables */
void expand_variables(data_of_program *data);

/* this is to expand aliases */
void expand_alias(data_of_program *data);

/* this is to append the string to the end of the buffer*/
int buffer_add(char *buffer, char *str_to_add);


/*==This is for str_tok.c ==*/

/* this is to Separate the string in tokens using a designed delimiter */
void tokenize(data_of_program *data);

/* this is to Create a pointer to a part of a string */
char *_strtok(char *line, char *delim);


/*==this is for execute.c ===*/

/* this is to Execute a command with its entire path */
int execute(data_of_program *data);


/*== this is for builtins_list.c ===*/

/* This is to match a builtin, executes it */
int builtins_list(data_of_program *data);


/*==  THIS IS TO find_in_path.c ==*/

/* this is to Creates an array of the path directories */
char **tokenize_path(data_of_program *data);

/* This is to Search for program in path */
int find_program(data_of_program *data);


/***** THIS IS FOR HELPERS FOR MEMORY MANAGEMENT ********/


/*===this is helpers_free.c =====*/

/* this is to Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* this is to Free the fields needed each loop */
void free_recurrent_data(data_of_program *data);

/* this is to Free all field of the data */
void free_all_data(data_of_program *data);


/******THIS IS FOR BUILTINS *******/


/*=== this is builtins_more.c ====*/

/* yhis is to Close the shell */
int builtin_exit(data_of_program *data);

/* this is to Change the current directory */
int builtin_cd(data_of_program *data);

/* this is to set the work directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* this is to show help information */
int builtin_help(data_of_program *data);

/* this is to set, unset and show alias */
int builtin_alias(data_of_program *data);


/*===this is builtins_env.c ====*/

/* this is to Show the environment where the shell runs */
int builtin_env(data_of_program *data);

/* this is to create or override a variable of environment */
int builtin_set_env(data_of_program *data);

/* this is to delete a variable of environment */
int builtin_unset_env(data_of_program *data);


/******* THIS IS FOR HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT ******/


/*====this is env_management.c =====*/

/* this is to Gets the value of an environment variable */
char *env_get_key(char *name, data_of_program *data);

/* this is to Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, data_of_program *data);

/* this is to Remove a key from the environment */
int env_remove_key(char *key, data_of_program *data);

/* this is to prints the current environ */
void print_environ(data_of_program *data);


/***** THIS IS HELPERS FOR PRINTING ******/


/*====only helpers_print.c ====*/

/* this is to Prints a string in the standar output */
int _print(char *string);

/* this is to Prints a string in the standar error */
int _printe(char *string);

/* this is to Prints a string in the standar error */
int _print_error(int errorcode, data_of_program *data);


/************only HELPERS FOR STRINGS MANAGEMENT ***********/


/*=====only helpers_string.c =====*/

/* this is to Counts the number of characters of a string */
int str_length(char *string);

/* this is to Duplicates an string */
char *str_duplicate(char *string);

/* this is to Compares two strings */
int str_compare(char *string3, char *string4, int number);

/* this is to Concatenates two strings */
char *str_concat(char *string3, char *string4);

/* this is to Reverse a string */
void str_reverse(char *string);


/*========only helpers_numbers.c ========*/

/* this is to Cast from int to string */
void long_to_string(long number, char *string, int base);

/* this is to convert an string in to a number */
int _atoi(char *s);

/* this is to count the coincidences of character in string */
int count_characters(char *string, char *character);


/*========only alias_management.c ========*/

/* this is to print the list of alias */
int print_alias(data_of_program *data, char *alias);

/* this is to get the alias name */
char *get_alias(data_of_program *data, char *alias);

/* this set the alias name */
int set_alias(char *alias_string, data_of_program *data);


#endif /* MAIN_H */
