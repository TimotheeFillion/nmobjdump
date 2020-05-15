/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** sort
*/

#include "my_nm.h"

char *filter_name(char *str)
{
    char *new = malloc(strlen(str) * sizeof(char));
    int count = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] != '_' && str[i] != '@') {
            new[count] = str[i];
            count++;
        }
    }
    for (int i = 0; new[i]; i++)
        if (new[i] > 64 && new[i] < 91)
            new[i] += 32;
    return (new);
}

int compare(char *name1, char *name2)
{
    char *sup = filter_name(name1);
    char *inf = filter_name(name2);

    if (strcmp(sup, inf) == 0 && name1[0] == '_')
        return 0;
    if (strcmp(sup, inf) == 0 && name2[0] == '_')
        return 1;
    if (strcmp(sup, inf) > 0)
        return 1;
    return 0;
}

int check_sorted(syminfo_t *start)
{
    syminfo_t *node = start;

    while (node->next != NULL) {
        if (compare(node->name, node->next->name))
            return 1;
        node = node->next;
    }
    return 0;
}

void bubble_sort(syminfo_t *start)
{
    syminfo_t *node = start;
    char *n_tmp = NULL;
    char type_tmp;
    Elf64_Addr value_tmp;

    while (node->next != NULL) {
        if (compare(node->name, node->next->name)) {
            n_tmp = node->name;
            type_tmp = node->type;
            value_tmp = node->value;
            node->name = node->next->name;
            node->value = node->next->value;
            node->type = node->next->type;
            node->next->name = n_tmp;
            node->next->value = value_tmp;
            node->next->type = type_tmp;
        }
        node = node->next;
    }
}

void sort_list(syminfo_t *start)
{
    while (check_sorted(start) != 0)
        bubble_sort(start);
}