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

        old_path = _get_env("PATH");

        if(old_path)
        {
                new_path = path_memories(old_path, cmds);
                return(new_path);
        }

        return(NULL);
}

/**
 * path_memories - Gets the path of my current working directory
 * @old_path: Pointer to store the path
 * @cmds: Inputs
 * Return: Always file_path else NULL if successfull
 */
char *path_memories(char *old_path, char *cmds)
{
        char *pathTokens, *filePaths, *myPathCopy;

        myPathCopy = _strdup(old_path);
        pathTokens = _strtoks(myPathCopy, ":");
        filePaths = malloc(_strlen(cmds) + _strlen(myPathCopy) + 2);

       while(pathTokens != NULL)
       {
                _strcpy(filePaths, pathTokens);
                _strcat(filePaths, "/");
                _strcat(filePaths, command);
                _strcat(filePaths, "\0");

                if(access(filePaths, X_OK) == 0)
                {
                        return(filePaths);
                        free(filePaths);
                        free(myPathCopy);
                }

                pathTokens = _strtoks(NULL, ":");
       }
       
       free(filePaths);
       free(myPathCopy);

       return(NULL);
}
