#include "shell.h"

/**
 * *_strncpys - copies a string
 * @dest: The desination strings to be copied to
 * @src: The source string
 * @n: The an=mount of characters to be copied
 * Return: The concatenated string.
 */
char *_strncpys(char *dest, char *src, int n)
{
        int a, b;
        char *s = dest;

        a = 0;
        while(src[a] != '\0' && a < n -1)
        {
                dest[a] = src[a];
                a++;
        }
        if(a < n)
        {
                b = a;
                while(b < n)
                {
                        dest[b] = '\0';
                        b++;
                }
        }
        return(s);
}

/**
 * *_strncats - Concatenates two strings
 * @dest: The first string
 * @src: The second string
 * @n: The amount of bytes to be maximally used
 * Return: The concatenated string
 */
char *_strncats(char *dest, char *src, int n)
{
        int a, b;
        char *s = dest;

        a = 0;
        b = 0;
        while(dest[a] != '\0')
                a++;
        while(src[b] != '\0' && b < n)
        {
                dest[a] = src[b];
                a++;
                b++;
        }
        if(b < n)
                dest[a] = '\0';
        return(s);
}

/**
 * *_strchrs - locates a character in a string
 * @s: The string to be parsed
 * @c: The character to look for
 * Return: (s) a pointer to the memory area s
 */
char *_strchrs(char *s, char c)
{
        do {
                if(*s == c)
                        return(s);
        } while (*s++ != '\0');

        return(NULL);
}
