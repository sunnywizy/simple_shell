#include "shell.h"

/** 
 * close_shell - Exit shell programm. Called in _Folks() 
 *               after creating a child process.
 * @text: Input
 * Return: Always 0 if sucessful
 */
int close_shell(char *text)
{
        if(_strnCmp(text, "exit", 4) == 0)
        {
                free(text);
                exit(EXIT_SUCCESS);
        }

        return(0);
}
