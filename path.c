#include "shell.h"

/**
 * get_paths - Gets the PATH from the environment variable using _getEnv().
 *             Called in execute_command()
 * @cmds: Inputs or string entered
 * ReturnL Always new_path else NULL if successful
 */
char *_get_paths(char *cmds)
{
        char *old_path, *new_path;

        old_path = _getEnv("PATH");

        if(old_path)
        {
                new_path = path_memories(old_path, cmds);
                return(new_path);
        }

        return(NULL);
}

/**
 * path_memory - Gets the path of my current working directory
 * @old_path: Pointer to store the path
 * @cmds: Inputs
 * Return: Always file_path else NULL if successfull
 */
char *path_memories(char *old_path, char *cmds)
{
        char *pathTokens, *filePaths, *myPathCopy;

        myPathCopy = _strDup(old_path);
        pathTokens = _strToks(myPathCopy, ":");
        filePaths = malloc(_strLen(cmds) + _strLen(myPathCopy) + 2);

       for(; pathTokens != NULL; pathTokens = _strToks(NULL, ":"))
       {
                _strCpy(filePaths, pathTokens);
                _strCat(filePaths, "/");
                _strCat(filePaths, cmds);
                _strCat(filePaths, "\0");

                if(access(filePaths, X_OK) == 0)
                {
                         free(myPathCopy);
                         return(filePaths);
                }
       }

       free(filePaths);
       free(myPathCopy);

       return(NULL);
}
