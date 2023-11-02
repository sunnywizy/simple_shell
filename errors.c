#include "shell.h"

/** 
 * -eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputx(char *str)
{
        int n = 0;

        if(!str)
                return;
        while(str[n] != '\0')
        {
                _eputchars(str[n]);
                n++;
        }
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * on error, -1 is returned, and errno is set appropriatedly.
 */
int _eputchars(char c)
{
        static int n;
        static char buf[WRITE_BUF_SIZE];

        if(c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
        {
                write(2, buf, n)
                n = 0;
        }
        if(c != BUF_FLUSH)
                buf[n++] = c;
        return(1);
}

/**
 *_putfds - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On sucess 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfds(char c, int fd)
{
        static int n;
        static char buf(WRITE_BUF_SIZE);

        if(c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
        {
                write(fd, buf, n);
                n = 0;
        }
        if(c != BUF_FLUSH)
                buf[n++] = c;
        return(1);
}

/**
 * _putxfd - prints an input string
 * @str: The string to be printed
 * @fd: The filedescriptor to write to
 *
 * Return: The number of chars put
 */
int _putxfd(char *str, int fd)
{
        int n = 0;

        if(!str)
                return(0);
        while(*str)
        {
                n += _putfds(*str++, fd);
        }
        return(n);
}
