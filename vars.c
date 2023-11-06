#include "shell.h"

/**
 * is_chains - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chains(info_t *info, char *buf, size_t *p)
{
        size_t b = *p;

        if(buf[b] == '|' && buf[b + 1] == '|')
        {
                buf[b] = 0;
                b++;
                info->cmd_buf_type = CMD_OR;
        }
        else if(buf[b] == '&' && buf[b + 1] == '&')
        {
                buf[b] = 0;
                b++;
                info->cmd_buf_type = CMD_OR;
        }
        else if(buf[b] == ';') /* found end of this command */
        {
                buf[b] = 0; /* replace semicolon with null */
                info->cmd_buf_type = CMD_CHAIN;
        }
        else
                return(0);
        *p = j;
        return(1);
}

/**
 * check_chains - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: void
 */
void check_chains(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
        size_t b = *p;

        if(info->cmd_buf_type == CMD_AND)
        {
                if(info->status)
                {
                        buf[i] = 0;
                        b = len;
                }
        }
        if(info->cmd_buf_type == CMD_OR)
        {
                if(!info->status)
                {
                        buf[i] = 0;
                        b = len;
                }
        }

        *p = j;
}

/**
 * replaces_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replace, 0 otherwise
 */
int replaces_alias(info_t *info)
{
        int i;
        list_t *node;
        char *p;

        for(i = 0; i < 10; i++)
        {
                node = node_starts_with(info-alias, info->argv[0], '=');
                if(!node)
                        return(0);
                free(info->argv[0]);
                p = _strchrs(node->str, '=');
                if(!p)
                        return(0);
                p = _strdups(p + 1);
                if(!p)
                        return(0);
                info->argv[0] = p;           
        }
        return(1);
}

/**
 * replaces_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaces_vars(info_t *info)
{
        int i = 0;
        list_t *node;

        for(i = 0; info->argv[i]; i++)
        {
                if(info->argv[i][0] != '$' || !info->argv[i][1])
                        continue;

                if(!_strcmps(info->argv[i], "$?"))
                {
                        replaces_strings(&(info->argv[i]),
                                _strdups(convert_number(info->status, 10, 0)));
                        continue;
                }
                if(!_strcmps(info->argv[i], "$$"))
                {
                        replaces_strings(&(info->argv[i]),
                                _strdups(convert_number(getpid(), 10, 0)));
                        continue;
                }
                node = node_starts_with(info->env, &info->argv[i][1], '=');
                if(node)
                {
                        replaces_strings(&(info->argv[i]),
                                _strdups(_strchrs(node->str, '=') + 1));
                        continue;
                }
                replaces_strings(&info->argv[i], _strdups(""));
        
        }
        return(0);
}

/**
 * replaces_strings - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if relaced, 0 otherwise
 */
int replaces_strings(char **old, char *new)
{
        free(*old);
        *old = new;
        return(1);
}
