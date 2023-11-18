#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

extern char **environ;

int print_string(int files_descs, char *text);
int print_integer(int files_descs, int i);
char *_get_paths(char *cmds);
char *path_memories(char *old_path, char *cmds);
int main(int argc, char *argv[]);
int _getLines(char **pointer_text, size_t *text_size);
char *_memories_copy(char *goal, char *origin, unsigned int number);
char *_get_env(char *text);
void _Forks(char *chart, char **sunny_token);
int close_shell(char *text);
void executes_cmds(char *chart, char **sunny_token);
int sunny_error(char *chart, char **sunny_token, int error_number);
int _strlen(char *text);
int _strncmp(const char *goal, char *origin, int number);
char *_strcpy(char *goal, char *origin);
char *_strcat(char *goal, char *origin);
char *_strdup(char *text);
char *_strtoks(char *text, const char *marks);
char *_strchr(const char *text, int chrt);
void creates_tokens(char *text, char **sunny_token);

#endif
