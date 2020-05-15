/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** flag_s
*/

#include "objdump.h"

int display_usage(void)
{
    FILE *fptr = NULL;
    char c = 0;

    if ((fptr = fopen("objdump/usage.txt", "r")) == NULL) return 0;
    while ((c = fgetc(fptr)) != EOF)
        fprintf(stderr, "%c", c);
    fclose(fptr);
    return 0;
}

void flag_s(char *filepath)
{
    filepath++;
    printf("bruh\n");
}