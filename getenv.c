#include "shell.h"

/** 
 * _getEnv - Collects any environment variable
 * @text: Input
 * Return: Environ if successful else NULL
 */
char *_getEnv(char *text)
{
        int str_len = _strLen(text);
        int n = 0;

       for(; environ[n] != NULL; n++)
       {
                if(_strnCmp(environ[n], text, str_len) == 0 && environ[n][str_len] == '=')
                {
                        return(environ[n] +str_len + 1);
                }
       }

       return(NULL);
}
