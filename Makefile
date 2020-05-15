##
## EPITECH PROJECT, 2020
## Untitled (Workspace)
## File description:
## Makefile
##

NAMENM	=	my_nm
NAMEOBJ	=	my_objdump

SRCSNM	=	nm/my_nm.c\
		nm/addinfo.c\
		nm/print.c\
		nm/sort.c\

SRCSOBJ	=	objdump/main.c\
			objdump/flag_f.c\
			objdump/flag_s.c\
			objdump/display64.c\

CFLAGS	+=	-W -Wall -Wextra -Werror

CC	=	gcc

RM	=	rm -f

OBJSNM	=	$(SRCSNM:.c=.o)
OBJSOBJ	=	$(SRCSOBJ:.c=.o)

all:		nm objdump

nm:		$(NAMENM)

objdump:	$(NAMEOBJ);

$(NAMENM):	$(OBJSNM)
		$(CC) $(OBJSNM) -o $(NAMENM) $(LDFLAGS)

$(NAMEOBJ):	$(OBJSOBJ)
		$(CC) $(OBJSOBJ) -o $(NAMEOBJ) $(LDFLAGS)

clean:
		$(RM) $(OBJSNM)
		$(RM) $(OBJSOBJ)

fclean:		clean
		$(RM) $(NAMENM)
		$(RM) $(NAMEOBJ)

re:		fclean all

.PHONY: all nm objdump clean fclean re