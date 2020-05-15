/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** types
*/

#include "my_nm.h"

char single_ifs(Elf64_Sym sym, Elf64_Shdr *shdr, char c)
{
    if (shdr[sym.st_shndx].sh_type == SHT_NOBITS &&
    shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE) && c == 1)
        c = 'B';
    if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS &&
    shdr[sym.st_shndx].sh_flags == SHF_ALLOC && c == 1)
        c = 'R';
    if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS &&
    shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE) && c == 1)
        c = 'D';
    if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS &&
    shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR) && c == 1)
        c = 'T';
    if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC && c == 1)
        c = 'D';
    if (c == 1)
        c = 't';
    return c;
}

char ifs_again(Elf64_Sym sym, char c)
{
    if (sym.st_shndx == SHN_UNDEF && c == 1)
        c = 'U';
    if (sym.st_shndx == SHN_ABS && c == 1)
        c = 'A';
    if (sym.st_shndx == SHN_COMMON && c == 1)
        c = 'C';
    return c;
}

char get_type(Elf64_Sym sym, Elf64_Shdr *shdr)
{
    char c = 1;

    if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE && c == 1)
        c = 'u';
    if (ELF64_ST_BIND(sym.st_info) == STB_WEAK && c == 1) {
        c = 'W';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'w';
    }
    if (ELF64_ST_BIND(sym.st_info) == STB_WEAK &&
    ELF64_ST_TYPE(sym.st_info) == STT_OBJECT && c == 1) {
        c = 'V';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'v';
    }
    c = ifs_again(sym, c);
    c = single_ifs(sym, shdr, c);
    if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != 't')
        c += 32;
    return c;
}

void first_node(file_t *file, int pos, char *name)
{
    file->start = malloc(sizeof(syminfo_t));
    file->start->name = name;
    file->start->value = file->sym[pos].st_value;
    file->start->type = get_type(file->sym[pos], file->shdr);
    file->start->next = NULL;
}

void add_to_struct(file_t *file, int pos)
{
    syminfo_t *node = file->start;
    char *name = file->str + file->sym[pos].st_name;

    if (name[strlen(name) - 1] == 'c' && name[strlen(name) - 2] == '.')
        return;
    if (file->start == NULL) {
        first_node(file, pos, name);
        return;
    }
    while (node->next != NULL)
        node = node->next;
    node->next = malloc(sizeof(syminfo_t));
    node->next->name = name;
    node->next->value = file->sym[pos].st_value;
    node->next->type = get_type(file->sym[pos], file->shdr);
    node->next->next = NULL;
}