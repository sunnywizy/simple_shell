#include "shell.h"

/**
 * _strlens - returns the length of a string
 * @s: The string whose length to check
 *
 * Return: integer length of string
 */
int _strlens(char *s)
{
        int a = 0;

        if(!s)
                return(0);
        
        while(*s++)
                a++;
        return(a);
}

/**
 _strcmps - performs lexicogarphic commparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, zero if s1 == s2
 */
int _strcmps(char *s1, char *s2)
{
        while(*s1 && *s2)
        {
                if(*s1 != *s2)
                        return(*s1 - *s2);
                s1++;
                s2++;
        }
        if(*s1 == *s2)
                return(0);
        else
                return(*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 * 
 * Return: address of next char of haystack of NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
        while(*needle)
                if(*needle++ != *haystack++)
                        return(NULL);
        return((char *)haystack);
}

/**
 * _strcats - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
chat *_strcats(char *dest, char *src)
{
        char *rets = dest;

        while(*dest)
                dest++;
        while(*src)
                *dest++ = *src++;
        *dest = *src;
        return(rets);
}
