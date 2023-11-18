#include "shell.h"

/**
 *
 */
char *_strtoks(char *text, const char *marks)
{
        static char *save_text;
        char *tokenStart, *tokenEnd;

        if(text != NULL)
                save_text = text;
        else if (save_text == NULL)
                return(NULL);

        tokenStart = save_text;
        while(*tokenStart != '\0' && _strChr(marks, *tokenStart) != NULL)
                tokenStart++;
        if(*tokenStart == '\0')
        {
                save_text = NULL;
                return(NULL);
        }

        tokenEnd = tokenStart;
        while(*tokenEnd != '\0' && _strChr(marks, *tokenEnd) == NULL)
                tokenEnd++;
        if(*tokenEnd == '\0')
                save_text = NULL;
        else
        {
                *tokenEnd = '\0';
                save_text = tokenEnd + 1;      
        }

        return(tokenStart);
}

/**
 *
 */
char *_strchr(const char *text, int chrt)
{
        for(; *text != '\0'; text++)
        {
                if(*text == chrt)
                        return((char *)text);
        }

        return(NULL);
}
