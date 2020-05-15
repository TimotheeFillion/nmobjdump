/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** print
*/

#include "my_nm.h"

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

void some_ifs(file_t *file)
{
    for (int i = 0; i < file->elf->e_shnum; i++) {
        if (strcmp(&file->str[file->shdr[i].sh_name], ".symtab") == 0)
            file->symtab = (Elf64_Shdr *) &file->shdr[i];
        if (strcmp(&file->str[file->shdr[i].sh_name], ".shstrtab") == 0)
            file->shstrtab = (Elf64_Shdr *) &file->shdr[i];
        if (strcmp(&file->str[file->shdr[i].sh_name], ".strtab") == 0)
            file->strtab = (Elf64_Shdr *) &file->shdr[i];
    }
}

void print_infos(syminfo_t *list)
{
    while (list) {
        if (list->value == 0 && list->type != 'T')
            printf("                 %c %s\n", list->type, list->name);
        else
            printf("%016lx %c %s\n", list->value, list->type, list->name);
        list = list->next;
    }
}