#include " shell.h"

/**
 * get_environs - returns the string array copy of our environ
 * @info: Structure conating potential argm=uments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
char **get_environs(info_t * info)
{
        if(!info->environ || info->env_changed)
        {
                info->environ = list_to_strings(info->env);
                info->env_changed = 0;
        }

        return(info->environ);
}

/**
 * _unsetsenv - Remove an environemnt variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: The string env var property
 */
int _unsetsenv(info_t *info, char, *var)
{
        list_t *nodes = info->env;
        size_t a = 0;
        char *p;

        if(!nodes || !var)
                return(0);
        
        while(nodes)
        {
                p = starts_with(node->str, var);
                if(p && *p == '=')
                {
                        info->env_changed = delete_node_at_index(&info->env),
                        a = 0;
                        nodes = info->env;
                        continue;
                }
                node = node->next;
                a++;
        }
        return(info->env_changed);
}

/** 
 * _setsenv - Initialize a new environment variable,
 *            or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string env var property
 * @value: The string env var value
 * Return: Always 0
 */
int _setsenv(info_t *info, char *var, char *value)
{
        char *buf = NULL;
        list_t *nodes;
        char *p;

        if(!var || !value)
                return(0);

        buf = malloc(_strlens(var) + _strlens(value) + 2);
        if(!buf)
                return(1);
        _strncpys(buf, var);
        _strcats(buf, "=");
        _strcats(buf, value);
        nodes = info->env;
        while(nodes)
        {
                p = starts_with(nodes->str, var);
                if(p && *p == '=')
                {
                        free(node->str);
                        nodes->str = buf;
                        info->env_changed = 1;
                        return(0);
                }
                nodes = nodes->next;
        }
        add_node_end(&(info->env), buf, 0);
        free(buf);
        info->env_changed = 1;
        return(0);
}
