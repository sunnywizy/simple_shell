#include "shell.h"

/**
 * input_bufs - buffers chained commands 
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_bufs(info_t *info, char **buf, size_t *len)
{
        ssize_t c = 0;
        size_t lens_p = 0;

        if(!*len) /* if nothing left in the buffer, fill it */
        {
                /*bfree((avoid**)info->cmd_buf);*/
                free(*buf);
                *buf = NULL;
                signal(SIGINT, sigintHandlers);
#if USE_GETLINE
                c = getlines(buf, &lens_p, stdin);
#else
                c = _getlines(info, buf, &lens_p);
#endif
                if(c > 0)
                {
                        if((*buf)[c -1] == '\n')
                        {
                                (*buf)[c - 1] = '\0'; /* remove trailing newline */
                                c--;
                        }
                        info->linecount_flag = 1;
                        removes_comments(*buf);
                        builds_history_lists(info, *buf, info->histcount++);
                        /* if (_strchr(*buf, ';') is this a command chain? */
                        {
                                *len = c;
                                info->cmd_buf = buf;
                        }
                }       
        }
        return(c);
}

/**
 * get_inputs - get a line minus the newline 
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_inputs(info_t *info)
{
        static char *buf; /* The ';' command chain buffer */
        static size_t a, b, lens;
        ssize_t c = 0;
        char **buf_p = &(info->arg), *p;

        _putchars(BUF_FLUSH);
        c = input_bufs(info, &buf, &lens);
        if(c == -1) /*EOF */
                return(-1);
        if(lens) /* we have commands left in the chain buffer */
        {
                b = a; /* init new iterator to current buf position */
                p = buf + a; /* get pointer for return */

                check_chains(info, buf, &b, a, lens);
                while (b < lens) /* iterate to semicolon of end */
                {
                        if(is_chains(info, buf, &b))
                                break;
                        b++;
                }

                a = b + 1; /* increment past nulled ';'' */
                if(a >= lens) /* reached end of buffer? */
                {
                        a = lens = 0; /* reset position and length */
                        info->cmd_buf_type = CMD_NORM;
                }

                *buf_p = p; /* pass back pointer to current command position */
                return(_strlens(p)); /* return length of buffer from _getlines() */
        }

        *buf_p = buf; /* else not a chain, pass back buffer from _getlines() */
        return(c); /* return length of buffer from _getlines() */
}

/**
 * read_bufs - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_bufs(info_t *info, char *buf, size_t *i)
{
        ssize_t c = 0;

        if(*i)
                return(0);
        c = read(info->readfd, buf, READ_BUF_SIZE);
        if(c >= 0)
                *i = c;
        return(c);
}

/**
 * _getlines - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getlines(info_t *info, char **ptr, size_t *length)
{
        static char buf[READ_BUF_SIZE];
        static size_t a, lens;
        size_t d;
        ssize_t c = 0, s = 0;
        char *p = NULL, *new_p = NULL, *f;

        p = *ptr;
        if(p && length)
                s = *length;
        if(a == lens)
                a = lens = 0;
        
        c = read_bufs(info, buf, &lens);
        if(c == -1 || (c == 0 && lens == 0))
                return(-1);
        
        f = _strchrs(buf + a, '\n');
        d = f ? 1 + (unsigned int)(f - buf) : lens;
        new_p = _reallocs(p, s, s ? s + d : d + 1);
        if(!new_p) /* MALLOC FAILURE */
                return(p ? free(p), -1 : -1);
        
        if(s)
                _strncats(new_p, buf + a, d - a);
        else
                _strncpys(new_p, buf + a, d - a + 1);
        
        s += d - a;
        a = d;
        p = new_p;

        if(length)
                *length = s;
        *ptr = p;
        return(s);
}

/**
 * sigintHandlers - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandlers(__attribute__((unused))int sig_num)
{
        _putx("\n");
        _putx("$ ");
        _putchars(BUF_FLUSH);
}
