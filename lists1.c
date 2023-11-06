#include "shell.h"

/**
 * list_lens - determines length of linked list
 * @h: pointer to first node.
 *
 * Return: size of list
 */
size_t list_lens(const list_t *h)
{
        size_t a = 0;

        while(h)
        {
              h = h->next;
              a++;  
        }
        return(a);
}

/**
 * lists_to_strings returns an array of string of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **lists_to_strings(list_t *head)
{
        list_t *node = head;
        size_t i = list_lens(head), j;
        char **strs;
        char *str;

        if(!head || !i)
                return(NULL);
        strs = malloc(sizeof(char *) * (i + 1));
        if(!strs)
                return(NULL);
        for(i = 0; node; node = node->next, i++)
        {
                str = malloc(_strlens(node->str) + 1);
                if(!str)
                {
                        for(j = 0; j < i; j++)
                                free(strs[j]);
                        free(strs);
                        return(NULL);
                }

                str = _strcpys(str, node->str);
                strs[i] = str;
        }
        strs[i] = NULL;
        return(strs);
}


/**
 * print_lists - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_lists(const list_t *h)
{
        size_t i = 0;

        while(h)
        {
                _putx(convert_numbers(h->num, 10, 0));
                _putchars(':');
                _putchars(' ');
                _putx(h->str ? h->str : "(nil)");
                _putx("\n");
                h = h->next;
                i++;
        }
        return(i);
}

/**
 * nodes_starts_with - returns node whose string starts with prefix
 * @node: pointer t list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nodes_starts_with(list_t *node, char *prefix, char c)
{
        char *p = NULL;

        while(node)
        {
                p = starts_with(node->str, prefix);
                if(p && ((c == -1) || (*p == c)))
                        return(node);
                node = node->next;
        }
        return(NULL);
}

/**
 * gets_nodes_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t gets_nodes_index(list_t *head, list_t *node)
{
        size_t i = 0;

        while(head)
        {
                if(head == node)
                        return(i);
                head = head->next;
                i++;
        }
        return(-1);
}
