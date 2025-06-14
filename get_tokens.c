#include "shell_2.h"

/**
 * get_tokens - makes a tokenized array of arguments
 * @line: line to parse
 * @delimiters: characters to mark tokens
 * @argvp: argument array to populate
 * Return: number of tokens in list
 */
int get_tokens(char *line, const char *delimiters, char ***argvp)
{
        int error, i, numtokens = 0;
        char *t, *token, *line_cpy;
        const char *snew;

        if (!line || !delimiters || !argvp)
        {
                errno = EINVAL;
                return (-1);
        }

        if (_strlen(line) > 0 && line[_strlen(line) - 1] == '\n')
                line[_strlen(line) - 1] = '\0';

        *argvp = NULL;
        snew = line + _strspn(line, delimiters);
        line_cpy = malloc(_strlen(snew) + 1);
        if (!line_cpy)
                return (-1);
        _strcpy(line_cpy, snew);

        t = strtok(line_cpy, delimiters);
        while (t)
        {
                numtokens++;
                t = strtok(NULL, delimiters);
        }

        *argvp = malloc((numtokens + 1) * sizeof(char *));
        if (*argvp == NULL)
        {
                error = errno;
                free(line_cpy);
                errno = error;
                return (-1);
        }

        _strcpy(line_cpy, snew);
        token = strtok(line_cpy, delimiters);
        for (i = 0; token; i++)
        {
                (*argvp)[i] = malloc(_strlen(token) + 1);
                if (!(*argvp)[i])
                {
                        free(line_cpy);
                        free_dub(*argvp);
                        return (-1);
                }
                _strcpy((*argvp)[i], token);
                token = strtok(NULL, delimiters);
        }
        (*argvp)[i] = NULL;

        free(line_cpy);
        return (numtokens);
}

