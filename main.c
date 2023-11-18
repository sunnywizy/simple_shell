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
        char *text = NULL, *sunny_token[1], *programName =argv[0];
        (void)argc;

        while(1)
        {
                if(isatty(STDIN_FILENO))
                        print_string(STDOUT_FILENO, "$ ");

                _getLines(&text, &bufferSize);

                creates_tokens(text, sunny_token);
                if(sunny_token[0] == NULL)
                        continue;
                
                _Forks(programName, sunny_token);

                sunny_error(programName, NULL, 0);
        }
        free(text);

        return(0);
}
