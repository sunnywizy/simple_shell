#include "shell.h"

/**
 * _myenvs - Prints the current environment
 * @info: Structure containing potential arguments. Used to maintan
 *        constant function prototype.
 * Return: Always 0
 */
int _myenvs(info_t *info)
{
        print_lists_strs(info->env);
        return(0);
}

/**
 * _getsenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name.
 *
 * Return: the value.
 */
char *_getsenv(info_t *info, const char *name)
{
        list_t *nodes = info->env;
        char *ptr;

        while(nodes)
        {
                ptr = starts_with(nodes->str, name);
                if(ptr && *ptr)
                        return(ptr);
                nodes = nodes->next;
        }
        return(NULL);
}

/**
 * _mysetsenv - Initialize a new environment variable,
 *              or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _mysetsenv(info_t *info)
{
        if(info->argc != 3)
        {
                _eputx("Incorrect number of arguements\n");
                return(1);
        }
        if(_setsenv(info, info->argv[1], info->argv[2]))
                return(0);
        return(1);
}

/**
 * _myunsetsenv - Remove an environemnt variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myunsetsenv(info_t *info)
{
        int n;

        if(info->argc == 1)
        {
                _eputx("Too few arguements.\n");
                return(-1);
        }
        for(n = 1; n <= info->argc; n++)
                _unsetsenv(info, info->argv[i]);
        
        return(0);
}

/** 
 * populate_env_lists - populates env linked list
 * @info: Structure containing potential arguments. used to maint
 *        constant function prototype
 * Return: Always 0
 */
int populate_env_lists(info_t *info)
{
        list_t *nodes = NULL;
        size_t n;

        for(n = 0; environ[n]; n++)
                add_node_end(&nodes, environ[n], 0);
        info->env = nodes;
        return(0);
}
