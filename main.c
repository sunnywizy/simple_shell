#include "shell.h"

/**
 * main - Entry point for my shell program
 * @argc: Counts arguments but typecasted (not use for now)
 * @argv: Arguments variable, gets the name of my shell
          progran=m for use in my error function
 * Return: Always 0 (Success), my shell is perfect
 */

int main(int argc, char *argv[])
{
        size_t bufferSize = 0;
        char *buf = NULL, *sunny_token[1], *programName =argv[0];
        (void)argc;

        for(,,)
        {
                /*checks if its Interactive mode*/
                if(isatty(STDIN_FILENO))
                        print_string(STDOUT_FILENO, "$ ");
                
                /*Collects Input from Users*/
                _getLines(&buf, &bufferSize);

                /*Splits Inputs into tokens*/
                _tokenizes(buf, sunny_token);
                if(sunny_token[0] == NULL)
                        continue;
                
                /*Create Child Progress*/
                _Forks(programName, sunny_token);

                /*Handles the loop in sunny_error()*/
                sunny_error(programName, NULL, 0);

        }
        free(buf);

        return(0);
}
