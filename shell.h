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
char *_getEnv(char *text);
void _Forks(char *programName, char **sunny_token);
int close_shell(char *text);
void executes_cmds(char *programName, char **sunny_token);
int sunny_error(char *programName, char **sunny_token, int errNum);
int _strLen(char *text);
int _strnCmp(const char *goal, char *origin, int number);
char *_strCpy(char *goal, char *origin);
char *_strCat(char *goal, char *origin);
char *_strDup(char *text);
char *_strToks(char *text, const char *marks);
char *_strChr(const char *text, int chrt);
void creates_tokens(char *text, char **sunny_token);

#endif
