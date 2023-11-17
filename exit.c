#include "shell.h"

/** 
 * close_shell - Exit shell programm. Called in _Folks() 
 *               after creating a child process.
 * @buf: Input
 * Return: Always 0 if sucessful
 */
int close_shell(char *buf)
{
        if(_strnCmp(buf, "exit, 4") == 0)
        {
                free(buf);
                exit(EXIT_SUCCESS);
        }

        return(0);
}
