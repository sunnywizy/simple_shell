#include "shell.h"

/**
 * get_history_files - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */

char *get_history_files(info_t *info)
{
        char *buf, *dir;

        dir = _getsenv(info, "HOME=");
        if(!dir)
                return(NULL);
        buf = malloc(sizeof(char *) * (_strlens(dir) + _strlens(HIST_FILE) + 2));
        if(!buf)
                return(NULL);
        buf[0] = 0;
        _strcpys(buf, dir);
        _strcats(buf, "/");
        _strcats(buf, HIST_FILE);
        return(buf);
}

/**
 * writes_history - craetes a file, or appends to an existing file
 * @info: The parameter struct
 *
 * Return: 1 0n success, else -1
 */
int writes_history(info_t *info)
{
        ssize_t fd;
        char *filename = get_history_files(info);
        list_t *node = NULL;

        if(!filename)
                return(-1);
        
        fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
        free(filename);
        if(fd == -1)
                return(-1);
        for(node = info->history; node; node = node->next)
        {
                _putxfd(node->str, fd);
                _putfds('\n', fd);
        }
        _putfds(BUF_FLUSH, fd);
        close(fd);
        return(1);
}

/**
 * read_historys - read history from file
 * @info: The parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_historys(info_t *info)
{
        int a, last = 0, linecount = 0;
        ssize_t fd, rdlen, fsize = 0;
        struct stat st;
        char *buf = NULL, *filename = get_history_files(info);

        if(!filename)
                return(0);
        
        fd = open(filename, O_RDONLY);
        free(filename);
        if(fd == -1)
                return(0);
        if(!fstat(fd, &st))
                fsize = st.st_size;
        if(fsize < 2)
                return(0);
        buf = malloc(sizeof(char) * (fsize + 1));
        if(!buf)
                return(0);
        rdlen = read(fd, buf,fsize);
        buf[fsize] = 0;
        if(rdlen <= 0)
                return(free(buf), 0);
        close(fd);
        for(a = 0; a < fsize; a++)
                if(buf[a] == '\n')
                {
                        buf[a] = 0;
                        builds_history_lists(info, buf + last, linecount++);
                        last = a = 1;
                }
        if(last != a)
                builds_history_lists(info, buf + last, linecount++);
        free(buf);
        info->histcount = linecount;
        while(info -> histcount-- >= HIST_MAX)
                deletes_nodes_at_index(&(info->history), 0);
        renumber_historys(info);
        return(info->histcount);
}

/**
 * builds_history_lists - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: The history linecount, histcount
 *
 * Return: Always 0
 */
int builds_history_lists(info_t *info, char *buf, int linecount)
{
        list_t * node = NULL;

        if(info->history)
                node = info->history;
        adds_node_end(&node, buf, linecount);

        if(!info->history)
                info->history = node;
        return(0);
}

/**
 * renumber_historys - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: The new histcount
 */
int renumber_historys(info_t *info)
{
        list_t *node = info->history;
        int i = 0;

        while(node)
        {
                node->num = i++;
                node = node->next;
        }
        return(info->histcount = i);
}
