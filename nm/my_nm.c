/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** my_nm
*/

#include "my_nm.h"

file_t *init_struct_file(char *filepath)
{
    file_t *file = malloc(sizeof(file_t));

    file->fd = open(filepath, O_RDONLY);
    file->file_size = lseek(file->fd, 0, SEEK_END);
    file->data = NULL;
    file->str = NULL;
    file->elf = NULL;
    file->shdr = NULL;
    file->symtab = NULL;
    file->shstrtab = NULL;
    file->strtab = NULL;
    file->sym = NULL;
    file->start = NULL;
    return file;
}

void display_sections(file_t *file, int fd)
{
    file->data = mmap(NULL, file->file_size, PROT_READ, MAP_SHARED, fd, 0);
    if (file->data != NULL) {
        file->elf = (Elf64_Ehdr *)(file->data);
        file->shdr = (Elf64_Shdr *)((char *) file->data + file->elf->e_shoff);
        file->str = (char *) (file->data +
        file->shdr[file->elf->e_shstrndx].sh_offset);
        some_ifs(file);
        file->sym = (Elf64_Sym *) (file->data + file->symtab->sh_offset);
        file->str = (char *) (file->data + file->strtab->sh_offset);
        for (size_t i = 0; i < file->symtab->sh_size / sizeof(Elf64_Sym); i++)
            if (file->sym[i].st_name)
                add_to_struct(file, i);
    }
}

int my_nm_mult(char *filepath)
{
    file_t *file = init_struct_file(filepath);

    if (error_gestion(file, filepath))
        return 1;
    display_sections(file, file->fd);
    if (file->start == NULL) {
        fprintf(stderr, "mmap error\n");
        return 1;
    }
    sort_list(file->start);
    printf("\n%s:\n", filepath);
    print_infos(file->start);
    close(file->fd);
    return 0;
}

int my_nm_single(char *filepath)
{
    file_t *file = init_struct_file(filepath);

    if (error_gestion(file, filepath))
        return 84;
    display_sections(file, file->fd);
    if (file->start == NULL) {
        fprintf(stderr, "mmap error\n");
        return 84;
    }
    sort_list(file->start);
    print_infos(file->start);
    close(file->fd);
    return 0;
}

int main(int ac, char **av)
{
    int return_val = 0;

    if (ac == 1)
        return my_nm_single("a.out");
    if (ac == 2)
        return my_nm_single(av[1]);
    for (int i = 1; av[i]; i++) {
        if (my_nm_mult(av[i]) == 1)
            return_val = 84;
    }
    return return_val;
}