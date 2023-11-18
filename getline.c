#include "shell.h"

/**
 *
 */
int _getLines(char **pointer_text, size_t *text_size)
{
        int num_character = 0;
        size_t a = 0, new_text_size;
        char input;
        char *new_text;

        if(pointer_text == NULL || *text_size == 0)
        {
                *text_size = 100;
                *pointer_text = malloc(*text_size);
                if(pointer_text == NULL)
                        return(-1);
        }
        while ((num_character = read(STDIN_FILENO, &input, 1)) > 0)
        {
                if(input == '\n')
                        break;
                (*pointer_text)[a++] = input;

                if(a == *text_size)
                {
                        new_text_size = *text_size * 2;
                        new_text = (char *)malloc(new_text_size);
                        if(new_text == NULL)
                                return(-1);
                        _memories_copy(new_text, *pointer_text, *text_size);
                        free(*pointer_text);
                        *pointer_text = new_text;
                        *text_size = new_text_size;
                }
        }
        if(num_character == 0 && a == 0)
        {
                free(pointer_text);
                exit(EXIT_SUCCESS);
        }
        (*pointer_text)[a] = '\0';

        return(num_character);
}

/**
 *
 */
char *_memories_copy(char *goal, char *origin, unsigned int number)
{
        unsigned int b = 0;

        while(b < number)
        {
                goal[b] = origin[b];
                b++;
        }

        return(goal);
}
