#include "shell.h"

/**
 * _strLen - Gets the length of size of the input
 *           Unsed in print_string() & path_memories()
 * @text: Input
 * Return: Length or size (i)
 */
int _strlen(char *text)
{
        int n;
        for(n = 0; text[n] != '\0'; n++)
                ;
        
        return(n);
}

/**
 *
 */
int _strncmp(const char *goal, char *origin, int number)
{
        while(number && *goal == *origin)
        {
                number--;
                goal++;
                origin++;
        }
        if(number)
                return(*goal - *origin);
        
        return(0);
}

/**
 *
 */
char *_strcpy(char *goal, char *origin)
{
        int a;

        a = 0;
        while(goal[a] != '\0')
        {
                goal[a] = origin[a];
                a++;
        }
        goal[a] = '\0';

        return(goal);
}

/**
 *
 */
char *_strcat(char *goal, char *origin)
{
     int a, b;
     
     a = 0;
     b = 0;
     while(goal[a] != '\0')
    {
            a++;
    }
    goal[a] = ' ';
    while(origin[b] != '\0')
    {
            goal[a] = origin[b];
            a++;
            b++;
    }
    goal[a] = '\0';

    return(goal);
}

/**
 *
 */
char *_strdup(char *text)
{
        int length = _strlen(text) + 1;
        char *new_string = malloc(length);

        if(new_string == NULL)
                return(NULL);
        
        _memories_copy(new_string, text, length);

        return(new_string);
}
