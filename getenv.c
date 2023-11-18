#include "shell.h"

/** 
 * _getEnv - Collects any environment variable
 * @text: Input
 * Return: Environ if successful else NULL
 */
char *_get_env(char *text)
{
        int str_len = _strlen(text);
        int n = 0;

       for(; environ[n] != NULL; n++)
       {
                if(_strncmp(environ[n], text, str_len) == 0 && environ[n][str_len] == '=')
                {
                        return(environ[n] + str_len + 1);
                }
       }

       return(NULL);
}
