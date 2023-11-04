#include "shell.h"

/**
 * main - entery point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, i on error
 */
int main(int ac, char **av)
{
        info_t info[] = { INFO_INIT };
        int fd = 2;

        asm("mov %1, %0\n\t"
                "add $3, %0"
                : "=r" (fd)
                : "r"  (fd));

        if(ac == 2)
        {
                fd = open(av[1], O_RDONLY);
                if(fd == -1)
                {
                        if(errno == EACCES)
                                exit(126);
                        if(errno == ENDENT)
                        {
                                _eputx(av[0]);
                                _eputx(": 0: Can't open");
                                _eputx(av[1]);
                                _eputchars('\n');
                                _eputchars(BUF_FLUSH);
                                exit(127);
                        }
                        return(EXIT_FAILURE);
                }
                info->readfd = fd;
        }
        populate_env_lists(info);
        read_historys(info);
        hsh(info, av);
        return(EXIT_SUCCESS);
}
