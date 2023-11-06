#include "shell.h"

/**
 * hsh - main shell loop
 * @info: The parameter & return info struct
 * @av: argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
        ssize_t r = 0;
        int builtin_rets = 0;

        while(r != -1 && builtin_rets != -2)
        {
                clears_info(info);
                if(interactives(info))
                        _puts("$ ");
                _eputchars(BUF_FLUSH);
                r = get_input(info);
                if(r != -1)
                {
                        sets_info(info, av);
                        builtin_rets= find_builtins(info);
                        if(builtin_rets == -1)
                                find_cmds(info);  
                }
                else if(interactives(info))
                        _putchar('\n');
                free_info(info, 0);  
        }
        write_history(info);
        free_info(info, 1);
        if(!interactives(info) && info->status)
                exit(info->status);
        if(builtin_rets == -2)
        {
                if(info->err_num == -1)
                        exit(info->status);
                exit(info->err_num);
        }
        return(builtin_rets);
}

/**
 * find_builtins - finds a builtin command 
 * @info: The parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *                      0 if builtin executed successfully,
                        1 if builtin found but not successful
                        -2 if builtin signals exit()
 */
int find_builtins(info_t *info)
{
        int a, builts_in_rets = -1;
        builtin_table builtintbl[] = {
                {"exit", _myexit},
                {"env", _myenv},
                {"help", _myhelp},
                {"history", _myhistory},
                {"setenv", _mysetenv},
                {"unsetenv", _myunsetenv},
                {"cd", _mycd},
                {"alias", _myalias},
                {NULL, NULL}
        };

        for(a = 0; builtintbl[a].type; a++)
                if(_strcmp(info->argv[0], builtintbl[a].type) == 0)
                {
                        info->line_count++;
                        builts_in_rets = builtintbl[a].func(info);
                        break;
                }
        return(builts_in_rets);
}

/**
 * find_cmds - finds a command in PATH
 * @info: The parameter & return info struct
 *
 * Return: void
 */
void find_cmds(info_t *info)
{
        char *path = NULL;
        int a, b;

        info->path = info->argv[0];
        if(info->linecount_flag == 1)
        {
                info->line_count++;
                info->linecount_flag = 0;
        }
        for(a = 0, b = 0; info->arg[a]; a++)
                if(!is_delims(info->arg[a], " \t\n"))
                        b++;
        if(!b)
                return;

        path = find_paths(info, _getenv(info, "PATH="), info->argv[0]);
        if(path)
        {
                info->path = path;
                fork_cmds(info);
        }
        else
        {
                if((interactives(info) || _getenv(info, "PATH=")
                        || info->argv[0][0] == '/') && is_cmds(info, info->argv[0]))
                        fork_cmds(info);
                else if(*(info->arg) != '\n')
                {
                        info->status = 127;
                        print_errors(info, "not found\n");
                }
        }
}

/**
 * fork_cmds - forks a an exec thread to run cmd
 * @info: The parameter & return info struct
 *
 * Return: void
 */
void fork_cmds(info_t *info)
{
        pid_t child_pids;

        child_pids = fork();
        if(child_pids == -1)
        {
                /* TODO: PUT ERROR FUNCTION */
                perror("Error:");
                return;
        }
        if(child_pids == 0)
        {
                if(execve(info->path, info->argv, get_environ(info)) == -1)
                {
                        free_info(info, 1);
                        if(errno == EACCES)
                                exit(126);
                        exit(1);
                }
                /* TODO: PUT ERROR FNCTION */
        }
        else
        {
                wait(&(info->status));
                if(WFEXITED(info->status))
                {
                        info->status WEXITSTATUS(info->status);
                        if(info->status == 126)
                                print_errors(info, "Permission denied\n");
                }
        }
}
