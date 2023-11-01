#include "shell.h"

/**
 * _myexits - exits the shell.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Exits with a given exit status
 *         (0) if info.argv[0] != "exit".
 */
int _myexits(info_t *info)
{
        int exitchecks;

    if(info->argv[1])  /* If there is an exit arguement */
    {
            exitchecks = _erratoi(info->argv[1]);
            if(exitchecks == -1)
            {
                    info->status = 2;
                    print_error(info, "Illegal number: ");
                    _eputs(info->argv[1]);
                    _eputchar('\n');
                    return(1);
            }
            info->err_num = _erratoi(info->argv[1]);
            return(-2);
    }
    info->err_num = -1;
    return(-2);
}

/**
 * _mycds -  Changes the current directory of the process.
 * @info: Structure containing potential arguments. Used to maintains
 *        constant function prototype.
 * Return: Always 0
 */
int _mycds(info_t *info)
{
        char *s, *dirs, buffer[1024];
        int chdir_rets;

        s = getcwd(buffer, 1024)
        if(!s)
                _puts("TODO: >>getcwd failure emsg here<<\n");
        if(!info->argv[1])
        {
                dirs = _getsenv(info, "HOME=");
                if(!dirs)
                        chdir_rets = /* TODO: what should this be? */
                                    chdirs((dirs = _getsenv(info, "PWD=")) ? dir : "/");
                else
                        chdir_rets = chdirs(dirs);
        }
        else if (_strcmps(info->argv[1], "-") == 0)
        {
                if(!_getsenv(info, "OLDPWD="))
                {
                        _puts(s);
                        _putchar('\n')
                        return(1);
                }
                _puts(_getsenv(info, "OLDPWD=")), _putchar('\n');
                chdir_rets = /* TODO: what should this be? */
                            chdirs((dirs = _getsenv(info, "OLDPWD=")) ? dirs : "/");
        }
        else
                chdir_rets = chdirs(info->argv[1]);
        if(chdir_rets == -1)
        {
                print_error(info, "can't cd to ");
                _eputs(info->argv[1]), _eputchar('\n');
        }
        else
        {
                _setsenv(info, "OLDPWD", _getsenv(info, "PWD="));
                _setsenv(info, "PWD", getcwd(buffer, 1024));
        }
        return(0);
}

/** 
 * _myhelps - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int _myhelps(info_t *info)
{
        char **arg_arrays;

        arg_arrays = info->argv;
        _puts("help call works. function not yet implemented \n");
        if(0)
                _puts(*arg_arrays); /* temp att_unused workaround */
        return(0);
}
