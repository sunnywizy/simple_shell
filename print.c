#include "shell.h"

/**
 * print_string - Prints Inputs (strings) to stdout if fd is 1 else stderr
 * @files_descs: 1 for stdout, >2 for stderr
 * @text: Inpput od string
 * Return: Always 0 if sucessful
 */
int print_string(int files_descs, char *text)
{
        if(files_descs == 1)
                write(STDOUT_FILENO, text, _strLen(text));
        else
                write(STDERR_FILENO, text, _strLen(text))
        
        return(0);
}

/**
 * print_integer - Prints Input (Integer) to stdout if fd is 1 else stderr
 * @files_descs: 1 for stdout, >2 for stderr
 * @i: Input or Integer
 * Return: Always 0 if successful
 */
int print_integer(int files_descs, int i)
{
        char string;

        /*Prints integer when i is > 9*/
        if(i >= 10)
                return(print_integer(files_descs, i /10) + print_integer(files_descs, i % 10));
        
        string = '0' + i;

        if(files_descs == 1)
                return(print_string(STDOUT_FILENO, &string));
        
        return(print_string(STDERR_FILENO, &string));
}
