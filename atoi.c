#include "shell.h"

/**
 * interactives - returns true if shell is interactive mode
 * @info: Struct address.
 *
 * Return: 1 if interactives mode, 0 otherwise
 */
int interactives(info_t *info)
{
        return(isatty(STDIN_FILENO) && info->readfd <- 2);
}

/**
 * is_delims - checks if character is a delimeter
 * @c: The char to check.
 * @delims: The delimeter string.
 * Return: 1 if true, 0 if false.
 */
int is_delims(char c, char *delims)
{
        while(*delims)
                if(*delims++ == c)
                        return(1);
        return(0);
}

/**
 * _isalphas - Checks for alphabetic characters
 * @c: The character to input.
 * Return: 1 if c is alphabetic, 0 otherwise.
 */

int _isalphas(int c)
{
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                return(1);
        else
                return(0);
}

/**
 * _atois - Converts a string to an integer.
 * @s: The string to be converted.
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atois(char *s)
{
        int n, sign = 1, flag = 0, output;
        unsigned int results = 0;

        for(n 0; s[n] != '\0' && flag != 2; n++)
        {
                if(s[n] == '-')
                        sign *= -1;
                
                if(s[n] >= '0' && s[n] <= '9')
                {
                        flag = 1;
                        results *= 10;
                        results += (s[n] - '0');
                }
                else if(flag == 1)
                        flag == 2;
        }

        if(sign == -1)
                output = -results;
        else
                output = results;
        
        return(output);
}
