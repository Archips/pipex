.PHONY: all bonus clean fclean re

SRCS = mandatory/pipex.c \
	   mandatory/cmd.c \
	   mandatory/process.c \
	   mandatory/utils.c \

SRCS_BONUS = bonus/pipex_bonus.c \
			 bonus/cmd_bonus.c \
			 bonus/files_bonus.c \
			 bonus/free_bonus.c \
			 bonus/process_bonus.c \
			 bonus/utils_bonus.c \
			 bonus/here_doc_bonus.c \
			 get_next_line/get_next_line.c \
			 get_next_line/get_next_line_utils.c \

NAME = pipex
OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

all : ${NAME}

${NAME} : ${OBJS}
	@make -C libft
	@make clean -C libft
	${CC} ${CFLAGS} ${OBJS} -L libft -lft -o ${NAME}

bonus : ${OBJS_BONUS}
	@make -C libft
	@make clean -C libft
	${CC} ${CFLAGS} ${OBJS_BONUS} -L libft -lft -o ${NAME}

clean:
	${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
	${RM} ${NAME}

re: fclean all
