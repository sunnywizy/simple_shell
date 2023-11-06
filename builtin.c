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
            exitchecks = _erratois(info->argv[1]);
            if(exitchecks == -1)
            {
                    info->status = 2;
                    print_errors(info, "Illegal number: ");
                    _eputx(info->argv[1]);
                    _eputchars('\n');
                    return(1);
            }
            info->err_num = _erratois(info->argv[1]);
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

        s = getcwd(buffer, 1024);
        if(!s)
                _putx("TODO: >>getcwd failure emsg here<<\n");
        if(!info->argv[1])
        {
                dirs = _getsenv(info, "HOME=");
                if(!dirs)
                        chdir_rets = /* TODO: what should this be? */
                                    chdir((dirs = _getsenv(info, "PWD=")) ? dirs : "/");
                else
                        chdir_rets = chdir(dirs);
        }
        else if (_strcmps(info->argv[1], "-") == 0)
        {
                if(!_getsenv(info, "OLDPWD="))
                {
                        _putx(s);
                        _putchars('\n');
                        return(1);
                }
                _putx(_getsenv(info, "OLDPWD=")), _putchars('\n');
                chdir_rets = /* TODO: what should this be? */
                            chdir((dirs = _getsenv(info, "OLDPWD=")) ? dirs : "/");
        }
        else
                chdir_rets = chdir(info->argv[1]);
        if(chdir_rets == -1)
        {
                print_errors(info, "can't cd to ");
                _eputx(info->argv[1]), _eputchars('\n');
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
        _putx("help call works. function not yet implemented \n");
        if(0)
                _putx(*arg_arrays); /* temp att_unused workaround */
        return(0);
}
