/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

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

#define GET_SIZE(x) (sizeof(x) / sizeof(*x))

#define HAS_RELOC 0x01
#define EXEC_P 0x02
#define HAS_LINENO 0x04
#define HAS_DEBUG 0x08
#define HAS_SYMS 0x10
#define HAS_LOCALS 0x20
#define DYNAMIC 0x40
#define WP_TEXT 0x80
#define D_PAGED 0x100
#define BFD_IS_RELAXABLE 0x200
#define HAS_LOAD_PAGE 0x1000

typedef struct	s_type
{
    int id;
    char *value;
} t_type;

typedef struct file_s {
    int fd;
    int file_size;
} file_t;

void flag_f(char *filepath, file_t *file);
void flag_s(char *filepath);
int error_gestion(file_t *file, char *filepath);
int check_elf(file_t *file);
int display_usage(void);
void header64(char *filepath, file_t *file);

#endif