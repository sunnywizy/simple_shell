#include "shell.h"

/**
 * **strtows - splits a string into words. repeat delimiters are ignored
 * @str: The input string
 * @d: The delimeter string
 * Return: a pointer to an array of string, or NULL on failure
 */

char **strtows(char *str, char *d)
{
        int a, b, c, m, numword = 0;
        char **s;
        
        if(str == NULL || str[0] == 0)
                return(NULL);
        if(!d)
                d = " ";
        for(a = 0; str[a] != '\0'; a++)
                if(!is_delims(str[a], d) && (is_delims(str[a + 1], d) || !str[a + 1]))
                        numword++;
                
        if(numword == 0)
                return(NULL);
        s = malloc((1 + numword) * sizeof(char *));
        if(!s)
                return(NULL);
        for(a = 0, b = 0; b < numword; b++)
        {
                while(is_delims(str[a], d))
                        a++;
                c = 0;
                while(!is_delims(str[a + c], d) && str[a + c])
                        c++;
                s[b] = malloc((c + 1) * sizeof(char));
                if(!s[b])
                {
                        for(c = 0; c < b; c++)
                                free(s[c]);
                        free(s);
                        return(NULL);
                }
                for(m = 0; m < c; m++)
                        s[b][m] = str[a++];
                s[b][m] = 0;
        }   
        s[b]  = NULL;
        return(s);
}

/**
 * **strtows2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings or NULL on failure
 */
char **strtows2(char *str, char d)
{
        int a, b, c, m, numword = 0;
        char **s;

        if(str == NULL || str[0] == 0)
                return(NULL);
        for(a = 0; str[a] != '\0'; a++)
                if((str[a] != d && str[a + 1] == d) || 
                    (str[a] != d && !str[a +1]) || str[a + 1] == d)
                            numword++;
        if(numword == 0)
                return(NULL);
        s = malloc((1 + numword) * sizeof(char *));
        if(!s)
                return(NULL);
        for(a = 0, b = 0; b < numword; b++)
        {
                while(str[a] == d && str[a] != d)
                        a++;
                c = 0;
                while(str[a + c] != d && str[a + c] && str[a + c] != d)
                        c++;
                s[b] = malloc((c + 1) * sizeof(char));
                if(!s[b])
                {
                        for(c = 0; c < b; c++)
                            free(s[c]);
                        free(s);
                        return(NULL);
                }
                for(m = 0; m < c; m++)
                        s[b][m] = str[a++];
                s[b][m] = 0;
        }
        s[b] = NULL;
        return(s);
}
