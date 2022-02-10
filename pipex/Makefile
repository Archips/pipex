.PHONY: all clen fclean re

SRCS = pipex.c

NAME = pipex
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

all : ${NAME}

${NAME} : ${OBJS}
	@make -C libft
	${CC} ${CFLAGS} ${OBJS} -L libft -lft -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all
