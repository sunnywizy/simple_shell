#include "shell.h"

/**
 * _myhistorys - displays the history list, one command by line, preceded
 *               with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myhistorys(info_t *info)
{
        print_lists(info->history);
        return(0);
}

/** 
 * unsets_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 o error
 */
int unsets_alias(info_t *info, char *str)
{
        char *ptr, c;
        int rets;

        ptr = _strchrs(str, '=');
        if(!ptr)
                return(1);
        c = *ptr;
        *ptr = 0;
        rets = deletes_nodes_at_index(&(info->alias), 
                gets_nodes_index(info->alias, nodes_starts_with(info->alias, str, -1)));
        *ptr = c;
        return(rets);
}

/**
 * sets_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int sets_alias(info_t *info, char *str)
{
        char *ptr;

        ptr = _strchrs(str, '=');
        if(!ptr)
                return(1);
        if(!*++ptr)
                return(unsets_alias(info, str));

        unsets_alias(info, str);
        return(adds_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * prints_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error 
 */
int prints_alias(list_t *node)
{
        char *ptr = NULL, *a = NULL;

        if(node)
        {
                ptr = _strchrs(node->str, '=');
                for(a = node->str; a <= ptr; a++)
                        _putchars(*a);
                _putchars('\'');
                _putx(ptr + 1);
                _putx("'\n");
                return(0);
        }
        return(1);
}

/**
 * _myaliases - mimcs the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype
 * Return: Always 0
 */
int _myaliases(info_t *info)
{
        int n = 0;
        char *ptr = NULL;
        list_t *node = NULL;

        if(info->argc == 1)
        {
                node = info->alias;
                while(node)
                {
                        prints_alias(node);
                        node = node->next;
                }
                return(0);
        }
        for(n = 1; info->argv[n]; n++)
        {
                ptr = _strchrs(info->argv[n], '=');
                if(ptr)
                        sets_alias(info, info->argv[n]);
                else
                        prints_alias(nodes_starts_with(info->alias, info->argv[n], '='));
        }

        return(0);
}
