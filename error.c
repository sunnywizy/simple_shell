#include "shell.h"

/**
 * sunny_error - Display error msg. Called in main(),
 *               _Fork() & executes_cmds
 * @chart: Name of Shell program after compiling hsh
 * @sunny_token: Stores the address of the input
 * @error_number: Specific numbers for the different error msgs
 * Return: Always -1 (EXIT_FAILURE) if successful
 */
int sunny_error(char *chart, char **sunny_token, int error_number)
{
        static int n = 1;

        if(!error_number)
                n++;
        
        if(error_number)
        {
                print_string(STDERR_FILENO, chart);
                print_string(STDERR_FILENO, ": ");
                print_integer(2, n);
        }

        if(error_number == 1)
        {
                print_string(STDERR_FILENO, ": ");
                print_string(STDERR_FILENO, sunny_token[0]);
                print_string(STDERR_FILENO, ": Fork Failed\n");
        }

        if(error_number == 2)
        {
                print_string(STDERR_FILENO, ": ");
                print_string(STDERR_FILENO, sunny_token[0]);
                print_string(STDERR_FILENO, ": No such file or directory\n");
        }

        if(error_number == 3)
        {
                print_string(STDERR_FILENO, ": ");
                print_string(STDERR_FILENO, sunny_token[0]);
                print_string(STDERR_FILENO, ": not found\n");
        }

        return(EXIT_FAILURE);
}
