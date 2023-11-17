#include "shell.h"

/** 
 * creates_tokens - splits input of buffer into tokens 
 *                  (commands and arguments) using _strToks()
 * @text: Input
 * @sunny_token: Store the address of the tokens (commands and arguments)
 */
void creates_tokens(char *text, char **sunny_token)
{
        int n = 0;

        for(sunny_token[n] = _strToks(text, " \n"); sunny_token[n]; sunny_token[++n] = _strToks(NULL, " \n")) 
        {

        }

        sunny_token[n] = NULL
}
