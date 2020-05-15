/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** flag_f
*/

#include "objdump.h"

int error_gestion(file_t *file, char *filepath)
{
    if (file->fd == -1) {
        fprintf(stderr, "nm: '%s': No such file\n", filepath);
        return 1;
    }
    if (opendir(filepath) != NULL) {
        fprintf(stderr, "nm: %s: file format not recognized\n", filepath);
        return 1;
    }
    if (check_elf(file)) {
        fprintf(stderr, "nm: %s: file format not recognized\n", filepath);
        return 1;
    }
    return 0;
}

int check_elf(file_t *file)
{
    void *data = mmap(NULL, file->file_size,
    PROT_READ, MAP_SHARED, file->fd, 0);
    char *str = (char *)(data);

    if (str[1] == 'E' && str[2] == 'L' && str[3] == 'F')
        return 0;
    return 1;
}

void flag_f(char *filepath, file_t *file)
{
    header64(filepath, file);
}