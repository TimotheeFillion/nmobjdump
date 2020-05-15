/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** main
*/

#include "objdump.h"

file_t *init_struct_file(char *filepath)
{
    file_t *file = malloc(sizeof(file_t));

    file->fd = open(filepath, O_RDONLY);
    file->file_size = lseek(file->fd, 0, SEEK_END);
    return file;
}

int check_s(char **av)
{
    for (int i = 0; av[i]; i++)
        if (av[i][0] == '-')
            if (strstr(av[i], "s") != NULL)
                return 1;
    return 0;
}

int check_f(char **av)
{
    for (int i = 0; av[i]; i++)
        if (av[i][0] == '-')
            if (strstr(av[i], "f") != NULL)
                return 1;
    return 0;
}

int objdump(char *filepath, char **av)
{
    file_t *file = init_struct_file(filepath);

    if (error_gestion(file, filepath))
        return 1;
    if (check_f(av))
        flag_f(filepath, file);
    if (check_s(av))
        flag_s(filepath);
    return 0;
}

int main(int ac, char **av)
{
    int return_value = 0;

    if (ac == 1) {
        display_usage();
        return 2;
    }
    for (int i = 1; av[i]; i++)
        if (av[i][0] != '-')
            if (objdump(av[i], av))
                return_value = 84;
    return return_value;
}