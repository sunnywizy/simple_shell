#include "shell.h"
 
/**
 * clears_info - Initializes info_t struct
 * @info: Struct address
 */
void clears_info(info_t *info)
{
        info->arg = NULL;
        info->argv = NULL;
        info->path = NULL;
        info->argc = 0;
}

/**
 * sets_info - Initializes info_t struct
 * @info: Struct address
 * @av: argument vector
 */
void sets_info(info_t *info, char **av)
{
        int a = 0;
        
        info->fname = av[0];
        if(info->arg)
        {
               info->argv = strtows(info->arg, " \t");
               if(!info->argv)
               {
                        
                        info->argv = malloc(sizeof(char *) * 2);
                        if(info->argv)
                        {
                                info->argv[0] = _strdups(info->arg);
                                info->argv[1] = NULL;
                        }
               }
               for(a = 0; info->argv && info->argv[a]; a++)
                        ;
                info->argc = a;

                replaces_alias(info);
                replaces_vars(info);
        }
}

/**
 * frees_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void frees_info(info_t *info, int all)
{
        ffrees(info->argv);
        info->argv = NULL;
        info->path = NULL;
        if(all)
        {
                if(!info->cmd_buf)
                        free(info->arg);
                if(info->env)
                        frees_lists(&(info->env));
                if(info->history)
                        frees_lists(&(info->history));
                if(info->alias)
                        frees_lists(&(info->alias));
                ffrees(info->environ);
                        info->environ = NULL;
                bfrees((void **)info->cmd_buf);
                if(info->readfd > 2)
                        close(info->readfd);
                _putchars(BUF_FLUSH);
        }
}
