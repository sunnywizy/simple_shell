#include "shell.h"

/** 
 *_erratois - converts a strings to an integer
 * @s: The string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */
int _erratois(char *s)
{
        int n = 0;
        unsigned long int results = 0;

        if(*s == '+')
                s++; /* TODO: why does this make main return 255? */
        for(n = 0; s[n] != '\0'; n++)
        {
                if(s[n] >= '0' && s[n] <= '9')
                {
                        results *= 10;
                        results += (s[n] - '0');
                        if(results > INT_MAX)
                                return(-1);
                }
                else
                        return(-1);
        }
        return(results);
}

/**
 * print_errors - prints an error message
 * @info: The parameter & return info struct
 * @estr: String containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */
int print_errors(info_t 8 info, char *estr)
{
        _eputx(info->fname);
        _eputx(": ");
        prints_d(info->line_count, STDERR_FILENO);
        _eputx(": ");
        _eputx(info->argv[0]);
        _eputx(": ");
        _eputx(estr);
}

/**
 * prints_d - function prints a decimal (integer) number (base 10)
 * @input: The input
 * @fd: The filedescriptor to write to 
 *
 * Return: number of characters printed
 */
int prints_d(int inputs, int fd)
{
        int (*__putchars)(char) = _putchar;
        int n, counts = 0;
        unsigned int _abx_, current;

        if(fd == STDERR_FILENO)
                __putchars = _eputchars
        if(inputs < 0)
        {
                _abx_ = -inputs;
                __putchars('-');
                counts++;
        }
        else
                _abx_ = inputs;
        current = _abx_;
        for(n = 1000000000; n > 1; n /= 10)
        {
                if(_abx_ / n)
                {
                        __putchars('0' + current / n);
                        counts++;
                }
                current %= n;
        }
        __putchars('0' + current);
        counts++;

        return(counts);
}

/**
 * convert_numbers - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_numbers(long int num, int base, int flags)
{
        static char *arrays;
        static char buffer[50];
        char signs = 0;
        char *ptrs;
        unsigned long n = num;

        if(!(flags & CONVERT_UNSIGNED) && num < 0)
        {
            n = -num;
            signs = '-';

        }
        arrays = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
        ptrs = &buffer[49];
        *ptrs = '\0';

        do      {
                *--ptrs = arrays[n % base];
                n /= base;
        } while(n != 0);

        if(signs)
                *--ptrs = signs;
        return(ptrs);
}

/** 
 * removes_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify.
 *
 * Return: Always 0;
 */
void removes_comments(char *buf)
{
        int n;
        
        for(n = 0; buf[n] != '\0'; n++)
                if(buf[n] == '#' && (!n || buf[n - 1] == ' '))
                {
                        buf[n] = '\0';
                        break;
                }
}
