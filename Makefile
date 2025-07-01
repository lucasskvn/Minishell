##
## EPITECH PROJECT, 2024
## Makefile Lucas SANGKHAVONGS
## File description:
## Makefile
##

MAINSRC = src/main.c

MAINOBJ = $(MAINSRC:.c=.o)

SRC	=	src/clean_str.c \
		src/env.c	\
		src/commands.c	\
		src/aux.c	\
		src/setenv.c \
		src/cd.c	\
		src/utils_env.c	\
		src/utils_path.c \
		src/redirection.c \
		src/utils_cd.c \
		src/redirections_handler.c \
		src/builtin.c \
		src/execute.c \
		src/path.c \
		src/pipe.c

OBJ	=	$(SRC:.c=.o)

LIBSRC = 	lib/my/my_strcmp.c	\
			lib/my/my_strncmp.c \
			lib/my/my_putstr.c	\
			lib/my/my_strdup.c	\
			lib/my/my_strlen.c 	\
			lib/my/my_putchar.c	\
			lib/my/my_strcat.c \
			lib/my/my_put_nbr.c \
			lib/my/my_strcpy.c \
			lib/my/my_strstr.c \
			lib/my/my_strchr.c

LIBOBJ =	$(LIBSRC:.c=.o)

NAME	=	mysh

LIBMY 	= 		libmy.a

CC      =       gcc

CFLAGS  =       -Wall -Wextra -Iinclude -g

LIBFLAG =       -L lib/my

MY      =       my.h

TEST_SRC =      tests/tests_connect_link.c

TESTOBJ =       $(TEST_SRC:.c=.o)

TEST_NAME =     unit_tests

TEST_FLAG =     --coverage -lcriterion $(LIBFLAG) $(CFLAGS) $(LIBFLAG)

TEST_DIR =      .

TEST_SCRIPT =   test_shell.sh

all: 	cp libmy compile

compile: $(MAINOBJ) $(OBJ)
		$(CC) -o $(NAME) $(MAINOBJ) $(OBJ) $(LIBOBJ) $(CFLAGS) $(LIBFLAG)

cp:
		@cmp -s lib/my/my.h include/my.h || cp lib/my/my.h include/

libmy: $(LIBOBJ)
		@cmp -s lib/my/$(LIBMY) $(LIBMY) || ($(AR) rc $(LIBMY) $(LIBOBJ) && ranlib $(LIBMY) && cp $(LIBMY) lib/my/)

clean:
		$(RM) $(MAINOBJ)
		$(RM) $(OBJ)
		$(RM) $(TESTOBJ)
		$(RM) $(LIBOBJ)
		$(RM) include/$(MY)
		$(RM) $(LIBMY)
		$(RM) lib/my/$(LIBMY)
		$(RM) *.gc*
		$(RM) lib/$(LIBMY)

fclean: clean
		$(RM) $(NAME)
		$(RM) $(TEST_NAME)

re:		fclean all

tests: all
		cd $(TEST_DIR) && ./$(TEST_SCRIPT)
		make fclean

unit_tests: cp libmy
		$(CC) $(TEST_FLAG) -o $(TEST_NAME) $(TEST_SRC) $(SRC) $(LIBSRC)

tests_run: cp libmy unit_tests
		./$(TEST_NAME)
		make fclean

gcovr: tests_run
		gcovr --exclude tests/*

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all compile clean fclean re unit_tests tests_run gcovr
