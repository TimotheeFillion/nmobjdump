/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** my_nm
*/

#ifndef MY_NM_H_
#define MY_NM_H_

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <elf.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>

typedef struct syminfo_s {
    char *name;
    char type;
    Elf64_Addr value;
    struct syminfo_s *next;
} syminfo_t;

typedef struct file_s {
    int fd;
    int file_size;
    void *data;
    char *str;
    Elf64_Ehdr *elf;
    Elf64_Shdr *shdr;
    Elf64_Shdr *symtab;
    Elf64_Shdr *shstrtab;
    Elf64_Shdr *strtab;
    Elf64_Sym *sym;
    syminfo_t *start;
    int return_val;
} file_t;

void add_to_struct(file_t *file, int pos);
void print_infos(syminfo_t *list);
void sort_list(syminfo_t *start);
void some_ifs(file_t *file);
int check_elf(file_t *file);
int error_gestion(file_t *file, char *filepath);
int display_usage(void);

#endif