#include "shell"

/**
 * sunny_error - Display error msg. Called in main(),
 *               _Fork() & executes_cmds
 * @program_name: Name of Shell program after compiling hsh
 * @sunny_token: Stores the address of the input
 * @err_num: Specific numbers for the different error msgs
 * Return: Always -1 (EXIT_FAILURE) if successful
 */
int sunny_error(char *programName, char *sunny_token, int errNum)
{
        static int n = 1;

        if(!errNum)
                n++;
        
        if(errNum)
        {
                print_string(STDERR_FILENO, programName);
                print_string(STDERR_FILENO, ": ");
                print_integer(2, n);
        }

        if(errNum == 1)
        {
                print_string(STDERR_FILENO, ": ");
                print_string(STDERR_FILENO, sunny_token[0]);
                print_string(STDERR_FILENO, ": Fork Failed\n");
        }

        if(errNum == 2)
        {
                print_string(STDERR_FILENO, ": ");
                print_string(STDERR_FILENO, sunny_token[0]);
                print_string(STDERR_FILENO, ": No such file or directory\n");
        }

        if(errNum == 3)
        {
                print_string(STDERR_FILENO, ": ");
                print_string(STDERR_FILENO, sunny_token[0]);
                print_string(STDERR_FILENO, ": not found\n");
        }

        return(EXIT_FAILURE);
}
