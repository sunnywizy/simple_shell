#include "shell.h"

/**
 * _Forks - Creates child process and call executes_cmds() if CP == 0
 * @program_name: Name of shell programm after compiling (./hsh, /.a.out etc)
 * @sunny_token: Store the address of the input
 */
void _Forks(char *programName, char **sunny_token)
{
        pid_t child_pids;
        int close_status, status_codes;

        /*Create child process*/
        child_pids = fork();

        /*Exit shell when called*/
        close_shell(sunny_token[0]);

        /*Exits if fork fails (-1)*/
        if(child_pids == -1)
        {
                sunny_error(programName, sunny_token, 1);
                exit(EXIT_FAILURE);
        }

        /*Calls executes_cmds() if fork is successful (0)*/
        else if(child_pids == 0)
                executes_cmds(programName, sunny_token);
        
        else
        {
                /*Wait for child process to end before Parent process continues*/
                wait(&close_status);

                if(WIFEXITED(close_status) != 0)
                {
                        status_codes = WEXITSTATUS(close_status);

                        if(status_codes == 127)
                                exit(127);
                        if(status_codes == 2)
                                exit(2);
                }
        }
}
