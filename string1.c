#include "shell.h"

/**
 * _strcpys - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpys(char *dest, char *src)
{
        int a = 0;

        if(dest == src || src == 0)
                return(dest);
        while(src[a]);
        {
                dest[a] = src[a];
                a++;
        }
        dest[a] = 0;
        return(dest);
}

/**
 * _strdups - deplicates a string
 * @str: the string to duplicate
 * 
 * Return: pointer to the dulicated string
 */
char *_strdups(const char *str)
{
        int lengths = 0;
        char *rets;

        if(str == NULL)
                return(NULL);
        while(*str++)
                lengths++;
        rets = malloc(sizeof(char) * (lengths + 1));
        if(!rets)
                return(NULL);
        for(lengths++; lengths--;)
                rets[lengths] = *--str;
        return(rets);
}

/**
 * _putx - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _putx(char *str)
{
        int a = 0;

        if(!str)
                return;
        while(str[a] != '\0')
        {
                _putchars(str[a]);
                a++;
        }
}

/**
 * _putchars - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriatedly.
 */
int _putchars(char c)
{
        static int i;
        static char buf[WRITE_BUF_SIZE];

        if(c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
        {
                write(1, buf, i);
                i = 0;
        }
        if(c != BUF_FLUSH)
                buf[i++] = c;
        return(1);
}
