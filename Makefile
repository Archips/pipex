NAME		= pipex

INC_DIR		= include
INC			= $(INC_DIR) 
			  
SRC_DIR		= src/mandatory
SRCS		= cmd.c						\
			  error.c					\
			  files.c					\
			  main.c					\
			  pipex.c					\
			  utils/free.c				\
			  utils/split.c				\
			  utils/string.c						
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

OBJ_DIR 	= obj
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRC_BONUS_DIR		= src/bonus
SRCS_BONUS			= cmd_bonus.c								\
					  error_bonus.c								\
					  main_bonus.c								\
					  files_bonus.c								\
					  here_doc_bonus.c							\
					  pipex_bonus.c								\
					  get_next_line/get_next_line_bonus.c		\
					  get_next_line/get_next_line_utils_bonus.c	\
					  utils/free_bonus.c						\
					  utils/split_bonus.c						\
					  utils/string_bonus.c	
SRCS_BONUS			:= $(SRCS_BONUS:%=$(SRC_BONUS_DIR)/%)

OBJ_BONUS_DIR	 	= obj
OBJS_BONUS			= $(SRCS_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

CC			= gcc
CPPFLAGS    += $(INC:%=-I%)

CFLAGS		= -Wall -Wextra -Werror

RM		= rm -rf
MAKE	= make -C

# ========== [ Recipe ]

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@$(ECHO)"$(G)created $(END)$(NAME)\n"

bonus: $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS_BONUS) -o $(NAME)
	@$(ECHO)"$(G)created $(END)$(NAME)\n"

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@[ ! -d $(@D) ] && mkdir -p  $(@D) || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@$(ECHO)"$(G)created $(END)$@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@[ ! -d $(@D) ] && mkdir -p  $(@D) || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@$(ECHO)"$(G)created $(END)$@"

clean:
	@[ -d $(OBJ_DIR) ] \
		&& $(RM) $(OBJ_DIR) && $(ECHO)"$(R)removed$(END) $(OBJ_DIR)/\n" || true

fclean: clean
	@[ -f $(NAME) ] \
		&& $(RM) $(NAME) && $(ECHO)"$(R)removed$(END) $(NAME)/\n" || true

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS) | grep -v "OK" || true
	@$(ECHO)"$(G)checked$(END) sources\n"
	@norminette -R CheckDefine $(INC_DIR) | grep -v "OK" || true
	@$(ECHO)"$(G)checked$(END) headers\n"

re : fclean all

.PHONY: all clean fclean norm re

# ========== [ Stdout ]

R		= $(shell tput setaf 1)
G		= $(shell tput setaf 2)
Y		= $(shell tput setaf 3)
B		= $(shell tput setaf 4)
M		= $(shell tput setaf 5)
C		= $(shell tput setaf 6)
W		= $(shell tput setaf 7)
K		= $(shell tput setaf 8)
END		= $(shell tput sgr0)
ECHO	= echo -n "\r\033[K$(NAME): "
