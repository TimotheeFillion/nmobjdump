/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** display64
*/

#include "objdump.h"

static t_type g_machine[] = {
  {EM_386, "i386"},
  {EM_X86_64, "i386:x86-64"},
};

uint32_t display_flags(Elf64_Ehdr *elf, Elf64_Shdr *shdr)
{
  uint32_t		flags;
  int			symFlag;
  int			i;

  flags = symFlag = i = 0;
  if (elf->e_type == ET_REL)
    flags |= HAS_RELOC;
  if (elf->e_type == ET_EXEC)
    flags |= EXEC_P;
  while (i < elf->e_shnum)
    {
      if (shdr[i].sh_type != SHT_SYMTAB || shdr[i].sh_type != SHT_DYNAMIC)
	symFlag = 1;
      i += 1;
    }
  if (symFlag == 1)
    flags |= HAS_SYMS;
  if (elf->e_type == ET_DYN)
    flags |= DYNAMIC;
  if (elf->e_phnum != 0)
    flags |= D_PAGED;
  return (flags);
}

static char	*get_architecture(int e_machine)
{
    for (int i = 0; i != (int)GET_SIZE(g_machine); i++)
        if (g_machine[i].id == e_machine)
  	        return (g_machine[i].value);
    return ("Unknown");
}

void header64(char *filepath, file_t *file)
{
    void *data = mmap(NULL, file->file_size,
    PROT_READ, MAP_SHARED, file->fd, 0);
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)(data);
    Elf64_Shdr shdr = (Elf64_Shdr)((char *) data + ehdr->e_shoff);

    if (data != NULL) {
        printf("\n%s:   file format elf64-x86-64\n", filepath);
        printf("architecture: %s, flags 0x%.8x:\n",
        get_architecture(ehdr->e_machine), display_flags(ehdr, shdr));
        display_flags(ehdr->e_flags);
        printf("start address 0x%016lx\n\n", ehdr->e_entry);
    }
}