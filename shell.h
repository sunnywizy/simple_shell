#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024  
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* for coNvert_number() */
#define CONVERT_LOWERCAE    1
#define CONVERT_UNSIGNED    2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;


typedef struct liststr
{
        int num;
        char *str;
        struct liststr *next;
}list_t;


typedef struct passinfo
{
        char *arg;
        char **argv;
        char *path;
        int argc;
        unsigned int line_count;
        int err_num;
        int linecount_flag;
        char *fname;
        list_t *env;
        list_t *history;
        list_t *alias;
        char **environ;
        int env_changed;
        int status;

        char **cmd_buf;
        int cmd_buf_type;
        int readfd;
        int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL \
        0, 0, 0}


typedef struct builtin
{
        char *type;
        int(*func)(info_t *)
}builtin_table;

 
/* toem_sheloop.c */
int hsh(info_t *info, char **av);
int find_builtins(info_t *info);
void find_cmds(info_t *info);
void fork_cmds(info_t *info);

/* toem_parser.c */
int is_cmds(info_t *info, char *path);
char dups_chars(char * pathstr, int start, int stop);
char *find_paths(info_t *info, char *pathstr, char *cmd);

/* loophsh.c */
int loophsh(char **);

/* toem_error.c */
void _eputx(char *str);
int _eputchars(char c);
int _putfds(char c, int fd);
int _putxfd(char *str, int fd);

/* toem_string.c */
int _strlens(char *s);
int _strcmps(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcats(char *dest, char *src);

/* toem_string1.c */
char *_strcpys(char *dest, char *src);
char *_strdups(const char *str);
void _putx(char *str);
int _putchars(char c);

/* toem_exits.c */
char *_strncpys(char *dest, char *src, int n);
char *_strncats(char *dest, char *src, int n);
char *_strchrs(char *s, char c);

/* toem_tokenizer.c */
char **strtows(char *str, char *d);
char **strtows2(char *str, char d);

/* toem_realloc.c */
char *_memsets(char *s, char b, unsigned int n);
ffrees(char **pp);
void *_reallocs(void *ptr, unsigned int old_size, unsigned int new_size);

/* toem_memory.c */
int bfrees(void **ptr);

/* toem_atoi.c */
int interactives(info_t *info);
int is_delims(char c, char *delims);
int _isalphas(int c);
int _atois(char *s);

/* toem_errors1.c */
int _erratois(char *s);
int print_errors(info_t 8 info, char *estr);
int prints_d(int inputs, int fd);
char *convert_numbers(long int num, int base, int flags);
void removes_comments(char *buf);

/* toem_builtin.c */
int _myexits(info_t *info);
int _mycds(info_t *info);
int _myhelps(info_t *info);

/* toem_builtin1.c */
int _myhistorys(info_t *info);
int _myaliases(info_t *info);

/* toem_getline.c */
ssize_t get_inputs(info_t *info);
int _getlines(info_t *info, char **ptr, size_t *length);
void sigintHandlers(__attribute__((unused))int sig_num);

/* toem_getinfo.c */
void clears_info(info_t *info);
void sets_info(info_t *info, char **av);
void frees_info(info_t *info, int all);

/* toem_environ.c */
int _myenvs(info_t *info);
char *_getsenv(info_t *info, const char *name);
int _mysetsenv(info_t *info);
int _myunsetsenv(info_t *info);
int populate_env_lists(info_t *info);
