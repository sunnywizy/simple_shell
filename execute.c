#include "shell.h"

/**
 * executes_cmds - Process the inputs and produces output. Called in _Fork()
 * @program_name: Name of shell program after compiling(/hsh, ./a.out etc)
 * @sunny_token: Stroes the address of the input
 */
void executes_cmds(char *programName, char **sunny_token)
{
        char *dirt_path = NULL;
        int numExecve;

        if(sunny_token[0][0] == '/')
        {
                execve(sunny_token[0], sunny_token, environ);

                sunny_error(programName, sunny_token, 2);
        }
        else
        {
             dirt_path = _get_paths(sunny_token[0]);

             if(dirt_path == NULL)
             {
                    sunny_error(programName, sunny_token, 3);
                    exit(127);
             }

             numExecve = execve(dirt_path, sunny_token, environ);
             if(numExecve == -1)
             {
                    sunny_error(programName, sunny_token, 3);
                    exit(127);
             }
        }
}
